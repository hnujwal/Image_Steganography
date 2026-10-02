#include <stdio.h>
#include "encode.h"
#include <string.h>
#include "types.h"

int main(int argc, char *argv[])
{
    if(check_operation_type(argv)==e_encode)
    {
         printf("Encoding operation selected\n");
        EncodeInfo encInfo;
        if(read_and_validate_encode_args(argv, &encInfo)==e_success)
        {
            printf("All arguments are valid\n");
            if(do_encoding(&encInfo)==e_success)
            {
                printf("Encoding done successfully\n");
            }
            else
            {
                printf("Error in encoding\n");
            }
        }
        else
        {
            printf("Invalid arguments\n");
        }
    }
    else if(check_operation_type(argv)==e_decode)
    {
        printf("Decoding operation selected\n");
    }
    else
    {
        printf("Unsupported operation selected\n");
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

