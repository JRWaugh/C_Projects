#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 50

int read_number();

int main() {
    FILE *fp;
    char filename[STR_LEN];
    char *data;
    long file_size;
    int offset = 0, amount = 0;
    do {
        printf("Enter name of file to read: ");
        fgets(filename, STR_LEN, stdin);
        if (filename[strlen(filename) - 1] == '\n')
            filename[strlen(filename) - 1] = '\0';

        fp = fopen(filename, "rb");

        if(!fp)
            printf("File could not be found.");
    } while (!fp);

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    data = malloc(file_size * sizeof(char));
    fread(data, sizeof(char), file_size, fp);
    fclose(fp);
 
    printf("File Size: %ld Bytes\n", file_size);
    do {
        printf("Enter offset (0 - %ld): ", file_size - 1);
        offset = read_number();
        if(offset < 0 || offset > file_size)
            printf("Input out of range.\n");
    } while(offset < 0 || offset > file_size);

    do {
        printf("Enter number of bytes to remove: ");
        amount = read_number();
        if(amount + offset > file_size)
            printf("Sum of starting byte and amount to remove exceeds data.\n");
        else if(amount < 0)
            printf("Error. Enter positive value.\n");
    } while (amount + offset > file_size || amount < 0);
    
    fp = fopen(filename, "wb");
    if(!fp){ //just in case this somehow happens
        printf("Error making changes to file.\n");
        return 0;
    }

    fwrite(data, sizeof(char), offset, fp);
    data += offset + amount;
    fwrite(data, sizeof(char), (file_size - offset - amount), fp);
    fclose(fp);
}

int read_number() {
    int number = 0;
    char input[STR_LEN];
    fgets(input, STR_LEN, stdin);
    sscanf(input, "%d", &number);
    return number;
}