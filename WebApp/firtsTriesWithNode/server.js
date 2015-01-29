var express = require('express');
var app = express();

var path = require("path");
var async = require('async');
var fs = require ('fs');

var portNr= 8081;
app.listen(portNr);
console.lof("Server runs on port: "+portNr );