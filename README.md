# Image Steganography

A C-based steganography project that hides a secret text file inside a BMP image using the Least Significant Bit (LSB) technique. The idea is to embed hidden data into the pixel bytes of an image without noticeably changing the image to the human eye.

This project demonstrates how digital data can be stored inside image files using bit-level manipulation in C. It includes both encoding and decoding logic, where the program can hide a `.txt` file in a `.bmp` image and later recover it safely.

## What This Project Does

This project is built to perform two main operations:

- Encoding: takes a source BMP image and a secret text file, embeds the secret data into the image, and saves the result as a stego image.
- Decoding: reads a stego BMP image, extracts the hidden data, and restores the original secret file.

The program stores a special marker string, `#*`, in the image to identify whether the image contains hidden data and to validate the decoding process.

## Why This Project Is Useful

Steganography is different from encryption. Encryption makes data unreadable, while steganography hides the existence of the data itself. This project shows how messages can be hidden inside ordinary image files so they appear harmless and unmodified.

Applications of this concept include:

- watermarking digital media
- covert communication
- secret file transfer inside images
- learning low-level bit manipulation in C

## How the Encoding Process Works

The project uses the LSB method, which modifies the least significant bit of selected image bytes to store hidden data bits.

### Step-by-step flow

1. Open the source BMP image and the secret text file.
2. Check whether the image has enough space to store the hidden data.
3. Copy the BMP header to the output image so the file remains a valid BMP.
4. Embed a magic string `#*` to mark the image as stego.
5. Store the length of the hidden file extension.
6. Encode the file extension (for example, `.txt`).
7. Store the size of the secret file.
8. Embed the secret file contents bit by bit by replacing the LSB of selected image bytes.
9. Copy the remaining image data unchanged.
10. Save the final stego image.

Because only the least significant bit of each byte changes, the visual difference in the image is usually negligible.

## How the Decoding Process Works

The decoder reads the stego image and reverses the same process.

### Step-by-step flow

1. Open the stego BMP image.
2. Skip the BMP header.
3. Read the magic string `#*` to verify the image contains hidden data.
4. Extract the size of the file extension.
5. Decode the file extension.
6. Extract the secret file size.
7. Recover the secret file data using the same LSB technique.
8. Save the extracted data into a new output file.

This ensures the hidden file is reconstructed correctly without needing to know the original image content.

## Project Structure

```text
├── common.h        - Contains shared constants like the magic string and file extension
├── types.h         - Defines custom data types such as Status and OperationType
├── encode.h        - Function prototypes and structures for encoding
├── encode.c        - Encoding logic and BMP manipulation
├── decode.h        - Function prototypes and structures for decoding
├── decode.c        - Decoding logic and LSB extraction
├── test_encode.c   - Main entry point for running encode/decode operations
├── README.md       - Project documentation
└── sample files    - BMP input and text secret used during testing
```

## Main Topics / Concepts Used in This Project

The following are the main topics and concepts used in this project:

- C Programming
  - Functions and modular design
  - File handling using `fopen`, `fread`, `fwrite`, `fseek`, `ftell`
  - Arrays and string handling
  - Pointers and memory operations

- Bit Manipulation
  - Using bit masks to modify individual bits
  - LSB encoding and extraction
  - Shifting bits for data packing and unpacking

- Steganography
  - Hidden message embedding
  - Secret data storage inside image pixels
  - Verification using a magic string

- BMP Image Structure
  - Reading BMP headers
  - Understanding image data layout
  - Copying header information to the output file

- File I/O and Data Encoding
  - Reading secret files
  - Writing output files
  - Handling file sizes and extensions

- Data Validation and Error Handling
  - Checking file existence
  - Validating input extensions
  - Verifying capacity before embedding data
  - Handling invalid operations and file errors

- Structures and Enumerations
  - `Status` enum for success/failure states
  - `OperationType` enum for encode/decode selection
  - Structured data definitions for encoding and decoding operations

- Computer Graphics Basics
  - Pixel data representation
  - Image byte-level modifications
  - Least significant bit-based data hiding

- Software Design
  - Separation of responsibilities into encode/decode modules
  - Reusable helper functions
  - Clear flow for operations with logs and validation

## Build

Compile the project with GCC:

```bash
gcc test_encode.c encode.c decode.c -o a.out
```

## Usage

### Encoding

Hide a secret text file inside a BMP image:

```bash
./a.out -e <source_image.bmp> <secret_file.txt> <stego_image.bmp>
```

### Decoding

Extract the hidden data from a stego BMP image:

```bash
./a.out -d <stego_image.bmp> <output_file>
```

## Example

```bash
./a.out -e beautiful.bmp secret.txt stego.bmp
./a.out -d stego.bmp output
```

This means:

- `beautiful.bmp` is the original image
- `secret.txt` is the secret file to hide
- `stego.bmp` is the output image with hidden data
- `output` is the recovered secret file after decoding

## Requirements

- GCC compiler
- A valid `.bmp` source image
- A secret `.txt` file
- Basic understanding of C programming and file handling

## Limitations

This project is designed as a learning project and has some practical limitations:

- It only supports `.bmp` image files.
- It only supports text file data (`.txt`).
- It is not a secure encryption method.
- Hidden data can be damaged if the stego image is compressed or manipulated heavily.
- It is not suitable for large files unless the image has enough capacity.

## Summary

This project combines C programming, binary data processing, image handling, and steganography to hide text inside BMP images. It is a strong example of how low-level computer science concepts like bit manipulation and file I/O can be applied to create a practical and interesting real-world application.

In short, this project teaches:

- how BMP image files work
- how textual data can be represented in binary
- how LSB replacement can store secret information
- how to reverse the process during decoding
- how to build a full C project with modular functions and validation

## Keywords / Topics Covered

- Steganography
- LSB Technique
- BMP Files
- C Programming
- File Handling
- Bitwise Operations
- Binary Data
- Image Processing
- Data Hiding
- Software Project Development

If you want, I can also improve this README further by adding a small flowchart, a diagram of the encoding/decoding algorithm, or a more professional project explanation for GitHub.

