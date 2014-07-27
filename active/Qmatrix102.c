/*  Qmatrix.C  Vehicle Analysis  v1.02 	-by Hamal and George */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

const char *getfield(char *line, int num);


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

    system("dir *.csv");
    printf("\nEnter the name of file you wish to open...\n");
    fgets(file_name, 255, stdin);

    /* Test the filename for '\n' -- fopen(below,) returns NULL unless \n is replaced with 0. */
    len = strlen(file_name);
    if(file_name[len-1] == '\n')
         file_name[len-1] = 0;

    fp = fopen(file_name,"r"); 		// file open "r", read mode

    if( fp == NULL ) {
         perror("\nError while opening the file.\n");
         printf("%s\n", file_name);
         exit(EXIT_FAILURE);
    }

    printf("\nThe contents of %s file are:\n", file_name);

    char line[1024], *tmp, 
         sDay[15], fDay[15];
    len = 0;
    while(fgets(line, 1024, fp)) {
         len++;
         tmp = strdup(line);
         if(len == 2) strcpy(sDay, getfield(tmp, 1)); 	// collect start date (as string)
         free(tmp);
         tmp = strdup(line);
         strcpy(fDay, getfield(tmp, 1)); 		// collect final date (as string)
         free(tmp);
         tmp = strdup(line);
         if(sodm == 0) sodm = atof(getfield(tmp, 2)); 	// collect start odometer
         free(tmp);
         tmp = strdup(line);
         fodm = atof(getfield(tmp, 2)); 		// collect final odometer
         free(tmp);
         tmp = strdup(line);
         totalgal += atof(getfield(tmp, 3)); 		// sum gallons of fuel
         free(tmp);
         tmp = strdup(line);
         fuelcost += atof(getfield(tmp, 4)); 		// sum fuel cost$
         free(tmp); 	// NOTE strtok(,) clobbers tmp
    }

    printf("\nsDay = %s \t fDay = %s\n\n", sDay, fDay);

    printf("Starting Odometer = %.0f; Final Odometer = %.0f miles\n", sodm, fodm);
    printf("Total Gallons Used       = %.2f\n", totalgal);
    printf("Total Fuel Cost          = $%.2f\n", fuelcost);
    printf("Average cost per gallon  = $%.2f\n", (fuelcost / totalgal));
    printf("Miles driven this period = %.0f\n", (fodm - sodm));
    printf("Miles per gallon         = %.2f\n", ((fodm - sodm) / totalgal));
    printf("Miles driven on each $1  = %.2f\n", ((fodm - sodm) / fuelcost));

    fclose(fp); 	// close the file.

    return 0;
}


const char *getfield(char *line, int num)
{
    const char *token;

    for(token = strtok(line, ",");
              token && *token;
              token = strtok(NULL, ","))
    {
        if(! --num)
              return token;

	if(*token == ',' || *token == '\n') {
		token = NULL;
		num--;
		break;
	}
    }

    return NULL;
}





/* ======== GLOSSARY, NOTES ==================================================================== O/
												Library Source:

setlocale(LC_NUMERIC, ""); 	Linux feature to tune displays to country, locale.
fgets(file_name, 255, stdin); 	fgets(,,) string that is file_name, 255 buff, standard input.	#include <string.h>
     fgets(line, 1024, fp) 	fgets(,,) char line[1024], fp pointer to file content. 		#include <string.h>
fopen(file_name,"r"); 		file open "r", read mode. 					#include <stdio.h>
perror("\nError while opening the file.\n"); 	Library file-open error-handler.
exit(EXIT_FAILURE); 		? 								#include <stdlib.h>
char *tmp = strdup(line);
free(tmp); 			Erase the contents of char *tmp?


const char *getfield(char *line, int num) 	Function call --const char --*get fields in FILE *fp (as called).
token = strtok(line, ","); 			Hunt on the char 'line' for "," (commas). 	#include <string.h>
     token = strtok(NULL, ",\n") 		Hunt for ",\n" after NULL.  token=num?
token && *token; 				?



======== */
