import { BaseModel } from './BaseModel';
import { Match } from './Match';

export class Tournament extends BaseModel {
  name!: string;
  status!: 'pending' | 'in_progress' | 'completed';
  start_time?: string;
  end_time?: string;

  static get tableName() {
    return 'tournaments';
  }

  static get relationMappings() {
    return {
      matches: {
        relation: BaseModel.HasManyRelation,
        modelClass: Match,
        join: {
          from: 'tournaments.id',
          to: 'matches.tournament_id'
        }
      }
    };
  }
}
