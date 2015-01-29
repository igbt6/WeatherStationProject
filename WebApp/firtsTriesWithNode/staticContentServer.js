var http = require('http'), path = require('path'), fs = require('fs');

function handle_incoming_request(req, res) {
	if (req.method.toLowerCase() == 'get'
			&& req.url.substring(0, 9) == '/content/') {
		serve_static_file(req.url.substring(9), res);
	} else {
		res.writeHead(404, {
			"Content-Type" : "application/json"
		});

		var out = {
			error : "not_found",
			message : "'" + req.url + "' not found"
		};
		res.end(JSON.stringify(out) + "\n");
	}
}

function serve_static_file(file, res) {
	fs.exists(file, function(exists) {
		if (!exists) {
			res.writeHead(404, {
				"Content-Type" : "application/json"
			});
			var out = {
				error : "not_found",
				message : "'" + file + "' not found"
			};
			res.end(JSON.stringify(out) + "\n");
			return;
		}
		var rs = fs.createReadStream(file);
		rs.on('error', function(e) {
			res.end();
		});
		var ct = content_type_for_path(file);
		res.writeHead(200, {
			"Content-Type" : ct
		});
		rs.pipe(res);
	});
}

function content_type_for_path(file) {
	var ext = path.extname(file);
	switch (ext.toLowerCase()) {
	case '.html':
		return "text/html";
	case ".js":
		return "text/javascript";
	case ".css":
		return 'text/css';
	case '.jpg':
	case '.jpeg':
		return 'image/jpeg';
	case '.bmp':
		return 'image/bmp';
	default:
		return 'text/plain';
	}
}

var exports = module.exports = {};

exports.startServer = function startServer(port) {
	var server = http.createServer(handle_incoming_request);

	server.on('listening', function() {
		console.log('ok, server is running on port: ' + port);
	});

	server.on('error', function(e) {
		if (e.code == 'EADDRINUSE') {
			console.log('Address in use, retrying...');
			setTimeout(function() {
				server.close();
				server.listen(port);

			}, 1000);

		}
	});
	server.listen(port);
	console.log('Server running  at http://localhost:' + port + '/');
}
