import Knex from 'knex';
import { Model } from 'objection';
import config from '../../knexfile';

export async function setupDatabase() {
  // Initialize knex
  const knex = Knex(config.development);

  // Bind all Models to the knex instance
  Model.knex(knex);

  try {
    // Run migrations
    await knex.migrate.latest();
    console.log('Database migrations completed successfully');

    // Test the connection
    await knex.raw('SELECT 1');
    console.log('Database connection established successfully');

    return knex;
  } catch (error) {
    console.error('Database setup failed:', error);
    throw error;
  }
}

export async function closeDatabase(knex: Knex) {
  try {
    await knex.destroy();
    console.log('Database connection closed successfully');
  } catch (error) {
    console.error('Error closing database connection:', error);
    throw error;
  }
}
