/**
 * Don't use this code, its nasty, nasty proof-of-concept stuff only.
 * It will eat your lunch and kill your kittens.
 */
var http = require('http'),
		url = require('url'),
    fs = require('fs'),
		io = require(__dirname + '/socket_io/lib/socket.io'),
		sys = require(process.binding('natives').util ? 'util' : 'sys'),
    vm = require('vm'),
    server;

try {
  var drupalSettings = vm.runInThisContext(fs.readFileSync(__dirname + '/nodejs.config.js'));
}
catch (e) {
  console.log("Failed to read config file, exiting: " + e);
  process.exit(1);
}

server = http.createServer(function (request, response) {
  var path = url.parse(request.url).pathname;
  switch (path) {
    case drupalSettings.publishUrl:
			request.setEncoding('utf8');
			request.on('data', function (chunk) {
        var message = JSON.parse(chunk);
        for (var id in clients) {
					console.log('got a call to publish something on channel "' + message.channel + '", data "' + message.message + '" to client "' + id + '"');
					clients[id].send({message: chunk});
        }
			});
			response.writeHead(200, {'Content-Type': 'text/plain'});
			response.end();
      break;
  }
});

server.listen(8080);

send404 = function(res){
  res.writeHead(404);
  res.write('404');
  res.end();
};

var socket = io.listen(server, {port: drupalSettings.port, resource: drupalSettings.resource});
var clients = {};

socket.on('connection', function(client) {
  client.on('message', function(message) {
    var match = null, authkey = '';
    if (match = message.match(/^authkey=(.*)$/)) {
			authkey = match[1];
      if (clients[authkey]) {
				console.log('reusing existing authkey' + authkey);
				return;
			}
			var options = {port: drupalSettings.backend.port, host: drupalSettings.backend.host, path: drupalSettings.backend.authPath + authkey};
      http.get(options, function (response) {
				console.log('client auth key: ' + authkey);
        response.setEncoding('utf8');
				response.on('data', function (chunk) {
          var auth_data = JSON.parse(chunk);
          if (auth_data.nodejs_valid_auth_key) {
            console.log("got valid login for uid " + auth_data.uid);
						clients[authkey] = client;
					}
					else {
            console.log("got invalid login for uid " + auth_data.uid);
						delete clients[authkey];
					}
				});
			}).on('error', function(e) {
				console.log("Got error: " + e.message);
			});
    }
		else {
			console.log('connection from client ' + client.sessionId);
			var msg = {message: client.sessionId + ': ' + message};
			client.broadcast(msg);
			client.send(msg);
		}
  });
  client.on('disconnect', function() {
    console.log('disconnect from client ' + client.sessionId);
		delete clients[client.sessionId];
  });
});

