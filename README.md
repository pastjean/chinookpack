         _____                                                      _____                             
      __|___  |__  __   _  ____  ____   _  _____  _____  __  __  __|__   |__  ____    ______  __  __  
     |   ___|    ||  |_| ||    ||    \ | |/     \/     \|  |/ / |     |     ||    \  |   ___||  |/ /  
     |   |__     ||   _  ||    ||     \| ||     ||     ||     \ |    _|     ||     \ |   |__ |     \  
     |______|  __||__| |_||____||__/\____|\_____/\_____/|__|\__\|___|     __||__|\__\|______||__|\__\ 
        |_____|                                                    |_____|                            
          

[![Build Status](https://secure.travis-ci.org/pastjean/fujin.png?branch=master)](http://travis-ci.org/pastjean/fujin)

ChinookPack : Encoder/Decoder for a simplified [MessagePack][msgpack] serialization format

The [MessagePack specification][msgpackspec] is more declarative about the format](msgpackspec)

[msgpack]:http://msgpack.org/
[msgpackspec]:http://wiki.msgpack.org/display/MSGPACK/Format+specification

Available types
===============

- positive fixnum
- negative fixnum
- uint8
- uint16
- int8
- int16
- float
- raw bytes


Encoding
========

positive fixnum
---------------

negative fixnum
---------------

uint8
-----

uint16
------

int8
----

int16
-----

float
-----

raw bytes
---------

Usage
=====

    chinookpack_parser_init
    chinookpack_parser_finish
    chinookpack_parser_execute
    chinookpack_parser_has_errors
