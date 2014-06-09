#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

const char* getfield(char* line, int num);

int main (void)
{
    int len;
    float fuelcost = 0,
          totalgal = 0,
          sodm = 0,
          fodm;
    setlocale(LC_NUMERIC, "");
    char file_name[25];
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

   char line[1024];
    while (fgets(line, 1024, fp))
    {
        char* tmp = strdup(line);
        if (sodm == 0) sodm = atof(getfield(tmp, 2));
        free(tmp);
        tmp = strdup(line);
        fodm = atof(getfield(tmp, 2));
        free(tmp);
        tmp = strdup(line);
        totalgal += atof(getfield(tmp, 3));
        free(tmp);
        tmp = strdup(line);
        fuelcost += atof(getfield(tmp, 4));

        // NOTE strtok clobbers tmp
        free(tmp);
    }
    printf("Total Gallons Used is %'.2f gal.\n", totalgal);
    printf("Total Fuel Cost is $%'.2f\n", fuelcost);
    printf("Averge dollar cost per gallon is $%'.2f\n", (fuelcost / totalgal));
    printf("Starting Odometer is %'.0f and Final Odometer is %'.0f\n", sodm, fodm);
    printf("Miles per gallon is %'.2f\n", ((fodm - sodm) / totalgal));
      //printf("%c",ch);

    fclose(fp);

return 0;
}

const char* getfield(char* line, int num)
{
    const char* token;
    for (token = strtok(line, ",");
            token && *token;
            token = strtok(NULL, ",\n"))
    {
        if (!--num)
            return token;
    }
    return NULL;
}
