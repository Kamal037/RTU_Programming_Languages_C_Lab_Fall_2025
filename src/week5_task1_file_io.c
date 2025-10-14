// week5_task1_file_io.c
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// TODO: Fill in the missing parts marked below.a

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char filename[100] = "data.txt";
    char line[256];
    int line_count = 0;

    // TODO: 1. Open file for writing (mode = "w")
     fp = fopen(filename, "w");
    // TODO: 2. Check if file opened successfully
     if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // TODO: 3. Write 2–3 lines of text to the file using fprintf()
    fprintf(fp, "This is the first line.\n");
    fprintf(fp, "This is the second line.\n");
    fprintf(fp, "This is the third line.\n");

    // TODO: 4. Close the file
 fclose(fp);

    // TODO: 5. Open file again for reading (mode = "r")
    fp = fopen(filename, "r"); if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
     printf("\nContents of %s:\n", filename);
    // TODO: 6. Use fgets() in a loop to read and print each line to the console
 while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        line_count++;
    }
    // TODO: 7. Close the file
    fclose(fp);

    // BONUS: ask user for filename instead of using default "data.txt"
      printf("Enter filename: ");
    scanf("%99s", filename);

    // BONUS: count number of lines read
    printf("\nTotal number of lines read: %d\n", line_count);

    return 0;
}
