var rdrand = require('../rdrand');

if (rdrand.hasRdrand() === false) {
  // processor doesn't support RDRAND
  console.log("RDRAND instruction not supported");
}
else {
  console.log(rdrand.rdrand32());
  console.log(rdrand.rdrand53());
  console.log(rdrand.rdrand64b());
  console.log(rdrand.rdrand64s());
}

