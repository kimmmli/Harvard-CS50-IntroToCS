#include <stdio.h>
#include<string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, sizeof(char), 7, infile) == 7)
    {

        //这里不能直接把buffer存plates，存的话都是一个address，放最后一个plates
        //所以plates里面要放七个不同的address，代表不同plates
        char *t=malloc(7);
        // Replace '\n' with '\0'
        buffer[6] = '\0';
        strcpy(t,buffer);

        // Save plate number in array
        plates[idx]=t;

        idx++;

    }


    for (int i = 0; i < 8; i++)
    {
            printf("%s\n", plates[i]);

    }
    fclose(infile);
}
