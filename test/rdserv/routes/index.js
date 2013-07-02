var rq = require('../requestor');
/*
 * GET home page.
 */

exports.index = function(req, res){
  console.log('requesting a random value');
  // request a random value and render when it gets back
  rq.request(function(r) {
    var v;
    if (r === null) {
      r = 'offline';
    }

    console.log('rendering index');
    res.render('index', { title: 'Express' ,rval:r});
  })
};
