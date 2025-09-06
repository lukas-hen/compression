# Huffman Compression in C

This project implements Huffman coding in C for compressing and decompressing files. Huffman coding is a lossless data compression algorithm that produces variable-length codes based on the frequency of characters in the input data.

## File Structure

The project is organized as follows:

```plaintext
huffman-compression-in-c/
├── bin/                 # Directory for compiled binary/executable files
├── include/             # Directory for header files
├── obj/                 # Directory for compiled object files
├── resources/           # Directory for example inputs, compressed files, and outputs
└── src/                 # Directory for source code files
```

All build artifacts (e.g., object files and the final binary) are generated into the `bin` and `obj` directories respectively.

---

## Requirements
- **clang** or any other C compiler (default: `clang` in the provided `Makefile`)
- A terminal or command-line environment

---

## Installation
### Build the Project
To compile the project, simply run:
```bash
make
```
This will create all necessary directories (`bin/`, `obj/`) and output the final executable to `bin/`.

### Install Globally
To install the program to your system (e.g., in `/usr/local/bin`):
```bash
make install
```
Once installed, the program can be accessed globally using the command:
```bash
compr
```
For example:
```bash
compr ./resources/poem.txt
```

### Uninstall
To remove the installed binary from your system:
```bash
make uninstall
```

---

## Usage
The program provides two main functionalities: compression and decompression.

### Compress a File
To compress a file:
```bash
bin/compr -c resources/input.txt resources/compressed.huff
```
- `resources/poem.txt`: The file to be compressed.
- `resources/compressed.huff`: The file containing the compressed binary output.

### Decompress a File
To decompress a file:
```bash
bin/compr -d resources/compressed.huff resources/output.txt
```
- `resources/compressed.huff`: The compressed file to decompress.
- `resources/output.txt`: The output file matching the original file.

### Debugging
Compile the program with debug symbols for troubleshooting:
```bash
make debug
```

### Format Source Code
To format all source (`.c`) and header (`.h`) files using `clang-format`:
```bash
make format
```

### Cleanup
To clean all build artifacts (binaries and object files):
```bash
make clean
```

---

## Examples
### Example Compression
Input file (`resources/poem.txt`):
```
hello huffman
```

Command:
```bash
bin/compr -c resources/poem.txt resources/compressed.huff
```

Outputs `resources/compressed.huff`

### Example Decompression
Command:
```bash
bin/compr -d resources/compressed.huff resources/output.txt
```

Output (`resources/output.txt`):
```
hello huffman
```

---

## Build Commands Overview

| Command            | Description                                                  |
|--------------------|--------------------------------------------------------------|
| `make`             | Compiles the project and creates the output binary.          |
| `make debug`       | Compiles the program with debug symbols.                     |
| `make format`      | Formats all `.c` and `.h` files using `clang-format`.         |
| `make clean`       | Removes all build artifacts (binary and object files).       |
| `make install`     | Copies the binary to `/usr/local/bin` for global access.     |
| `make uninstall`   | Removes the binary from `/usr/local/bin`.                    |

---

## Algorithm Overview

The implementation follows these steps:
1. **Frequency Analysis**: Analyze the frequency of each character in the input file.
2. **Build Huffman Tree**: Use a priority queue to build a binary tree, ensuring that low-frequency characters have longer paths than high-frequency characters.
3. **Generate Huffman Codes**: Assign binary codes (a sequence of 0s and 1s) to each character based on the structure of the Huffman Tree.
4. **Compression**: Replace the characters in the input file with their binary codes to create a compressed file.
5. **Decompression**: Use the Huffman Tree stored with the compressed file to decode the binary data back into the original content.

---

## License
This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute this code.

---

Feel free to reach out if you encounter any issues or have suggestions for improvements. 🚀