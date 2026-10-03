# Image Steganography

A C program that hides secret text files inside BMP images using the LSB (Least Significant Bit) technique.

## How It Works

- **Encoding**: Hides a secret `.txt` file inside a `.bmp` image by replacing the LSB of each pixel byte with bits from the secret data.
- **Decoding**: Extracts the hidden secret data from a stego BMP image and writes it back to a file.

A magic string `#*` is embedded during encoding to verify the image during decoding.

## Project Structure

```
├── common.h        - Magic string and file extension definitions
├── types.h         - User defined types (Status, OperationType)
├── encode.h        - Encoding function prototypes and EncodeInfo struct
├── encode.c        - Encoding implementation
├── decode.h        - Decoding function prototypes and DecodeInfo struct
├── decode.c        - Decoding implementation
└── test_encode.c   - Main entry point for encode/decode operations
```

## Build

```bash
gcc test_encode.c encode.c decode.c -o a.out
```

## Usage

**Encoding** — Hide a secret file inside a BMP image:
```bash
./a.out -e <source_image.bmp> <secret_file.txt> <stego_image.bmp>
```

**Decoding** — Extract the hidden secret from a stego image:
```bash
./a.out -d <stego_image.bmp> <output_file>
```

### Example

```bash
./a.out -e beautiful.bmp secret.txt stego.bmp
./a.out -d stego.bmp output
```

## Requirements

- GCC compiler
- A `.bmp` image file as the source
- A `.txt` file as the secret file to hide
