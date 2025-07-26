# Huffman Text Compressor and Decompressor

This C++ project implements a complete **Huffman Coding** system for lossless text compression and decompression. It encodes text into a compact binary file using frequency-based Huffman trees and restores it using the stored encoding map.

## 🔧 Features

- ✅ **Lossless Compression** using Huffman Coding
- ✅ **Min-Heap Tree Construction** for optimal binary codes
- ✅ **Binary Encoding Output** with metadata for precise decoding
- ✅ **Separate Encoding Map** for character-to-binary mapping
- ✅ **Compression Statistics** showing size reduction and savings
- ✅ **File Comparison Tool** to validate decompressed output

---

## 📁 Project Structure

- `encoder.cpp` - Compresses a text file into a binary `.bin` file and stores encoding map
- `decoder.cpp` - Decompresses encoded file using map and reconstructs the original file
- `file_compare.cpp` - Compares two files byte-by-byte to validate correctness
- `huffman.hpp` - Defines the Huffman Node, Tree structure, and utilities

---

## 🚀 How to Run

### 🔹 Step 1: Compile the components

```bash
g++ encoder.cpp -o encoder
g++ decoder.cpp -o decoder
g++ file_compare.cpp -o file_compare
