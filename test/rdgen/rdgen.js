var net = require('net')
  , irand = require('./irand')

var client = net.connect({port: 8124},
  function() { //'connect' listener
    console.log('client connected');
  });

client.on('data', function(data) {
  var i;
  var req = JSON.parse(data);
  var r;
  for(i=0;i<req.count;++i) {
    r = {val:Math.random()};
    client.write(JSON.stringify(r));
  }
});

client.on('end', function() {
  console.log('client disconnected');
});
