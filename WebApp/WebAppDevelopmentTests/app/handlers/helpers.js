
var path = require('path');


exports.version = '0.1.0';




exports.sendSuccess = function(res, data) {
    res.writeHead(200, {"Content-Type": "application/json"});
    var output = { error: null, data: data };
    res.end(JSON.stringify(output) + "\n");
}


exports.sendFailure = function(res, err) {
    console.log(err);
    var code = (err.code) ? err.code : err.name;
    res.writeHead(code, { "Content-Type" : "application/json" });
    res.end(JSON.stringify({ error: code, message: err.message }) + "\n");
}


exports.errorForResp = function (err) {
    if (!err instanceof Error) {
        console.error("** Unexpected error type! :"
                      + err.constructor.name);
        return JSON.stringify(err);
    } else {
        var code = err.code ? err.code : err.name;
        return JSON.stringify({ error: code,
                                message: err.message });
    }
}

exports.error = function (code, message) {
    var e = new Error(message);
    e.code = code;
    return e;
};

exports.fileError = function (err) {
    return exports.error("file_error", JSON.stringify(err));
};


exports.isImage = function (filename) {
    switch (path.extname(filename).toLowerCase()) {
      case '.jpg':  case '.jpeg': case '.png':  case '.bmp':
      case '.gif':  case '.tif':  case '.tiff':
        return true;
    }

    return false;
};


exports.invalidResource = function () {
    return exports.error("invalid_resource",
                         "The requested resource does not exist.");
};


exports.missingData = function (what) {
    return exports.error("missing_data",
                         "You must include " + what);
}


exports.notImage = function () {
    return exports.error("not_image_file",
                         "The uploaded file must be an image file.");
};



exports.httpCodeForError = function (err) {
    switch (err.message) {
      case "no_such_album":
        return 403;
      case "invalid_resource":
        return 404;
      case "invalid_email_address":
        return 403;
      case "no_such_user":
        return 403;
    }

    console.log("*** Error needs HTTP response code: " + err.message);
    return 503;
}


exports.validFilename = function (fn) {
    var re = /[^\.a-zA-Z0-9_-]/;
    return typeof fn == 'string' && fn.length > 0 && !(fn.match(re));
};


exports.invalidEmailAddress = function () {
    return exports.error("invalid_email_address",
                        "That's not a valid email address, sorry");
};

exports.authFailed = function () {
    return exports.error("auth_failure",
                         "Invalid email address / password combination.");
};