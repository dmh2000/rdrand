#include <node.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rdrand.h"

// V8 Wrapper for rdrand.c functions

using namespace v8;

#define RETRY_COUNT 10
/**
 * returns a 32 bit random value as a javascript NUMBER. will return 0 if RDRAND instruction failed
 */
Handle<Value> rand32(const Arguments& args) {
    HandleScope scope;
    uint32_t r;
    int      b;

    b = rdrand32(&r,RETRY_COUNT);
    if (b == 0) {
        r = 0;
    }

    Local<Number> num = Number::New((double)r);
    return scope.Close(num);
}

/**
 * returns a 64 bit random value as a javascript NUMBER. will return 0 if RDRAND instruction failed
 * because the javascript NUMBER type is a double precision float, it will have only 53 bits or
 * precision so the value is truncated to 53 bits long. if you need 64, use rand64b and rand64s
 */
Handle<Value> rand53(const Arguments& args) {
    HandleScope scope;
    uint64_t r;
    int      b;

    // get the random number
    b = rdrand64(&r,RETRY_COUNT);
    if (b == 0) {
        r = 0;
    }

    // cast it to a js double (loses 11 bits == 2048 of precision)
    Local<Number> num = Number::New((double)(r / 2048));
    return scope.Close(num);
}

/**
 * returns a 64 bit random value as a javascript ARRAY of the 8 bytes of the 64 bit number
 */
Handle<Value> rand64b(const Arguments& args) {
    HandleScope scope;
    uint64_t r;
    uint8_t *p;
    int      b;

    // get the random value
    b = rdrand64(&r,RETRY_COUNT);
    if (b == 0) {
        r = 0;
    }

    // point at the raw bytes
    p = (uint8_t *)&r;

    // add all 8 bytes to the array
    // transpose the order because Intel is little endian and this only works on Intel Ivy Bridge or later processors
    Local<Array> a = Array::New(8);
    a->Set(0,Uint32::New(p[7]));
    a->Set(1,Uint32::New(p[6]));
    a->Set(2,Uint32::New(p[5]));
    a->Set(3,Uint32::New(p[4]));
    a->Set(4,Uint32::New(p[3]));
    a->Set(5,Uint32::New(p[2]));
    a->Set(6,Uint32::New(p[1]));
    a->Set(7,Uint32::New(p[0]));

    return scope.Close(a);
}

/**
 * returns a 64 bit random value as a javascript STRING representation of the 64 bit decimal number
 */
Handle<Value> rand64s(const Arguments& args) {
    HandleScope scope;
    uint64_t r;
    char     s[24];  // max length of 64 bit number as decimal string is 20 digits
    size_t   len;
    int      b;

    // get the random number
    b = rdrand64(&r,RETRY_COUNT);
    if (b == 0) {
        r = 0;
    }

    // convert to a string
    len = sprintf(s,"%lu",r);

    // return it
    return scope.Close(String::New(s,len));
}

/**
 * @return true if the processor supports the RD rand instruction. false othersise
 */
Handle<Value> hasRdrand(const Arguments& args) {
    HandleScope scope;
    bool b;

    b = hasRDRAND();

    return scope.Close( Boolean::New(b));
}

void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("rand32")  ,FunctionTemplate::New(rand32 )->GetFunction());
  exports->Set(String::NewSymbol("rand53")  ,FunctionTemplate::New(rand53 )->GetFunction());
  exports->Set(String::NewSymbol("rand64b") ,FunctionTemplate::New(rand64b)->GetFunction());
  exports->Set(String::NewSymbol("rand64s") ,FunctionTemplate::New(rand64s)->GetFunction());
  exports->Set(String::NewSymbol("hasRdrand"),FunctionTemplate::New(hasRdrand)->GetFunction());
}

NODE_MODULE(irand, Init)
