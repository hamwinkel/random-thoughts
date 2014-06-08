#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    int len;
    char ch, file_name[25];
    FILE *fp;
    system("ls");
    printf("Enter the name of file you wish to open...\n");
    fgets(file_name, 255, stdin);

    /* Check for '\n' fopen returns NULL unless replaced with 0 */
    len = strlen(file_name);
    if (file_name[len-1] == '\n')
    file_name[len-1] = 0;

    fp = fopen(file_name,"r"); // read mode

    if( fp == NULL )
    {
      perror("Error while opening the file.\n");
      printf("%s", file_name);
      exit(EXIT_FAILURE);
    }

    printf("The contents of %s file are :\n", file_name);

    while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);

    fclose(fp);

return 0;
}
