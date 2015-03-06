var express = require('express');
var app = express();
var path = require('path');
var db = require('./data/db.js');
var config = require('./localConfig.js');
var stationHandler = require('./handlers/stations.js');
var helpers = require('./utility/helpers.js');

app.use(express.logger('dev'));
/*app.use(express.bodyParser({
	keepExtensions : true
}));*/

app.use(express.static(path.join(__dirname, config.config.staticContent)));
console.log("DIRNAME: " + __dirname);


app.get("/", function(req, res) {
	//console.log("Cookies: ", req.cookies)
	res.redirect("/pages/home.html");
	res.end();
});


app.get("/home", function(req, res) {
	var fs = require('fs');
    fs.readFile(
            'home.html',
            function (err, contents) {
                if (err) {
                    sendFailure(res, 500, err);
                    return;
                }

                contents = contents.toString('utf8');
                console.log(contents);
                res.send(contents);

            }
        );
});

app.get('/pages/:pageName', function (req, res) {
	var fs = require('fs');
    var page = req.params.pageName;

    fs.readFile(
        '../pages/'+page,
        function (err, contents) {
            if (err) {
            	 res.end("fuckup");
                return;
            }
            contents = contents.toString('utf8');
            console.log("NEW HTML LOADED !!!!!!!");
            res.send(contents);
        }
    );
});

//scripts
app.get('/script/:scriptName', function (req,res){
    var fs = require('fs');
    var script = req.params.scriptName;
    fs.readFile('../public/content/js/'+script, function(err,data){

        if(err){
            helpers.sendFailure(res, helpers.error(404,"not_found_such_script"));
            return;
        }
        res.send(data);
    }

);

});

// databases requests
app.get('/v1/stations.json', stationHandler.listAllStations);
app.get('/v1/stations/:stationName.json', stationHandler.getStationByName);
app.get('/v1/stations/id/:stationId.json', stationHandler.getStationById);

app.get('*', fourOhFour);

function fourOhFour(req,res){

    helpers.sendFailure(res, 404, helpers.invalidResource());

}


var port = 8082;
app.listen(port);
console.log("Application runs on: " +port+ " port ");