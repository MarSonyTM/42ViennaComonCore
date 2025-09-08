import { Knex } from 'knex';

export async function up(knex: Knex): Promise<void> {
  // Create users table
  await knex.schema.createTable('users', (table) => {
    table.increments('id').primary();
    table.string('username', 255).notNullable().unique();
    table.string('display_name', 255).notNullable();
    table.timestamp('created_at').defaultTo(knex.fn.now());
    table.timestamp('updated_at').defaultTo(knex.fn.now());
  });

  // Create tournaments table
  await knex.schema.createTable('tournaments', (table) => {
    table.increments('id').primary();
    table.string('name', 255).notNullable();
    table.enum('status', ['pending', 'in_progress', 'completed']).defaultTo('pending');
    table.timestamp('start_time');
    table.timestamp('end_time');
    table.timestamp('created_at').defaultTo(knex.fn.now());
    table.timestamp('updated_at').defaultTo(knex.fn.now());
  });

  // Create matches table
  await knex.schema.createTable('matches', (table) => {
    table.increments('id').primary();
    table.integer('tournament_id').unsigned().references('id').inTable('tournaments');
    table.integer('player1_id').unsigned().references('id').inTable('users');
    table.integer('player2_id').unsigned().references('id').inTable('users');
    table.integer('winner_id').unsigned().references('id').inTable('users');
    table.enum('status', ['pending', 'in_progress', 'completed']).defaultTo('pending');
    table.timestamp('start_time');
    table.timestamp('end_time');
    table.timestamp('created_at').defaultTo(knex.fn.now());
    table.timestamp('updated_at').defaultTo(knex.fn.now());
  });

  // Create scores table
  await knex.schema.createTable('scores', (table) => {
    table.increments('id').primary();
    table.integer('match_id').unsigned().references('id').inTable('matches').onDelete('CASCADE');
    table.integer('player_id').unsigned().references('id').inTable('users');
    table.integer('points').notNullable().defaultTo(0);
    table.timestamp('created_at').defaultTo(knex.fn.now());
    table.timestamp('updated_at').defaultTo(knex.fn.now());
  });
}

export async function down(knex: Knex): Promise<void> {
  await knex.schema.dropTableIfExists('scores');
  await knex.schema.dropTableIfExists('matches');
  await knex.schema.dropTableIfExists('tournaments');
  await knex.schema.dropTableIfExists('users');
}
