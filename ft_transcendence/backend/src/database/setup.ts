import knex, { Knex } from 'knex';
import { Model } from 'objection';
import config from '../../knexfile';

export async function setupDatabase() {
  // Initialize knex
  const db = knex(config.development);

  // Bind all Models to the knex instance
  Model.knex(db);

  try {
    // Run migrations
    await db.migrate.latest();
    console.log('Database migrations completed successfully');

    // Test the connection
    await db.raw('SELECT 1');
    console.log('Database connection established successfully');

    return db;
  } catch (error) {
    console.error('Database setup failed:', error);
    throw error;
  }
}

export async function closeDatabase(db: Knex) {
  try {
    await db.destroy();
    console.log('Database connection closed successfully');
  } catch (error) {
    console.error('Error closing database connection:', error);
    throw error;
  }
}