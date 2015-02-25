
var fs = require('fs'),
    local = require('../localConfig.js'),
    db = require('./db.js'),
    path = require("path"),
    async = require('async');

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
                "SELECT * FROM station ORDER BY ? " 
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



exports.stationByName = function (id, callback) {
    var dbc;

    async.waterfall([
        function (cb) {
            if (!id)
                cb(backhelp.missingData("station id"));
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
            callback(backhelp.no_such_album());
        } else {
            callback(null, results[0]);
        }
    });
};