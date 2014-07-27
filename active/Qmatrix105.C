/*  Qmatrix.C  Vehicle Analysis  v1.05 	-by Hamal and George */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

const char *getfield(char *line, int num);
const char *getfield2(char *line, int num);
int daycounter(int mon0, int day0, int year0, int mon1, int day1, int year1);


int main (void)
{
    int da1, mo1, yr1,
        da2, mo2, yr2,
        len, cDays;
    float totalgal = 0,
          fuelcost = 0,
          totoilqt = 0,
          othrcost = 0,
          sodm = 0,
          fodm;
    setlocale(LC_NUMERIC, "");
    char file_name[25];
    FILE *fp;

    system("cls");
    system("dir *.csv /X");
    puts("\nQmatrix v1.05  (C) 2014 Hamal and George Winkel");
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

    char line[1024], *tmp, 		/* This portion parses a file's lines (records) for its database fields */
         sDay[15], fDay[15];
    len = 0;
    while(fgets(line, 1024, fp)) {
         len++;
         tmp = strdup(line);
         if(len == 2) strcpy(sDay, getfield(tmp, 1)); 	// collect start date (as string)
         //free(tmp);
         tmp = strdup(line);
         strcpy(fDay, getfield(tmp, 1)); 		// collect final date (as string)
         //free(tmp);
         tmp = strdup(line);
         if(sodm == 0) sodm = atof(getfield(tmp, 2)); 	// collect start odometer
         //free(tmp);
         tmp = strdup(line);
         fodm = atof(getfield(tmp, 2)); 		// collect final odometer
         //free(tmp);
         tmp = strdup(line);
         totalgal += atof(getfield(tmp, 3)); 		// sum gallons of fuel
         //free(tmp);
         tmp = strdup(line);
         fuelcost += atof(getfield(tmp, 4)); 		// sum fuel cost$
         //free(tmp);
         tmp = strdup(line);
         totoilqt += atof(getfield(tmp, 5)); 		// sum qts. of oil
         //free(tmp);
         tmp = strdup(line);
         othrcost += atof(getfield(tmp, 7)); 		// sum all other cost$
         //free(tmp);
    }
   

    fclose(fp); 	// close the file.


    strcpy(line, sDay); 		/* This portion parses two string dates for six integers */
         tmp = strdup(line);
    mo1 = atoi(getfield2(tmp, 1)); 		// collect starting month
         //free(tmp);
         tmp = strdup(line);
    da1 = atoi(getfield2(tmp, 2)); 		// collect starting day
         //free(tmp);
         tmp = strdup(line);
    yr1 = atoi(getfield2(tmp, 3)); 		// collect starting year
         //free(tmp);

    strcpy(line, fDay);
         tmp = strdup(line);
    mo2 = atoi(getfield2(tmp, 1)); 		// collect final month
         //free(tmp);
         tmp = strdup(line);
    da2 = atoi(getfield2(tmp, 2)); 		// collect final day
         //free(tmp);
         tmp = strdup(line);
    yr2 = atoi(getfield2(tmp, 3)); 		// collect final year
         free(tmp);

    cDays = daycounter(mo1, da1, yr1, mo2, da2, yr2);

  /* ----------Cut this part out ---------------------
    printf("\nsDay = %s \t fDay = %s", sDay, fDay);
    printf("\nints:   %d   %d  %d", da1, mo1, yr1);
    printf("\nints:  %d  %d  %d\n", da2, mo2, yr2);
    printf("Count days this period = %d\n", cDays);
    -------------------------------------------------- */

    printf("\nThe contents of file:  %s\n", file_name);

    printf("Starting Record Date       %s\n", sDay);
    printf("Starting Odometer miles  = %.0f\n", sodm);
    printf("Total Gallons Fuel Used  = %.2f\n", totalgal);
    printf("Total Fuel Cost          =$%.2f\n", fuelcost);
    printf("Average cost per gallon  =$%.2f\n", (fuelcost / totalgal));
    printf("Subtotal of Other Costs  =$%.2f\n", othrcost);
    printf("Ending Odometer miles    = %.0f\n", fodm);
    printf("Ending Record Date         %s\n\n", fDay);
    printf("Records in this LogSheet = %d\n", len-1);
    printf("Count days this period   = %d\n", cDays);
    printf("Miles driven this period = %.0f\n", (fodm - sodm));
    printf("Tot Qts of Oil consumed  = %.0f\n", totoilqt);
    printf("Miles per gallon         = %.2f\n", ((fodm - sodm) / totalgal));
    printf("Total costs this period  =$%.2f\n", (fuelcost + othrcost));
    printf("Miles driven on each $1  = %.2f\n", ((fodm - sodm) / (fuelcost + othrcost)));

    return 0;
}


