import fastify from 'fastify';
import cors from '@fastify/cors';
import { setupDatabase, closeDatabase } from './database/setup';

const server = fastify({
  logger: true
});

// Register CORS
server.register(cors, {
  origin: true // Allow all origins in development
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

// Start the server
const start = async () => {
  try {
    // Setup database
    const knex = await setupDatabase();
    server.decorate('knex', knex);

    // Start listening
    await server.listen({ port: 3001, host: '0.0.0.0' });
    console.log('Server is running on port 3001');
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