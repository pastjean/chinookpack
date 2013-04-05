         _____                                                      _____                             
      __|___  |__  __   _  ____  ____   _  _____  _____  __  __  __|__   |__  ____    ______  __  __  
     |   ___|    ||  |_| ||    ||    \ | |/     \/     \|  |/ / |     |     ||    \  |   ___||  |/ /  
     |   |__     ||   _  ||    ||     \| ||     ||     ||     \ |    _|     ||     \ |   |__ |     \  
     |______|  __||__| |_||____||__/\____|\_____/\_____/|__|\__\|___|     __||__|\__\|______||__|\__\ 
        |_____|                                                    |_____|                            
          

[![Build Status](https://travis-ci.org/pastjean/chinookpack.png?branch=master)](https://travis-ci.org/pastjean/chinookpack)

ChinookPack : Encoder/Decoder for a simplified [MessagePack][msgpack] serialization format

The [MessagePack specification][msgpackspec] is more declarative about the [format][msgpackspec]

[msgpack]:http://msgpack.org/
[msgpackspec]:http://wiki.msgpack.org/display/MSGPACK/Format+specification


Disclaimer : *This project is a learning project primarily to learn and try to gain performance on a microcontroller, consider using the real msgpack implementation which is more tested. A large part of the code was taken and adapted from msgpack.*

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
        <td><code>0xcc??</code></td>
    </tr>
    <tr>
        <td>uint16</td>
        <td><code>0xcd????</code></td>
    </tr>
    <tr>
        <td>int8</td>
        <td><code>0xd0??</code></td>
    </tr>
    <tr>
        <td>int16</td>
        <td><code>0xd1????</code></td>
    </tr>
    <tr>
        <th>Floating Point</th>
        <td>float</td>
        <td><code>0xca????</code></td>
    </tr>
    <tr>
        <th>Raw bytes</th>
        <td>fix raw</td>
        <td><code>101XXXXX</code>(<code>X</code> is length in bytes)</td>
    </tr>
</table>


Usage
=====

Encode Data
-----------

    char* dataArray[10];
    chinookpack_fbuffer buf;
    chinookpack_packer pk;
    
    // Initialize everything
    chinookpack_fbuffer_init(&bug,dataArray,10);
    chinookpack_packer_init(&pk,buf,chinookpack_fbuffer_write);

    // And now encode
    chinookpack_pack_uint8(&pk,127);
