#include<stdio.h>
#include "decode.h"
int main(argc,argv)
{
    if(check_operation(argv)==e_decode)
    {
        printf("decoding started.......\n");
        DcodeInfo decodeInfo;
        if(check_argv_file_extention(argv,&decodeInfo)==e_success)
        {
            printf("file extention is valid");
            if(do_docode(&decodeInfo)==e_success)
            {
                printf("decoded successfully");
            }
            else
            {
                printf("failed to decode");
            }
        }
        else
        {
            printf("Error : file extention is invalid");
        }
    }
    else{
        printf("unsupported operation");
    }
}
OperationType check_operation(char *argv[])
{
    if(strcmp(argv[1],"-d")==0)
    {
        return e_decode;
    }
    return e_unsupported;
}