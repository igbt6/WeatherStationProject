var mysql = require('mysql'),
    local = require("../local.config.js");

exports.db = function (callback) {

    connSettings = local.config.dbConfig;
    var c = mysql.createConnection({
        host:     connSettings.host,
        user:     connSettings.user,
        password: connSettings.password,
        database: connSettings.database
    });
    callback(null, c);
};
