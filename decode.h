#ifndef DECODE_H
#define DECODE_H
#include "types.h"

typedef struct _DcodeInfo
{
    char *src_fname;
    FILE *fptr_src_file;
    int ext_size;
    int file_size;

    char *stego_image_fname;
    FILE *fptr_stego_image;

}DcodeInfo;
OperationType check_operation(char *argv[]);
Status check_argv_file_extention(char *argv[],DcodeInfo *decodeInfo);
Status do_docode(DcodeInfo *decodeInfo);
FILE *open_all_file(DcodeInfo *decodeInfo,char *mode[]);
Status check_magic_string(char *mg_str,DcodeInfo *decodeInf);
#endif