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

The CAN Protocol
================

Definition of our can data format

### Fields

    {
      can id, // ID of the logical device, a different id is used to set or get a value
      can length, // The length of the data field
      data field // The data encoded with chinookpack
    }

Available types
===============

<table>
    <thead>
        <tr>
            <th></th>
            <th>Type</th>
            <th>Encoded Form</th>
        </tr>
    </thead>
    <tr>
        <th rowspan="2">Boolean</th>
        <td>true</td>
        <td><code>0xc3</code></td>
    </tr>
    <tr>
        <td>false</td>
        <td><code>0xc2</code></td>
    </tr>
    <tr>
        <th rowspan="4">Integer</th>
        <td>uint8</td>
        <td><code>0xcc</code></td>
    </tr>
    <tr>
        <td>uint16</td>
        <td><code>0xcd</code></td>
    </tr>
    <tr>
        <td>int8</td>
        <td><code>0xd0</code></td>
    </tr>
    <tr>
        <td>int16</td>
        <td><code>0xd1</code></td>
    </tr>
    <tr>
        <th>Floating Point</th>
        <td>float</td>
        <td><code>0xca</code></td>
    </tr>
    <tr>
        <th>Raw bytes</th>
        <td>fix raw</td>
        <td><code>101XXXXX</code></td>
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
