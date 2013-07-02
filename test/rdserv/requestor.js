var net = require('net');

// module-ate the server
var MODULE = (function(){
  var module = {};
  var server;
  var queue = [];
  var rsock = null;

  // create the server that gets random numbers from the ivy bridge server
  var rdserv = function(sock) {
    //'connection' listener
    console.log('server connected');

    // remember the socket
    rsock = sock;

    // when a response is received, forward
    // it to next waiting callback, if any
    sock.on('data',function(data) {
      var rsp = JSON.parse(data);
      var cb;
      console.log('received reply' + rsp.val);
      if (queue.length > 0) {
        cb = queue.pop();
        cb(rsp.val);
      }
    });

    // signal server closed
    sock.on('end', function() {
      console.log('server disconnected');
    });

    // will fire if client disconnects
    sock.on('error',function(err) {
      console.log('disco : ' + err);
      sock.end();
      rsock = null;
    });

    // will fire when socket is fully closed
    sock.on('close',function() {
      console.log('closed');
      rsock = null;
    })
  }

  // start the server
  function startServer() {
    var server = net.createServer(rdserv);
    server.listen(8124, function() { //'listening' listener
      console.log('server bound');
    });
  }

  function requestRandom(callback) {
    if (rsock != null) {
      // add callback to request queue
      queue.push(callback);

      // post a request to the hardware generator
      console.log("sending request");
      rsock.write(JSON.stringify({count:1}));
    }
    else {
      // no connection to hardware generator
      // callback immediately
      callback(null);
    }
  }
  module.start   = startServer;
  module.request = requestRandom;

  return module;
}());

module.exports.start   = MODULE.start;
module.exports.request = MODULE.request;
