var mysql = require('mysql'),
    localConfig = require("../localConfig.js");

exports.db = function (callback) {

    connSettings = localConfig.config.dbConfig;
    var c = mysql.createConnection({
        host:     connSettings.host,
        user:     connSettings.user,
        password: connSettings.password,
        database: connSettings.database
    });
    callback(null, c);
};
