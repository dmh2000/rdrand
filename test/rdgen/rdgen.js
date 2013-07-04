var net = require('net')
  , rdrand = require('../../rdrand')

function start() {
  var client = net.connect(8124,"192.168.1.15",
    function() { //'connect' listener
      console.log('client connected');
  });

  client.on('data', function(data) {
    var i;
    var req = JSON.parse(data);
    var r;
    for(i=0;i<req.count;++i) {
      r = {val:rdrand.rdrand64s()};
      client.write(JSON.stringify(r));
    }
  });

  client.on('end', function() {
    console.log('client disconnected');
  });

  client.on('error',function(err) {
    console.log('no connection : ' + err.toString());
  });

  client.on('close',function() {
    console.log('connection closed');
    client = null;

    // restart attempt to connect
    setTimeout(function() {
      console.log('retry connect');
      start();
    },1000);
  });
}

start();
