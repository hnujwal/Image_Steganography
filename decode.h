#ifndef DECODE_H
#define DECODE_H
#include "types.h"

typedef struct _DcodeInfo
{
    char *stego_image_fname;
    FILE *fptr_src_file;
    char file_ext[5];
    char magic_string[5];
    uint ext_size;
    uint file_size;

    char src_fname[20];
    FILE *fptr_stego_image;

}DecodeInfo;
OperationType check_operation(char *argv[]);
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decodeInfo);
Status do_decoding(DecodeInfo *decodeInfo);
Status open_all_file_decode(DecodeInfo *decodeInfo);
Status decode_magic_string(int size,DecodeInfo *decodeInfo,char *str);
int decode_lsb_to_byte( char image_buffer[]);
Status decode_file_ext(int size,DecodeInfo *decodeInfo);
Status decode_lsb_to_size(int *size,DecodeInfo *decodeInfo);
Status decode_secret_data_form_lsb(DecodeInfo *decodeInfo);
#endif