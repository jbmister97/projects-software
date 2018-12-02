#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *file = "test2.txt";
    FILE *outputFile = fopen(file, "w");
    char line[256] = {0};

    if(outputFile){
        printf("Successfully opened %s", file);
        while(fgets(line,sizeof(line),outputFile)) {
            printf("%s",line);
        }
        fprintf(outputFile,"Hello There!\nHow are you?\n");

        /* print some text */
        const char *text = "Write this to the file";
        fprintf(outputFile, "Some text: %s\n", text);

        /* print integers and floats */
        int i = 1;
        float py = 3.1415927;
        fprintf(outputFile, "Integer: %d, float: %f\n", i, py);

        /* printing single chatacters */
        char c = 'A';
        fprintf(outputFile, "A character: %c\n", c);
        fclose(outputFile);
    }
    else{
        printf("Could not open %s", file);
    }

    return 0;
}
