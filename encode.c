#include <stdio.h>
#include "encode.h"
#include "common.h"
#include <string.h>
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}
uint get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);   // seek to end of file
    long size_secret_file = ftell(fptr);    // get current file pointer
    fseek(fptr, 0, SEEK_SET);  // seek back to beginning of file
    return size_secret_file;

}
/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
 Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
    {
        if(argv[2]!=NULL && strcmp(strstr(argv[2], "."), ".bmp") == 0)
        {
            encInfo->src_image_fname=argv[2];
        }
        else
        {

            printf("Invalid source image format. Only .bmp files are supported.\n");
            return e_failure;
        }
        if(argv[3]!=NULL && strcmp(strstr(argv[3], "."), ".txt") == 0)
        {
            encInfo->secret_fname=argv[3];
        }
        else
        {
            printf("Invalid secret file format. Only .txt files are supported.\n");
            return e_failure;
        }
        
        if(argv[4]==NULL)
        {
            encInfo->stego_image_fname="stego.bmp";
        }
        else
        {
            encInfo->stego_image_fname=argv[4];
        }
        return e_success;
    }
Status check_capacity(EncodeInfo *encInfo)
    {
        encInfo->image_capacity=get_image_size_for_bmp(encInfo->fptr_src_image);
        encInfo->size_secret_file=get_file_size(encInfo->fptr_secret);
        if(encInfo->image_capacity>(54+(2+4+4+4+encInfo->size_secret_file)*8))
        {
            return e_success;
        }
        else
        {
            printf("Error: Insufficient capacity in source image to encode secret file\n");
            return e_failure;
        }
    }
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
        char buffer[54];
        fseek(fptr_src_image, 0, SEEK_SET);
        fread(buffer, 54, 1, fptr_src_image);
        fwrite(buffer, 54, 1, fptr_dest_image);
        return e_success;
}
Status encode_byte_to_lsb(char data, char *image_buffer)
    {
        uint mask=1<<7;
        for(int i=0;i<8;i++)
        {
            image_buffer[i]= (image_buffer[i] & 0xFE) | ((data & mask) >> (7-i));
            mask >>= 1;
        }
        return e_success;
    }
Status encode_data_to_image(char *data, int size, EncodeInfo *encInfo)
    {
        for(int i=0;i<size;i++)
        {
            fread(&encInfo->image_data, 8, 1, encInfo->fptr_src_image);
            encode_byte_to_lsb(data[i], encInfo->image_data);
            fwrite(encInfo->image_data , 8, 1, encInfo->fptr_stego_image);
        }
        return e_success;
    }
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo) 
    {
        if(encode_data_to_image((char *)magic_string, strlen(magic_string), encInfo )==e_success)
        {
            return e_success;
        }
        else
        {
            return e_failure;
        }
    }
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    if(encode_data_to_image((char *)file_extn,strlen(file_extn),encInfo)==e_success);
    return e_success;
    return e_failure;
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char image_buffer[32];
    fread(image_buffer, 32, 1, encInfo->fptr_src_image);
    unsigned mask=1<<31;
    for(int i=0;i<31;i++)
    {
        image_buffer[i]=(image_buffer[i] & 0xFE) | (size & mask) >> (31-i);
        mask >>= 1;
    }
    fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    encode_secret_file_extn_size(file_size,encInfo);
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char ch;
    fseek(encInfo->fptr_secret, 0, SEEK_SET);
    for(int i=0;i<encInfo->size_secret_file;i++)
    {
    fread(&ch,1,sizeof(char),encInfo->fptr_secret);
    fread(&encInfo->image_data,8,1,encInfo->fptr_src_image);
    encode_byte_to_lsb(ch,encInfo->image_data);
    fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_stego)
{
    char ch;
    while(fread(&ch,1,1,fptr_src)>0)
    {
        fwrite(&ch, 1, 1,fptr_stego);
    }
    return e_success;
}
Status do_encoding(EncodeInfo *encInfo)
    {
        printf("Encoding in progress...\n");
        if(open_files(encInfo)==e_success)
        {
            printf("All files opened successfully\n");
            if(check_capacity(encInfo)==e_success)
            {
                printf("Capacity check passed\n");
                if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
                {
                    printf("BMP header copied successfully\n");
                    if(encode_magic_string(MAGIC_STRING, encInfo)==e_success)
                    {
                        printf("Magic string encoded successfully\n");
                        if(encode_secret_file_extn_size(strlen(FILE_EXTN),encInfo)==e_success)
                        {
                            printf("Secret file extension size encoded successfully\n");
                            if(encode_secret_file_extn(FILE_EXTN,encInfo)==e_success)
                            {
                                printf("Secret file extension encoded successfully\n");
                                if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
                                {
                                    printf("Secret file size encoded successfully\n");
                                    if(encode_secret_file_data(encInfo)==e_success)
                                    {
                                        printf("Secret file data encoded successfully\n");
                                        if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
                                        {
                                            printf("Remaining image data copied successfully\n");
                                            return e_success;
                                        }
                                        else
                                        {
                                            printf("Error in copying remaining image data\n");
                                            return e_failure;
                                        }
                                    }
                                    else
                                    {
                                        printf("Error in encoding secret file data\n");
                                        return e_failure;
                                    }
                                }
                                else
                                {
                                    printf("Error in encoding secret file size\n");
                                    return e_failure;
                                }
                            }
                            else
                            {
                                printf("Error in encoding secret file extension\n");
                                return e_failure;
                            }
                        }
                        else
                        {
                            printf("Error in encoding secret file extension size\n");
                            return e_failure;
                        }
                        
                        
                    }
                    else
                    {
                        printf("Error in encoding magic string\n");
                        return e_failure;
                    }
                
                }
                else
                {
                    printf("Error in copying BMP header\n");
                    return e_failure;
                }
            }
        }
        else
        {
            printf("Error in opening files\n");
            return e_failure;
        }
        return e_success;
    }
