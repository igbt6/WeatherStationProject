
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