const char *getfield(char *line, int num) 	/* ===== Parse string fields by "," ===== */
{
    const char *token;

    for(token = strtok(line, ",");
              token && *token;
              token = strtok(NULL, ",\n"))
    {
         if(! --num)
              return token;
    }

    return NULL;
}


const char *getfield2(char *line, int num) 	/* ===== Parse string fields by "/" ===== */
{
    const char *token;

    for(token = strtok(line, "/");
              token && *token;
              token = strtok(NULL, "/\n"))
    {
         if(! --num)
              return token;
    }

    return NULL;
}


/* =================== Dates Numberizing, Days Time function ================ */
int Cyear(int syr, int eyr);
int Rmonth(int dcount, int yr);
int Cmonth(int mon, int yr, int dir);
int Isleap(int year);
int daycounter(int mon0, int day0, int year0, int mon1, int day1, int year1)
{

    int startmonth, 	endmonth,
        startday,	endday,
        startyear, 	endyear,
        sdays = 0,	edays = 0,
        tdays = 0;

    startmonth = mon0;
    startday = day0;
    startyear = year0;

    endmonth = mon1;
    endday = day1;
    endyear = year1;

    sdays = Cmonth(startmonth, startyear, 1) - startday;
    edays = Cmonth(endmonth, endyear, 0) - (Rmonth(endmonth, endyear) - endday);

    if(endyear == startyear) { 		/* Solve the Same-Year Problem here */
         tdays = (sdays + edays) - 365 - Isleap(endyear);
    } else 
         tdays = Cyear(startyear, endyear) + (sdays + edays);

    /*  ------- This can be cut out ------------------------
    float tropy = tdays / 365.2421897;
    float tropm = (tropy - (int)tropy) * 12;
    float tropd = (tropm  - (int)tropm) * 30.43684914;

    printf("Starting month %d has [%d days left in the start-year.\n", startmonth, sdays);
    printf("This time-span covers %.7g tropical years!\n", tdays/365.2421897);
    printf("    which is %d years\n\t     %d months\n\t     %.7g days.\n", (int)tropy, (int)tropm, tropd);
    printf("Ending month %d is %d] days into the end-year.\n\n", endmonth, edays);
    printf(" %d total days!\n\n", tdays);
    ------------------------------------------------------ */

    return tdays;
}


int Cyear(int syr, int eyr)
{
    int dtotal = 0;
    if(syr == eyr || syr == (eyr - 1)) {
        printf("%d\n", dtotal);

    } else {
        syr++;
        for(; syr < eyr; syr++) {
            if(Isleap(syr) == 1) {
                dtotal += 366;
            }
            else dtotal += 365;
        }
    }
    return dtotal;
}


int Rmonth(int dcount, int yr)
{
    if(dcount == 4 || dcount == 6 || dcount == 9 || dcount == 11) {
        return 30;
    } else if(dcount == 2 && Isleap(yr) == 1) {
        return 29;
    } else if(dcount == 2 && Isleap(yr) == 0) {
        return 28;
    } else {
        return 31;
    }
}


int Cmonth(int mon, int yr, int dir)
{
    int num = 0;
    if(dir == 1) {
        for(; mon < 13; mon++) {
            num += Rmonth(mon, yr);
        }
    }
    else {
        for(; mon > 0; mon--) {
            num += Rmonth(mon, yr);
        }
    }
    return num;
}


int Isleap(int year)
{
    if(((year % 4) == 0 && (year % 100) != 0)  || ((year % 400 == 0) && (year % 4000) != 0)) {
        return 1;
    } else {
        return 0;
    }
}






/* ======== GLOSSARY, NOTES ==================================================================== O/
												Library Source:

setlocale(LC_NUMERIC, ""); 	Linux feature to tune displays to country, locale. 		#include <locale.h>
fgets(file_name, 255, stdin); 	fgets(,,) string that is file_name, 255 buff, standard input.	#include <string.h>
     fgets(line, 1024, fp) 	fgets(,,) char line[1024], fp pointer to file content. 		#include <string.h>
fopen(file_name,"r"); 		file open "r", read mode. 					#include <stdio.h>
perror("\nError while opening the file.\n"); 	Library file-open error-handler.
exit(EXIT_FAILURE); 		0, success; 1 unsussessful; impeccible code 								#include <stdlib.h>
char *tmp = strdup(line);
free(tmp); 			Erase the contents of char *tmp?


const char *getfield(char *line, int num) 	Function call --const char --*get fields in FILE *fp (as called).
token = strtok(line, ","); 			Hunt on the char 'line' for "," (commas). 	#include <string.h>
     token = strtok(NULL, ",\n") 		Hunt for ",\n" after NULL.  token=num.
token && *token; 				?



======== */
