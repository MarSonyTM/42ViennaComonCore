import fastify from 'fastify';
import cors from '@fastify/cors';
import fs from 'fs';
import path from 'path';
import { setupDatabase, closeDatabase } from './database/setup';

const serverOptions = {
  logger: true,
  https: process.env.HTTPS === 'true' ? {
    key: fs.readFileSync('/app/certs/server.key'),
    cert: fs.readFileSync('/app/certs/server.crt')
  } : undefined
};

const server = fastify(serverOptions);

// Register CORS
server.register(cors, {
  origin: true, // Allow all origins in development
  methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
  credentials: true
});

// Health check route
server.get('/health', async (request, reply) => {
  return { status: 'ok', message: 'Server is running' };
});

// Database test route
server.get('/db-test', async (request, reply) => {
  try {
    await server.knex.raw('SELECT 1');
    return { status: 'ok', message: 'Database connection is working' };
  } catch (error) {
    reply.status(500);
    return { status: 'error', message: 'Database connection failed' };
  }
});

// HTTP to HTTPS redirect
server.addHook('onRequest', (request, reply, done) => {
  if (process.env.HTTPS === 'true' && request.protocol === 'http') {
    const httpsUrl = `https://${request.hostname}${request.url}`;
    reply.redirect(301, httpsUrl);
    return;
  }
  done();
});

// Start the server
const start = async () => {
  try {
    // Setup database
    const knex = await setupDatabase();
    server.decorate('knex', knex);

    // Start listening
    await server.listen({ 
      port: 3001, 
      host: '0.0.0.0'
    });
    console.log(`Server is running on port 3001 (${process.env.HTTPS === 'true' ? 'HTTPS' : 'HTTP'})`);
  } catch (err) {
    server.log.error(err);
    process.exit(1);
  }
};

// Handle shutdown
process.on('SIGTERM', async () => {
  console.log('Received SIGTERM signal. Shutting down gracefully...');
  await server.close();
  if (server.knex) {
    await closeDatabase(server.knex);
  }
  process.exit(0);
});

start();