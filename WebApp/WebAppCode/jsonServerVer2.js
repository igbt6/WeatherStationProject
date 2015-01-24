//HANDLING MUTIPLE REQUEST TYPES 
var http = require('http');
var fs = require('fs');

function loadAlbumList(callback) {

	fs.readdir("albums", function(err, files) {
		if (err) {
			callback(makeError("file Error", JSON.stringify(err)));
			return;
		}

		var only_dirs = []; // contains only dirs from folder albums
		(function iterator(index) {
			if (index == files.length) {
				callback(null, only_dirs);
				return;
			}

			fs.stat("albums/" + files[index], function(err, stats) {
				if (err) {
					callback(makeError("file Error", JSON.stringify(err)));
					return;
				}
				if (stats.isDirectory()) {
					only_dirs.push(files[index]);
				}
				iterator(index + 1)
			});
		})(0);
	});
}

function loadAlbum(albumName, callback) {

	fs.readdir("albums/"+albumName, function(err, files) {

		if (err) {

			if (err.code == "ENOENT") {
				callback(noSuchAlbum());
			} else {
				callback(makeError("file Error", JSON.stringify(err)));
			}
			return;
		}
		var onlyFiles = [];
		var path = "albums/" + albumName + "/";
		(function iterator(index) {

			if (index == files.length) {
				var obj = {
					'name' : albumName,
					'photos' : onlyFiles
				}
				callback(null, obj);
				return;
			}

			fs.stat(path + files[index], function(err, stats) {
				if (err) {
					callback(makeError("file_error", JSON.stringify(err)));
					return;
				}
				if (stats.isFile()) {
					var obj = {
						filename : files[index],
						desc : files[index]
					};
					onlyFiles.push(obj);
				}
				iterator(index + 1)
			});

		})(0);

	});

}

// better version ; )
function handleIncomingRequest(req, res) {

	console.log("Incoming request: " + req.method + " " + req.url);

	if (req.url == '/albums.json') {

		handleListAlbums(req, res);
	} else if (req.url.substr(0, 7) == '/albums'
			&& req.url.substr(req.url.length - 5) == '.json') {
		handleGetAlbum(req, res);
	} else {
		sendFailure(res, 404, invalidResource());
	}

}

function handleListAlbums(req, res) {

	loadAlbumList(function(err, albums) {
		if (err) {
			sendFailure(res, 500, err);
			return;
		}
		sendSuccess(res, {
			albums : albums
		});

	});

}

function handleGetAlbum(req, res) {

	var albumName = req.url.substr(7, req.url.length - 12);
	loadAlbum(albumName, function(err, albumContent) {
		if (err && err.error == "no_such_album") {
			sendFailure(res, 404, err);
			return;
		} else if (err) {
			sendFailure(res, 500, err);
		} else {
			sendSuccess(res, {
				albumData : albumContent
			});
		}

	});

}

function makeError(err, msg) {
	var e = new Error(msg);
	e.code = err;
	return e;
}

function sendSuccess(res, data) {
	res.writeHead(200, {
		"Content-Type" : "application/json"
	});
	var output = {
		error : null,
		data : data
	};
	res.end(JSON.stringify(output) + "\n");
}

function sendFailure(res, code, err) {
	var code = (err.code) ? err.code : err.name;
	res.writeHead(code, {
		"Content-Type" : "application/json"
	});
	res.end(JSON.stringify({
		error : code,
		message : err.message
	}) + "\n");

}

function invalidResource() {

	return makeError("invalid_resource",
			"the requested resource does not exist.");
}

function no_such_album() {
	return make_error("no_such_album", "The specified album does not exist");
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