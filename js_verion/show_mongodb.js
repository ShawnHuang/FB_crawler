var http = require('http');
var url = require('url');
var queryString = require( "querystring" );

var uuid = require('node-uuid');
var mongodb = require('mongodb');

var mongodbServer = new mongodb.Server('localhost', 27017, { auto_reconnect: true, poolSize: 10 });
var db = new mongodb.Db('homework', mongodbServer);

 
db.open(function() {
  db.collection('crawler', function(err, collection) {
    console.log(collection.find());
  });
});
db.close();
