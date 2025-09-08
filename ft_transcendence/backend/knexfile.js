"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const path_1 = __importDefault(require("path"));
const config = {
    development: {
        client: 'sqlite3',
        connection: {
            filename: path_1.default.join(__dirname, 'database', 'dev.sqlite3')
        },
        migrations: {
            directory: path_1.default.join(__dirname, 'database', 'migrations')
        },
        useNullAsDefault: true,
        pool: {
            afterCreate: (conn, cb) => {
                conn.run('PRAGMA foreign_keys = ON', cb);
            }
        }
    },
    test: {
        client: 'sqlite3',
        connection: {
            filename: ':memory:'
        },
        migrations: {
            directory: path_1.default.join(__dirname, 'database', 'migrations')
        },
        useNullAsDefault: true,
        pool: {
            afterCreate: (conn, cb) => {
                conn.run('PRAGMA foreign_keys = ON', cb);
            }
        }
    }
};
exports.default = config;
