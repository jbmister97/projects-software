#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *inputFile;
    char *file;
    char line[256];
    char *identifier;

    if(argc == 1) {
        printf("Not enough paramgters\n");
        return 1;
    }
    else if(argc > 3) {
        printf("Too many parameters\n");
        return 1;
    }

    file = argv[1];
    if(strcmp(file, "-h") == 0) {
        printf("Help Information\nFormat: ./read_c Arg1 Arg1\n");
        printf("Arg1: name of file to open\nArg2: identifier to search for and print out lines that have it\n");
        return 0;
    }

    if(argc == 3) {identifier = argv[2];}

    inputFile = fopen(file, "r");

    if(inputFile) {
        printf("Successfully opened %s\n", file);

        while(fgets(line,sizeof(line),inputFile)) {
            if(argc == 3 && strstr(line,identifier) != NULL) {
                printf("%s",line);
            }
            else if(argc == 2) {printf("%s",line);}
        }

        if(fclose(inputFile) == 0) {printf("Successfully closed %s\n", file);}
        else {printf("Could not close %s\n", file);}
    }
    else {
        printf("Could not open %s\n", file);
        return 1;
    }

    return 0;
}
