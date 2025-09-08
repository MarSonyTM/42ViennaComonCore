import { BaseModel } from './BaseModel';
import { User } from './User';
import { Tournament } from './Tournament';
import { Score } from './Score';

export class Match extends BaseModel {
  tournament_id?: number;
  player1_id!: number;
  player2_id!: number;
  winner_id?: number;
  status!: 'pending' | 'in_progress' | 'completed';
  start_time?: string;
  end_time?: string;

  static get tableName() {
    return 'matches';
  }

  static get relationMappings() {
    return {
      tournament: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: Tournament,
        join: {
          from: 'matches.tournament_id',
          to: 'tournaments.id'
        }
      },
      player1: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: User,
        join: {
          from: 'matches.player1_id',
          to: 'users.id'
        }
      },
      player2: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: User,
        join: {
          from: 'matches.player2_id',
          to: 'users.id'
        }
      },
      winner: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: User,
        join: {
          from: 'matches.winner_id',
          to: 'users.id'
        }
      },
      scores: {
        relation: BaseModel.HasManyRelation,
        modelClass: Score,
        join: {
          from: 'matches.id',
          to: 'scores.match_id'
        }
      }
    };
  }
}
