
var helpers = require('../utility/helpers.js'),
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
Station.prototype.id = null;
Station.prototype.name = null;
Station.prototype.date = null;
Station.prototype.country = null;
Station.prototype.city = null;

Station.prototype.retResponseJSONObj = function () {
    return { id: this.id,
       name: this.name,
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
                    out.push( new Station(results[i]).retResponseJSONObj());
                }
            }
            helpers.sendSuccess(res, { Stations: out });
            //console.log(out);
        }
    });
};


exports.getStationByName= function(req,res){
     console.log("STATIONNAME"+req.params.stationName);
    async.waterfall([
        //get the station
      
        function(cb){
            if(!req.params|| !req.params.stationName){
                cb(helpers.noSuchStation());
            }
            else
                stationData.stationByParam(req.params.stationName,'name',cb);
        }],

        function(err,results){
            if(err){
                helpers.sendFailure(res,err);
            }
            else if(!results){
                helpers.sendFailure(res,helpers.noSuchStation());
            }
            else{
                var station = new Station(results);
                helpers.sendSuccess(res, {Station: station.retResponseJSONObj()});
            }
        }
        );
};


exports.getStationById= function(req,res){
    async.waterfall([
        //get the station
      
        function(cb){
            if(!req.params|| !req.params.stationId){
                cb(helpers.noSuchStation());
            }
            else
                stationData.stationByParam(req.params.stationId,'id',cb);
        }],

        function(err,results){
            if(err){
                helpers.sendFailure(res,err);
            }
            else if(!results){
                helpers.sendFailure(res,helpers.noSuchStation());
            }
            else{
                var station = new Station(results);
                helpers.sendSuccess(res, {Station: station.retResponseJSONObj()});
            }
        }
        );
};
