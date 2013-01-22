         _____                                                      _____                             
      __|___  |__  __   _  ____  ____   _  _____  _____  __  __  __|__   |__  ____    ______  __  __  
     |   ___|    ||  |_| ||    ||    \ | |/     \/     \|  |/ / |     |     ||    \  |   ___||  |/ /  
     |   |__     ||   _  ||    ||     \| ||     ||     ||     \ |    _|     ||     \ |   |__ |     \  
     |______|  __||__| |_||____||__/\____|\_____/\_____/|__|\__\|___|     __||__|\__\|______||__|\__\ 
        |_____|                                                    |_____|                            
          

[![Build Status](https://secure.travis-ci.org/pastjean/fujin.png?branch=master)](http://travis-ci.org/pastjean/fujin)

ChinookPack : Encoder/Decoder for a simplified [MessagePack][msgpack] serialization format

The [MessagePack specification][msgpackspec] is more declarative about the [format][msgpackspec]

[msgpack]:http://msgpack.org/
[msgpackspec]:http://wiki.msgpack.org/display/MSGPACK/Format+specification

Available types
===============

- uint8
- uint16
- int8
- int16
- boolean
- float

- raw bytes


Encoding
========

Integers
--------

### uint8

unsigned 8-bit integer on 2 bytes

    +--------+--------+
    |  0xcc  |XXXXXXXX|
    +--------+--------+
    => unsigned 8-bit XXXXXXXX

### uint16

unsigned 16-bit big-endian integer on 3 bytes

    +--------+--------+--------+
    |  0xcd  |XXXXXXXX|XXXXXXXX|
    +--------+--------+--------+
    => unsigned 16-bit big-endian XXXXXXXX_XXXXXXXX

### int8

signed 8-bit integer on 2 bytes


    +--------+--------+
    |  0xd0  |XXXXXXXX|
    +--------+--------+
    => signed 8-bit XXXXXXXX


### int16

signed 16-bit big-endian integer on 3 bytes
    +--------+--------+--------+
    |  0xd1  |XXXXXXXX|XXXXXXXX|
    +--------+--------+--------+
    => signed 16-bit big-endian XXXXXXXX_XXXXXXXX


Boolean
-------

### true

    +--------+
    |  0xc3  |
    +--------+

### false


    +--------+
    |  0xc2  |
    +--------+

Floating point
--------------

### float

Big endian IEEE 754 on 5 bytes

    +--------+--------+--------+--------+--------+
    |  0xca  |XXXXXXXX|XXXXXXXX|XXXXXXXX|XXXXXXXX|
    +--------+--------+--------+--------+--------+
    => big-endian IEEE 754 single precision floating point number XXXXXXXX_XXXXXXXX_XXXXXXXX_XXXXXXXX

raw bytes
---------

raw bytes up to 31 bytes.

    +--------+--------
    |101XXXXX|...N bytes
    +--------+--------
    => 000XXXXXX (=N) bytes of raw bytes.

Usage
=====

    chinookpack_parser_init
    chinookpack_parser_finish
    chinookpack_parser_execute
    chinookpack_parser_has_errors
