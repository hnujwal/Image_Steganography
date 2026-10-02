#include<stdio.h>
#include<string.h>
#include "decode.h"
#include "common.h"
#include "types.h"
FILE *open_all_file(DcodeInfo *decodeInfo,char *mode[])
{
    FILE *fptr = fopen(decodeInfo->stego_image_fname, mode);
    return fptr;
}
Status check_argv_file_extention(char *argv[],DcodeInfo *decodeInfo)
{
    if(argv[2]!=NULL && strcmp(strstr(argv[2],"."),".bmp")==0)
    {
        decodeInfo->stego_image_fname=argv[2];
    }
    else
    {
        printf("pleas enter the valide extention");
        return e_failure;
    }
    if(argv[3]==NULL)
    {
        decodeInfo->src_fname="secret";
    }
    else{
        decodeInfo->src_fname=strtok(argv[3],'.');
    }
}
Status check_magic_string(char *mg_str,DcodeInfo *decodeInf);
Status do_docode(DcodeInfo *decodeInfo)
{
    printf("Decoding Process Started\n");
    if(open_all_file(&decodeInfo,"rd")!=NULL)
    return e_success;
}