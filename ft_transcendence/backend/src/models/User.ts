import { BaseModel } from './BaseModel';
import { Match } from './Match';
import { Score } from './Score';

export class User extends BaseModel {
  username!: string;
  display_name!: string;

  // Table name is specified here
  static get tableName() {
    return 'users';
  }

  // Relationships
  static get relationMappings() {
    return {
      matches_as_player1: {
        relation: BaseModel.HasManyRelation,
        modelClass: Match,
        join: {
          from: 'users.id',
          to: 'matches.player1_id'
        }
      },
      matches_as_player2: {
        relation: BaseModel.HasManyRelation,
        modelClass: Match,
        join: {
          from: 'users.id',
          to: 'matches.player2_id'
        }
      },
      scores: {
        relation: BaseModel.HasManyRelation,
        modelClass: Score,
        join: {
          from: 'users.id',
          to: 'scores.player_id'
        }
      }
    };
  }
}
