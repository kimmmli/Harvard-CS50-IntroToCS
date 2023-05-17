#include <stdio.h>
#include <stdlib.h>
#define BYTE 1

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong number of input.\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    unsigned char* block = malloc(BYTE * 512);
    FILE *output=NULL;
    // Remember here, we cannot write the below code
    // char* filename[8]
    // have to write this
    //因为filename需要一个char * 不要规定了[8]
    char* filename=malloc(BYTE * 8);



    // iterate over infile
    int i=0;
    while (fread(block, sizeof(block), 1, inptr) !=0)
    {
        //这里0xff不要加‘’，就是单纯表示hexiedcial number
        if (block[0]==0xff && block[1]==0xd8 && block[2]==0xff && (block[3] & 0xf0)== 0xe0)
        {

            sprintf(filename, "%03i.jpg",i);
            output=fopen(filename, "w");
            i++;

        }
        if (output!=NULL)
        {
            fwrite(block, sizeof(block),1,output);
        }

    }
    free(filename);
    free(block);
    fclose(output);
    fclose(inptr);


}