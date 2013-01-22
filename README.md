         _____                                                      _____                             
      __|___  |__  __   _  ____  ____   _  _____  _____  __  __  __|__   |__  ____    ______  __  __  
     |   ___|    ||  |_| ||    ||    \ | |/     \/     \|  |/ / |     |     ||    \  |   ___||  |/ /  
     |   |__     ||   _  ||    ||     \| ||     ||     ||     \ |    _|     ||     \ |   |__ |     \  
     |______|  __||__| |_||____||__/\____|\_____/\_____/|__|\__\|___|     __||__|\__\|______||__|\__\ 
        |_____|                                                    |_____|                            
          

[![Build Status](https://secure.travis-ci.org/pastjean/chinookpack.png?branch=master)](http://travis-ci.org/pastjean/chinookpack)

ChinookPack : Encoder/Decoder for a simplified [MessagePack][msgpack] serialization format

The [MessagePack specification][msgpackspec] is more declarative about the [format][msgpackspec]

[msgpack]:http://msgpack.org/
[msgpackspec]:http://wiki.msgpack.org/display/MSGPACK/Format+specification

Available types
===============

<table>
    <thead>
        <tr>
            <th>Family</th>
            <th>Type</th>
            <th>Encoded Form</th>
        </tr>
    </thead>
    <tr>
        <td rowspan="2">Boolean</td>
        <td>true</td>
        <td>`0xc3`</td>
    </tr>
    <tr>
        <td>false</td>
        <td>`0xc2`</td>
    </tr>
    <tr>
        <td rowspan="4">Integer</td>
        <td>uint8</td>
        <td> `0xcc` </td>
    </tr>
    <tr>
        <td>uint16</td>
        <td> `0xcd` </td>
    </tr>
    <tr>
        <td>int8</td>
        <td>`0xd0`</td>
    </tr>
    <tr>
        <td>int16</td>
        <td>`0xd1`</td>
    </tr>
    <tr>
        <td>Floating Point</td>
        <td>float</td>
        <td>0xca</td>
    </tr>
    <tr>
        <td>Raw bytes</td>
        <td>fix raw</td>
        <td>101XXXXX</td>
    </tr>
</table>


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

Raw bytes
---------

### fix raw

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
