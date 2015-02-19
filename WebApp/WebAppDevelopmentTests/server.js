var express = require('express');
var app = express();

app.use(express.logger('dev'));
app.use(express.bodyParser({
	keepExtensions : true
}));

app.get("/", function(req, res) {
	console.log("Cookies: ", req.cookies)
	//res.send('/ GET OK');
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
                res.writeHead(200, { "Content-Type": "text/html" });
                res.end(contents);
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
            console.log(contents);
            // replace page name, and then dump to output.
            //contents = contents.replace('{{PAGE_NAME}}', page);
            res.writeHead(200, { "Content-Type": "text/html" });
            res.end(contents);
        }
    );
});


var port = 8082;
app.listen(port);
console.log("Application runs on: " +port+ " port ");