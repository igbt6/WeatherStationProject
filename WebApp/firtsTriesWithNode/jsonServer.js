/**
 * New node file
 */
var http = require('http');
var fs = require('fs');

function loadAlbumList(callback) {

	fs.readdir("albums", function(err, files) {
		if (err) {
			callback(err);
			return;
		}

		var only_dirs = []; // contains only dirs from folder albums
		(function iterator(index) {
			if (index == files.length) {
				callback(null, only_dirs);
				return;
			}
			console.log("Iterator: " + index + " " + files[index]);
			fs.stat("albums/" + files[index], function(err, stats) {
				if (err) {
					callback(err);
					return;
				}
				if (stats.isDirectory()) {
					only_dirs.push(files[index]);
				}
				iterator(index + 1)
			});
		})(0);

		/*
		 * for (var i = 0; i < files.length; i++) { fs.stat("albums/" +
		 * files[i], function(err, stats) { if (stats.isDictionary()) {
		 * only_dirs.push(files[i]); } }); } callback(null, only_dirs);
		 */
	});
}

function handleIncomingRequest(req, res) {

	console.log("Incoming request: " + req.method + " " + req.url);
	loadAlbumList(function(err, albums) {
		if (err) {
			res.writeHead(503, {
				"Content-Type" : "application/json"
			});
			res.end(JSON.stringify(err) + "\n");
			return;
		}

		var out = {
			error : null,
			data : {
				albums : albums
			}
		};
		res.writeHead(200, {
			"Content-Type" : "application/json"
		});
		res.end(JSON.stringify(out) + "\n");
	});
}



var exports = module.exports = {};

exports.startServer = function startServer(port) {
	var server = http.createServer(handleIncomingRequest);

	server.on('listening', function() {
		console.log('ok, server is running on port: ' + port);
	});

	server.on('error', function(e) {
		if (e.code == 'EADDRINUSE') {
			console.log('Address in use, retrying...');
			server.close();
			setTimeout(function() {

				server.listen(port);

			}, 1000);

		}
	});
	server.listen(port);
	console.log('Server running at http://localhost:' + port + '/');
}