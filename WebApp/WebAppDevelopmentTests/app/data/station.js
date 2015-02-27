
var fs = require('fs'),
local = require('../localConfig.js'),
db = require('./db.js'),
path = require("path"),
async = require('async');
helper = require('../utility/helpers.js');

exports.version = "0.1.0";



exports.allStations = function (sort_by, desc, skip, count, callback) {
    var dbc;
    async.waterfall([
        function (cb) {
            db.db(cb);
        },
        function (dbclient, cb) {
            dbc = dbclient;
            dbc.query(
                "SELECT * FROM stations ORDER BY ? " 
                + (desc ? "DESC" : "ASC")
                + " LIMIT ?, ?",
                [ sort_by, skip, count ],
                cb);
        }
        ],
        function (err, results) {
            if (dbc) dbc.end();
            if (err) {
                callback (err);
            } else {
                callback(null, results);
            }
        });
};

function isCorrectStationParam(param){

    switch(param){
        case 'name':
        case 'id':
        return true;
        default:
        return false;
    }
}

exports.stationByParam = function (value, param, callback) {
    var dbc;
    if(!isCorrectStationParam(param)){callback (helper.error("incorrect_param",
        param +" cannot get this parameter"));
        return;
    }
    async.waterfall([
        function (cb) {
            if (!value)

                cb(helper.missingData("station_"+param));
            else
                db.db(cb);
        },

        function (dbclient, cb) {
            dbc = dbclient;
            dbc.query(
                "SELECT * FROM stations WHERE "+param+" = ?",
                [ value ],
                cb);
        }

        ],
        function (err, results) {
            if (dbc) dbc.end();
            if (err) {
                callback (err);
            } else if (!results || results.length == 0) {
                callback(helper.noSuchStation());
            } else {
                callback(null, results[0]);
        }
    });
};

/*
exports.stationById = function (id, callback) {
    var dbc;

    async.waterfall([
        function (cb) {
            if (!id)
                cb(helper.missingData("station_id"));
            else
                db.db(cb);
        },

        function (dbclient, cb) {
            dbc = dbclient;
            dbc.query(
                "SELECT * FROM stations WHERE id = ?",
                [ id ],
                cb);
        }

    ],
    function (err, results) {
        if (dbc) dbc.end();
        if (err) {
            callback (err);
        } else if (!results || results.length == 0) {
            callback(helper.noSuchStation());
        } else {
            callback(null, results[0]);
        }
    });
};
*/