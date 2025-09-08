import { BaseModel } from './BaseModel';
import { Match } from './Match';
import { User } from './User';

export class Score extends BaseModel {
  match_id!: number;
  player_id!: number;
  points!: number;

  static get tableName() {
    return 'scores';
  }

  static get relationMappings() {
    return {
      match: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: Match,
        join: {
          from: 'scores.match_id',
          to: 'matches.id'
        }
      },
      player: {
        relation: BaseModel.BelongsToOneRelation,
        modelClass: User,
        join: {
          from: 'scores.player_id',
          to: 'users.id'
        }
      }
    };
  }
}
