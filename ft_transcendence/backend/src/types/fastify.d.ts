import { Knex } from 'knex';
import { FastifyInstance } from 'fastify';

declare module 'fastify' {
  interface FastifyInstance {
    knex: Knex;
  }
}
