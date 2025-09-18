# Huffman Compressor
A C++ project implementing Huffman coding for lossless file compression and decompression.

## Features
- Compresses text and binary files using Huffman coding.
- Decompresses to restore original files.
- Tested with ~1000-word text files and images (e.g., BMP).

## How to Run
1. Install MinGW (`g++`, `mingw32-make`).
2. Clone or download this repository.
3. Navigate to the folder: `cd huffman-compressor`
4. Compile: `mingw32-make`
5. Compress: `.\huff.exe c test.txt compressed.huff`
6. Decompress: `.\huff.exe d compressed.huff output.txt`
7. Verify: `fc.exe test.txt output.txt`
