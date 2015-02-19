var express = require('express');
var app = express();
var db = require('./data/db.js');
var helpers= require('./handlers/helpers.js');
var pageHandlers = require('./handlers/pages.js');

app.use(express.logger('dev'));
app.use(express.bodyParser({
	keepExtensions : true
}));
app.use(express.static(__dirname + "/../static"));
app.use(express.cookieParser("rycie"));
app.use(express.cookieSession({
	secret : "WHERE IS SHE ",
	maxAge : 86400000
}));

// Include the router middleware

app.use(app.router);
app.use(express.favicon(__dirname + '/favicon.ico'));


app.post('/', function(req, res) {
	res.send('/ POST OK');
});
/*
app.get("/", function(req, res) {
	console.log("Cookies: ", req.cookies)
	//res.send('/ GET OK');
	res.redirect("/pages/home");
	res.end();
});
*/


app.get("/station", function(req, res) {
	var fs = require('fs');
    fs.readFile(
            '../static/Bootstraptest/index.html',
            function (err, contents) {
                if (err) {
                    sendFailure(res, 500, err);
                    return;
                }

                contents = contents.toString('utf8');
                console.log(contents);
                //res.writeHead(200, { "Content-Type": "text/html" });
                res.send(contents);
                //res.end();
            }
        );
    //res.end();
});

//app.get('/pages/:pageName', pageHandlers.generate);
	


app.put('/', function(req, res) {
res.send('/ PUT OK');
});

app.patch('/', function(req, res) {
res.send('/ PATCH OK');
});

app.delete('/', function(req, res) {
res.send('/ DELETE OK');
});

app.options('/', function(req, res) {
res.send('/ OPTIONS OK');
});

app['m-search']('/', function(req, res) {
res.send('/ M-SEARCH OK');
});

app.notify('/', function(req, res) {
res.send('/ NOTIFY OK');
});

app.subscribe('/', function(req, res) {
res.send('/ SUBSCRIBE OK');
});

app.unsubscribe('/', function(req, res) {
res.send('/ UNSUBSCRIBE OK');
});

app.get('*', fourOhFour);


function fourOhFour(req, res) {
	res.writeHead(404, {
		"Content-Type" : "application/json"
	});
	res.end(JSON.stringify(helpers.invalidResource()) + "\n");
}


var port = 8081;
app.listen(port);
console.log("Application runs on: " +port+ " port ");
