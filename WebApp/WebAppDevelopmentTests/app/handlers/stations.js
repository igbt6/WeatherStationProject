
var helpers = require('./helpers.js'),
    stationData = require("../data/station.js"),
    async = require('async'),
    fs = require('fs');

exports.version = "0.1.0";


/**
 * Station class.
 */
function Station (stationData) {
    this.id = stationData.id;
    this.name = stationData.name;
    this.date = stationData.date;
    this.country = stationData.country;
    this.city = stationData.city;

}

Station.prototype.name = null;
Station.prototype.date = null;
Station.prototype.country = null;
Station.prototype.city = null;

Station.prototype.responseObj = function () {
    return { name: this.name,
             date: this.date,
             country: this.country,
             city: this.city };
};




exports.listAllStations = function (req, res) {
    stationData.allStations("date", true, 0, 25, function (err, results) {
        if (err) {
            helpers.sendFailure(res, err);
        } else {
            var out = [];
            if (results) {
                for (var i = 0; i < results.length; i++) {
                    out.push(new Station(results[i]).responseObj());
                }
            }
            helpers.sendSuccess(res, { Stations: out });
        }
    });
};

