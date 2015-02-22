var mysql = require('mysql'),
    local = require("../localConfig.js");

exports.db = function (callback) {

    connSettings = localConfig.dbConfig;
    var c = mysql.createConnection({
        host:     connSettings.host,
        user:     connSettings.user,
        password: connSettings.password,
        database: connSettings.database
    });
    callback(null, c);
};
