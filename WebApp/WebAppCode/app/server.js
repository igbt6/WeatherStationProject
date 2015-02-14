var express = require('express');
var app = express();

var db = require('./data/db.js');

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

// POST request to the root URL
app.post('/', function(req, res) {
	res.send('/ POST OK');
});

app.get("/", function(req, res) {
	console.log("Cookies: ", req.cookies)
	res.send('/ GET OK');
	res.redirect("/pages/home");
	res.end();
});

app.get('*', fourOhFour);

// PUT request to the root URL
app.put('/', function(req, res) {
res.send('/ PUT OK');
});
// PATCH request to the root URL
app.patch('/', function(req, res) {
res.send('/ PATCH OK');
});
// DELETE request to the root URL
app.delete('/', function(req, res) {
res.send('/ DELETE OK');
});
// OPTIONS request to the root URL
app.options('/', function(req, res) {
res.send('/ OPTIONS OK');
});
// M-SEARCH request to the root URL
app['m-search']('/', function(req, res) {
res.send('/ M-SEARCH OK');
});
// NOTIFY request to the root URL
app.notify('/', function(req, res) {
res.send('/ NOTIFY OK');
});
// SUBSCRIBE request to the root URL
app.subscribe('/', function(req, res) {
res.send('/ SUBSCRIBE OK');
});
// UNSUBSCRIBE request to the root URL
app.unsubscribe('/', function(req, res) {
res.send('/ UNSUBSCRIBE OK');
});


function fourOhFour(req, res) {
	res.writeHead(404, {
		"Content-Type" : "application/json"
	});
	res.end(JSON.stringify(helpers.invalid_resource()) + "\n");
}

function requireAPILogin(req, res, next) {
	// if they're using the API from the browser, then they'll be auth'd
	if (req.session && req.session.logged_in) {
		next();
		return;
	}
	var rha = req.headers.authorization;
	if (rha && rha.search('Basic ') === 0) {
		var creds = new Buffer(rha.split(' ')[1], 'base64').toString();
		var parts = creds.split(":");
		user_hdlr.authenticate_API(parts[0], parts[1], function(err, resp) {
			if (!err && resp) {
				next();
			} else
				need_auth(req, res);
		});
	} else
		need_auth(req, res);
}

function requirePageLogin(req, res, next) {
	if (req.session && req.session.logged_in) {
		next();
	} else {
		res.redirect("/pages/login");
	}
}

function need_auth(req, res) {
	res.header('WWW-Authenticate', 'Basic realm="Authorization required"');
	if (req.headers.authorization) {
		// no more than 1 failure / 5s
		setTimeout(function() {
			res.send('Authentication required\n', 401);
		}, 5000);
	} else {
		res.send('Authentication required\n', 401);
	}
}

app.listen(8081);
