var http = require('http');
var url = require('url');
var queryString = require( "querystring" );

var uuid = require('node-uuid');
var mongodb = require('mongodb');

var mongodbServer = new mongodb.Server('localhost', 27017, { auto_reconnect: true, poolSize: 10 });
var db = new mongodb.Db('homework', mongodbServer);

 
 var i=0;
http.createServer(function (req, res) {
    if (req.method == 'POST') {
        var fullBody = '';
        
        req.on('data', function(chunk) {
          // append the current chunk of data to the fullBody variable
          fullBody += chunk.toString();
        });
        
        req.on('end', function() {
        console.log(i++);
        
          // parse the received body data
          var queryObj = queryString.parse(fullBody);
          var obj = JSON.parse( queryObj.jsonData );
 
          //if(obj.privacy=="OPEN") console.log(obj.privacy);
          db.open(function() {
            db.collection('crawler', function(err, collection) {
              //collection.remove({});
              var data = {
                body: obj.message,
                author: obj.from.name,
                timestamp: Date.parse(obj.created_time)/1000,
                title: obj.message?obj.message.indexOf('\n')?obj.message.split('\n')[0]:obj.message:obj.message,
                link: obj.link?obj.link:"",
                board: obj.board,
                num_comments: obj.comments?obj.comments.data.length:0,
                id: obj.id,
                num_likes: obj.likes?obj.likes.data.length:0,
              }
              if(data.timestamp>1404172800 && data.timestamp<1430956800){
                collection.find();
                collection.insert( data, function(err, edata) {
                    if (data) {
                        console.log(data);
                    } else {
                        //console.log(data);
                    }
                });
              }
            });
          });
          //db.close();
          // Website you wish to allow to connect
          res.setHeader('Access-Control-Allow-Origin', 'http://localhost');
          // Request methods you wish to allow
          res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
          // Request headers you wish to allow
          res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');
          // Set to true if you need the website to include cookies in the requests sent
          // to the API (e.g. in case you use sessions)
          res.setHeader('Access-Control-Allow-Credentials', true);

          res.writeHead(200, "OK", {'Content-Type': 'text/html'});
          res.end();
        });
    }
    else{
        // parses the request url
        var theUrl = url.parse( req.url );

        console.log(theUrl.query);
        // gets the query part of the URL and parses it creating an object
        var queryObj = queryString.parse( theUrl.query );

        // queryObj will contain the data of the query as an object
        // and jsonData will be a property of it
        // so, using JSON.parse will parse the jsonData to create an object
        var obj = JSON.parse( queryObj.jsonData );

        //console.log( obj.name +"\r\n");
        
        // Website you wish to allow to connect
        res.setHeader('Access-Control-Allow-Origin', 'http://localhost');
        // Request methods you wish to allow
        res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
        // Request headers you wish to allow
        res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');
        // Set to true if you need the website to include cookies in the requests sent
        // to the API (e.g. in case you use sessions)
        res.setHeader('Access-Control-Allow-Credentials', true);

        res.writeHead(200, "OK", {'Content-Type': 'text/html'});
        res.end();
      }
}).listen(8111);
