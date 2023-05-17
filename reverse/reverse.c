#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc!=3)
    {
        printf("Wrong input numbers.\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2

    FILE *input=fopen(argv[1],"r");
    if (input==NULL)
    {
        printf("Not valid input.\n");
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header,sizeof(header), 1,input);

    printf("%i\n",check_format(header));

    // Open output file for writing
    // TODO #5
    FILE *output=fopen(argv[2],"w");
    if (output==NULL)
    {
        printf("Not valid output.\n");
    }

    // Write header to file
    // TODO #6
    fwrite(&header,sizeof(header),1, output);


    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size=get_block_size(header);

    printf("The block size is %i.\n",get_block_size(header));

    // Write reversed audio to file
    // TODO #8
    char *buffer = malloc(block_size * sizeof(char));
    if (buffer == NULL)
    {
        printf("no memory location");
        return 1;
    }

    // get the size of the input file
    fseek(input, 0, SEEK_END);
    long int infile_size = ftell(input);
    printf("file_size: %li\n", infile_size);

    // iterate through the input file audio data
    for (long int i = infile_size; i >= 0; i -= block_size)
    {
        // move the file indicator to the start
        fseek(input, i, SEEK_SET);

        // read from inptr each size
        fread(buffer, sizeof(char), block_size, input);

        // write in outfile
        fwrite(buffer, sizeof(char), block_size, output);
    }

    // free
    free(buffer);

    // close files:
    fclose(input);
    fclose(output);

    return 0;

}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0]=='W'&&header.format[1]=='A'&&header.format[2]=='V'&&header.format[3]=='E')
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int blocksize;
    blocksize=(header.bitsPerSample/8) * (header.numChannels);
    return blocksize;
}