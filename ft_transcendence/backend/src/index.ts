import fastify from 'fastify';
import cors from '@fastify/cors';

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

// Start the server
const start = async () => {
  try {
    await server.listen({ port: 3001, host: '0.0.0.0' });
    console.log('Server is running on port 3001');
  } catch (err) {
    server.log.error(err);
    process.exit(1);
  }
};

start();