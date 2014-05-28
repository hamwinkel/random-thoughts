/* 	Driver to find days between calendar dates in C,  v1.02     By Hamal */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Cyear(int syr, int eyr);
int Rmonth(int dcount,int yr);
int Cmonth(int mon, int yr, int dir);
int Isleap(int year);


int main(void)
{
    int startmonth, 	endmonth,
        startday,	endday,
        startyear, 	endyear,
        sdays = 0,	edays = 0,
        tdays = 0;

    printf("\nEnter Starting MM,DD,YYYY  ");
    scanf("%d, %d, %d", &startmonth, &startday, &startyear);
    puts("");

    printf("Enter   Ending MM,DD,YYYY  ");
    scanf("%d, %d, %d", &endmonth, &endday, &endyear);
    puts("\n");


    sdays = Cmonth(startmonth, startyear, 1) - startday;
    edays = Cmonth(endmonth, endyear, 0) - (Rmonth(endmonth, endyear) - endday);
    tdays = Cyear(startyear, endyear) + (sdays + edays);

    printf("Starting month %d has %d days left in the year!\n", startmonth, sdays);
    printf("Ending month %d is %d days into the year!\n", endmonth, edays);
    printf(" %d total days!\n", tdays);

    return 0;
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

