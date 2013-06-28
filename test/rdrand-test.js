var rdrand = require('../rdrand');

if (rdrand.hasRdrand() === false) {
  console.log("RDRAND instruction not supported");
  console.log(rdrand.rdrand32());
}
else {
  console.log(rdrand.rdrand32());
  console.log(rdrand.rdrand53());
  console.log(rdrand.rdrand64b());
  console.log(rdrand.rdrand64s());
}

