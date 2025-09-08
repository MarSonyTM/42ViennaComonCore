const { setupDatabase } = require('../../dist/database/setup');
const { User } = require('../../dist/models/User');
const { Tournament } = require('../../dist/models/Tournament');
const { Match } = require('../../dist/models/Match');
const { Score } = require('../../dist/models/Score');

async function insertTestData() {
    try {
        // Setup database connection
        const knex = await setupDatabase();

        // Create test users
        const user1 = await User.query().insert({
            username: 'player1',
            display_name: 'Player One'
        });
        console.log('✅ Users created successfully');

        const user2 = await User.query().insert({
            username: 'player2',
            display_name: 'Player Two'
        });

        // Create test tournament
        const tournament = await Tournament.query().insert({
            name: 'Test Tournament',
            status: 'in_progress',
            start_time: new Date().toISOString()
        });
        console.log('✅ Tournament created successfully');

        // Create test match
        const match = await Match.query().insert({
            tournament_id: tournament.id,
            player1_id: user1.id,
            player2_id: user2.id,
            status: 'in_progress',
            start_time: new Date().toISOString()
        });
        console.log('✅ Match created successfully');

        // Create test scores
        await Score.query().insert({
            match_id: match.id,
            player_id: user1.id,
            points: 5
        });
        await Score.query().insert({
            match_id: match.id,
            player_id: user2.id,
            points: 3
        });
        console.log('✅ Scores created successfully');

        // Test relationships
        const matchWithRelations = await Match.query()
            .findById(match.id)
            .withGraphFetched('[player1, player2, scores, tournament]');
        
        console.log('\nTest data verification:');
        console.log('Tournament:', matchWithRelations.tournament.name);
        console.log('Player 1:', matchWithRelations.player1.display_name);
        console.log('Player 2:', matchWithRelations.player2.display_name);
        console.log('Scores:', matchWithRelations.scores.map(s => `${s.player_id}: ${s.points}`));

        await knex.destroy();
        console.log('\n✅ All test data inserted and verified successfully');
    } catch (error) {
        console.error('Error:', error);
        process.exit(1);
    }
}

insertTestData();
