var rdrand = require('./build/Release/irand');

if (rdrand.hasRdrand() === false) {
  console.log("RDRAND instruction not supported");
}
else {
  console.log(rdrand.rand32());
  console.log(rdrand.rand53());
  console.log(rdrand.rand64b());
  console.log(rdrand.rand64s());
}
