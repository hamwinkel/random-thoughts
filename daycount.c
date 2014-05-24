#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Cyear (int syr, int eyr);
int Rmonth (int dcount,int yr);
int Cmonth (int mon, int yr, int dir);
int Isleap (int year);

int main (void)
{
    int startmonth = 1,     endmonth = 1,
        startyear = 2001,   endyear = 4001,
        startday = 1,       endday = 2,
        sdays = 0,          edays = 0,
        tdays = 0;

    sdays = Cmonth (startmonth, startyear, 1) - startday;
    edays = Cmonth (endmonth, endyear, 0) - (Rmonth(endmonth, endyear) - endday);
    tdays = Cyear (startyear, endyear) + (sdays + edays);
    printf ("Starting month %d has %d days left in the year!\n", startmonth, sdays);
    printf ("Ending month %d is %d days into the year!\n", endmonth, edays);
    printf (" %d total days!\n", tdays);
    return 0;
}

int Cyear (int syr, int eyr) {
    int dtotal = 0;
    if (syr == eyr || syr == (eyr - 1)) {
    } else {
        syr++;
        for (; syr < eyr; syr++) {
            if (Isleap(syr) == 1) {
                dtotal += 366;
            }
            else dtotal += 365;
        }
    }
    return dtotal;
}

int Rmonth (int dcount,int yr) {
    if (dcount == 4 || dcount == 6 || dcount == 9 || dcount == 11) {
        return 30;
    } else if (dcount == 2 && Isleap(yr) == 1){
        return 29;
    } else if (dcount == 2 && Isleap(yr) == 0){
        return 28;
    } else {
        return 31;
    }
}

int Cmonth (int mon, int yr, int dir) {
    int num = 0;
    if (dir == 1) {
        for (; mon < 13; mon++){
            num += Rmonth (mon, yr);
        }
    }
    else {
        for (; mon > 0; mon--) {
            num += Rmonth (mon, yr);
        }
    }
    return num;
}

int Isleap (int year) {
    if (((year % 4) == 0 && (year % 100) != 0)  || ((year % 400 == 0) && (year % 4000) != 0)) {
        return 1;
    } else {
        return 0;
    }
}
