#include<stdio.h>
#include "decode.h"
#include "common.h"
#include "types.h"
#include<string.h>
Status open_all_file_decode(DecodeInfo *decodeInfo)
{
    decodeInfo->fptr_stego_image = fopen(decodeInfo->stego_image_fname, "rb");
    if (decodeInfo->fptr_stego_image == NULL)
    {
        return e_failure;
    }
    return e_success;
}
int decode_lsb_to_byte(char image_buffer[])
{
    int ch=0;
    for(int i=0;i<8;i++)
    {
        ch|=(image_buffer[i]&01)<<7-i;
    }
    return ch;
}
Status decode_magic_string(int size,DecodeInfo *decodeInfo,char *str)
{
    char image_buffer[8];
    for(int i=0;i<size;i++)
    {
    fread(image_buffer,8,1,decodeInfo->fptr_stego_image);
    str[i]=decode_lsb_to_byte(image_buffer);
    }
    str[size]='\0';
    printf("INFO: Decoded string = %s\n",str);
    
    return e_success;
}
Status decode_file_ext(int size, DecodeInfo *decodeInfo)
{
    decode_magic_string(size,decodeInfo,decodeInfo->file_ext);
    if(strcat(decodeInfo->src_fname,decodeInfo->file_ext)==NULL)
    {
        return e_failure;
    }
    return e_success;
}
Status decode_lsb_to_size(int *size,DecodeInfo *decodeInfo)
{
    *size=0;
    char image_buffer[32];
    fread(image_buffer,32,1,decodeInfo->fptr_stego_image);
    for(int i=0;i<31;i++)
    {
        *size|=(image_buffer[i]&0x01)<<31-i;
    }
    if(*size!=0)
    {
    printf("INFO: Decoded size = %d\n", *size);
    return e_success;
    }
    return e_failure;
}
Status decode_secret_data_form_lsb(DecodeInfo *decodeInfo)
{
   decodeInfo->fptr_src_file=fopen(decodeInfo->src_fname,"wb");
   if(decodeInfo->fptr_src_file!=NULL) 
   {
    char data[decodeInfo->file_size];
    char image_buffer[8];
    for(int i=0;i<decodeInfo->file_size;i++)
    {
    fread(image_buffer,8,sizeof(char),decodeInfo->fptr_stego_image);
    data[i]=decode_lsb_to_byte(image_buffer);
    }
    data[decodeInfo->file_size]='\0';
    printf("INFO: Decoded data = %s\n",data);
    fwrite(data,1,decodeInfo->file_size,decodeInfo->fptr_src_file);
    return e_success;
   }
}
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decodeInfo)
{
    if(argv[1]!=NULL && strcmp(strstr(argv[2],"."),".bmp")==0)
    {
        decodeInfo->stego_image_fname=argv[2];
    }
    else
    {
        printf("ERROR: pleas enter the valide extention\n");
        return e_failure;
    }
    if(argv[2]==NULL)
    {
        strcpy(decodeInfo->src_fname,"decode_secret");
    }
    else{
        strcpy(decodeInfo->src_fname,strtok(argv[3],"."));
    }
    return e_success;
}
Status do_decoding(DecodeInfo *decodeInfo)
{
    printf("INFO: Decoding Process Started\n");
    if(open_all_file_decode(decodeInfo)==e_success)
    {
        printf("INFO: %s file open successfully\n",decodeInfo->stego_image_fname);
         fseek(decodeInfo->fptr_stego_image,54,SEEK_SET);
        if(decode_magic_string(strlen(MAGIC_STRING),decodeInfo,decodeInfo->magic_string)==e_success)
        {
            if(strcmp(decodeInfo->magic_string,MAGIC_STRING)==0)
            {
            printf("INFO: Magic string found\n");
            if(decode_lsb_to_size(&decodeInfo->ext_size,decodeInfo)==e_success)
            {
                printf("INFO: extention size decoded successfully\n");
                if(decode_file_ext(decodeInfo->ext_size, decodeInfo)==e_success)
                {
                    printf("INFO: extention decoded successfully\n");
                    if(decode_lsb_to_size(&decodeInfo->file_size,decodeInfo)==e_success)
                    {
                        printf("INFO: Secret file size decode successfully\n");
                        if (decode_secret_data_form_lsb(decodeInfo)==e_success)
                        {
                            printf("INFO: decode completed\n");
                        }
                        
                    }
                    else
                    {
                        printf("ERROR: Unable to decode secret file size\n");
                        return e_failure;
                    }
                }
                else
                {
                    printf("ERROR: failed to decode extention\n");
                }
            }
            else
            {
                printf("ERROR: failed to decode extention size\n");
            }
            }
            else
            {
                printf("ERROR: Magic string not found\n");
                return e_failure;
            }
        }
    }
    else
    {
        printf("ERROR: failed to open %s file\n",decodeInfo->stego_image_fname);
        return e_failure;
    }
    return e_success;
}