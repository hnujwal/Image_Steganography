#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include <string.h>
#include "types.h"

int main(int argc, char *argv[])
{
    if(check_operation_type(argv)==e_encode)
    {
         printf("INFO: Encoding operation selected\n");
        EncodeInfo encInfo;
        if(read_and_validate_encode_args(argv, &encInfo)==e_success)
        {
            printf("INFO: All arguments are valid\n");
            if(do_encoding(&encInfo)==e_success)
            {
                printf("INFO: Encoding done successfully\n");
            }
            else
            {
                printf("ERROR: Error in encoding\n");
            }
        }
        else
        {
            printf("ERROR: Invalid arguments\n");
        }
    }
    else if(check_operation_type(argv)==e_decode)
    {
        printf("INFO: Decoding operation selected\n");
        DecodeInfo decodeInfo;
        if(read_and_validate_decode_args(argv,&decodeInfo)==e_success)
        {
            printf("INFO: All arguments are valid\n");
            if(do_decoding (&decodeInfo)==e_success)
            {
                printf("INFO: Decoding done successfully\n");
            }
            else
            {
                printf("ERROR: Error in decoding\n");
            }
        }
    }
    else
    {
        printf("ERROR: Unsupported operation selected\n");
        printf("-------------------------------------------------------------------\n");
        printf("TO encode: ./a.out -e <source_image> <secret_file> <stego_image>\n");
        printf("TO decode: ./a.out -d <stego_image> <output_file>\n");
        printf("-------------------------------------------------------------------\n");
    }
    return 0;
}
OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-e")==0)
    {
        return e_encode;
    }
    else if(strcmp(argv[1],"-d")==0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}

