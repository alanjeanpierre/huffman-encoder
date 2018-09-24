# huffman-encoder
Implementation of a Huffman encoding algorithm. 
A Huffman code reduces filesizes by replacing source data with encoded representations. 
These codes are chosen based on the frequency of each datapoint. 
Ideally, more common characters have a representation shorter than their original length.


# Usage
Compilation: Use the included makefile or compile with `-std=c++11` or greater.

To compress: `./huffman -c <output> <input>`

To decompress: `./huffman -d <output> <input>` 
