
var helpers = require('./helpers.js'),
    fs = require('fs');


exports.version = "0.1.0";


exports.generateAdmin = function (req, res) {
    req.params.pageName = 'admin';
    exports.generate(req, res);
};

exports.generate = function (req, res) {

    var page = req.params.pageName;
    if (req.params.subPage && req.params.pageName == 'admin')
        page = req.params.pageName + "_" + req.params.subPage;

    fs.readFile(
        'basic.html',
        function (err, contents) {
            if (err) {
                sendFailure(res, 500, err);
                return;
            }

            contents = contents.toString('utf8');

            // replace page name, and then dump to output.
            contents = contents.replace('{{PAGE_NAME}}', page);
            res.writeHead(200, { "Content-Type": "text/html" });
            res.end(contents);
        }
    );
};

// if we made it here, then we're logged in. redirect to admin home
exports.login = function (req, res) {
    res.redirect("/pages/admin/home");
    res.end();
};
