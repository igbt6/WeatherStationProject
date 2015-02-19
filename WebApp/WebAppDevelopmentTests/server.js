var express = require('express');
var app = express();
var path = require('path');

app.use(express.logger('dev'));
app.use(express.bodyParser({
	keepExtensions : true
}));

//app.use(express.static(__dirname + '/public'));
app.use(express.static(path.join(__dirname, 'public')));
console.log("DIRNAME: " + __dirname);


app.get("/", function(req, res) {
	//console.log("Cookies: ", req.cookies)
	res.redirect("/pages/index.html");
	res.end();
});


app.get("/station", function(req, res) {
	var fs = require('fs');
    fs.readFile(
            'index.html',
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

app.get('/pages/:pageName', function (req, res) {
	var fs = require('fs');
    var page = req.params.pageName;

    fs.readFile(
        'pages/'+page,
        function (err, contents) {
            if (err) {
            	 res.end("fuckup");
                return;
            }

            contents = contents.toString('utf8');
            //console.log(contents);
            console.log("NEW HTML LOADED !!!!!!!");
            // replace page name, and then dump to output.
            //contents = contents.replace('{{PAGE_NAME}}', page);
            //res.writeHead(200, { "Content-Type": "text/html" });
            res.send(contents);
        }
    );
});


var port = 8082;
app.listen(port);
console.log("Application runs on: " +port+ " port ");