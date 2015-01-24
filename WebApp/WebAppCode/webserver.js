/*


var http = require('http');
http.createServer(function(req, res) {
	res.writeHead(200, {
		'Content-Type' : 'text/plain'
	});
	res.end('Hello World\n');
}).listen(1337, '127.0.0.1');
console.log('Server running at http://127.0.0.1:1337/');

 */

/* 
var http = require('http');
function process_request(req, res) {
	var body = 'Thanks for calling!\n';
	var content_length = body.length;
	res.writeHead(200, {
		'Content-Length' : content_length,
		'Content-Type' : 'text/plain'
	});
	res.end(body);
}
var s = http.createServer(process_request);
// s.listen(8080);
console.log('Server running at http://localhost:8081/');

// java script stufff
function person(first, last, age, eyecolor) {
	this.firstName = first;
	this.lastName = last;
	this.age = age;
	this.eyeColor = eyecolor;
}
person.prototype.name = function() {
	return this.firstName + " " + this.lastName;
};

dad = new person("JEREY", "NOOB", 19, "BLUE");
console.log(dad.firstName);
console.log("and full name is...");
setTimeout(function() {
	console.log(dad.name() + "\n");
}, 2000);

// require Node.js Files

var fs = require('fs'); // file handling - NODE

fs.open('info.txt', 'r', function(err, handle) {
	if (!err) {
		var bufLength = 100000;
		var buf = new Buffer(bufLength);
		fs.read(handle, buf, 0, bufLength, null, function(err, length) {
			if (!err) {
				console.log(buf.toString('utf8', 0, length));
				fs.close(handle, function() {
				});
			} else {
				console.log("ERROR while reading file: " + err.code + " "
						+ err.message);
			}
		})
	} else {
		console
				.log("ERROR while opening file: " + err.code + " "
						+ err.message);
	}
});
// another file example:

function FileObject() {
	this.filename = 'DEFAULT';
	this.file_exists = function(callback) {
        var self =this;
		console.log("About to open:" + self.filename);
		fs.open(this.filename, 'r', function(err, handle) {

			if (err) {
				console.log("Can't Open" + self.filename);
				callback(err);
				return;
			}
			fs.close(handle, function() {
			});
			callback(null, true);
		});
	};
}

var fo = new FileObject();
fo.filename = "file_that_does_not_exist";
fo.file_exists(function(err, results) {
	if (err) {
		console.log("Aw, bummer: " + JSON.stringify(err));
		return;
	}
	console.log("file exists!!!");
});
*/



var startServer= require("./jsonServerVer2.js");
startServer.startServer(8100);


