//HANDLING MUTIPLE REQUEST TYPES 
var http = require('http');
var fs = require('fs');
var url = require('url');
qs = require('querystring');

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

function loadAlbum(albumName, page, pageSize, callback) {

	fs.readdir("albums/" + albumName, function(err, files) {

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

				var ps;
				// slice fails gracefully if params are out of range
				ps = onlyFiles.splice(page * pageSize, pageSize);
				var obj = {
					name : albumName,
					photos : ps
				};
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
	/*
	 * console.log("---------------------------------------------------");
	 * console.log(req);
	 * console.log("---------------------------------------------------");
	 * console.log(res);
	 * console.log("---------------------------------------------------");
	 */
	req.parsed_url = url.parse(req.url, true);
	console.log("Parsed_Url" + req.parsed_url);
	var coreUrl = req.parsed_url.pathname;
	if (coreUrl == '/albums.json' && req.method.toLowerCase() == 'get') {
		handleListAlbums(req, res);
	} else if (coreUrl.substr(coreUrl.length - 12) == '/rename.json'
			&& req.method.toLowerCase() == 'post') {
		handleRenameAlbum(req, res);
	} else if (coreUrl.substr(0, 7) == '/albums'
			&& coreUrl.substr(coreUrl.length - 5) == '.json'
			&& req.method.toLowerCase() == 'get') {
		handleGetAlbum(req, res);
	} else {
		sendFailure(res, 404, invalidResource());
	}

}




function doRename(old_name, new_name, callback) {

    // rename the album folder.
    fs.rename(
        "albums/" + old_name,
        "albums/" + new_name,
        callback);
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

	// get the GET params
	var getp = req.parsed_url.query;
	var pageNum = getp.page ? getp.page : 0;
	var pageSize = getp.page_size ? getp.page_size : 1000;
	if (isNaN(parseInt(pageNum)))
		pageNum = 0;
	if (isNaN(parseInt(pageSize)))
		pageSize = 1000;

	// format of request is /albums/album_name.json
	var coreUrl = req.parsed_url.pathname;

	var albumName = coreUrl.substr(7, coreUrl.length - 12);
	loadAlbum(albumName, pageNum, pageSize, function(err, albumContent) {
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

function handleRenameAlbum(req, res) {
	// http://localhost:8080/albums/ old_album_name /rename.json
	var coreUrl = req.parsed_url.pathname;
	var parts = coreUrl.split('/');
	if (parts.length != 4) {

		sendFailure(res, 404, invalidResource(coreUrl));
	}
	var albumName = parts[2];
	var json_body = '';
	req.on('readable', function() {
		var d = req.read();
		if (d) {
			if (typeof d == 'string') {
				json_body += d;
			} else if (typeof d == 'object' && d instanceof Buffer) {
				json_body += d.toString('utf8');
			}
		}
	});

	// 3. when we have all the post data, make sure we have valid
	// data and then try to do the rename.
	req.on('end', function() {
		// did we get a body?
		if (json_body) {
			try {
				var album_data = JSON.parse(json_body);
				if (!album_data.album_name) {
					sendFailure(res, 403, missing_data('album_name'));
					return;
				}
			} catch (e) {
				// got a body, but not valid json
				sendFailure(res, 403, bad_json());
				return;
			}
			// 4. Perform rename!
			doRename(albumName, // old
			album_data.album_name, // new
			function(err, results) {
				if (err && err.code == "ENOENT") {
					sendFailure(res, 403, no_such_album());
					return;
				} else if (err) {
					sendFailure(res, 500, file_error(err));
					return;
				}
				sendSuccess(res, null);
			});
		} else { // didn't get a body
			sendFailure(res, 403, bad_json());
			res.end();
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

function file_error(err) {
	var msg = "There was a file error on the server: " + err.message;
	return makeError("server_file_error", msg);
}

function missing_data(missing) {
	var msg = missing ? "Your request is missing: '" + missing + "'"
			: "Your request is missing some data.";
	return makeError("missing_data", msg);
}

function bad_json() {
	return makeError("invalid_json", "the provided data is not valid JSON");
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