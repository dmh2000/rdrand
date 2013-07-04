
all:
	node-gyp configure build

clean:
	node-gyp clean

test: FORCE
	node test/rdrand-test.js

FORCE:


