/*!
 * rdrand : a wrapper on the Intel Ivy Bridge RDRAND instruction
 * generates cryptographically random numbers using the Ivy Bridge hardware RNG
 * Copywright(c) 2013 David howard <dmh2000@gmail.com>
 * MIT licensed
 */
var rdrand = require('./build/Release/irand');

module.exports.rdrand32 = function() {
	return rdrand.rand32();
}

module.exports.rdrand53 = function() {
	return rdrand.rand53();
}

module.exports.rdrand64b = function() {
	return rdrand.rand64b();
}

module.exports.rdrand64s = function() {
  var s = rdrand.rand64s();
	return rdrand.rand64s();
}

module.exports.hasRdrand = function() {
	return rdrand.hasRdrand();
}


