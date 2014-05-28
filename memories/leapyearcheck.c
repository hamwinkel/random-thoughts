#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Isleap(int year);

int main(void)
{

int startyear = 4000,
    i;
//    startmonth = 1,
//    startyear = 1,
//    endday = 1,
//    endmonth = 1,
//    endyear = 1,
//    leap;
    for(i=0;i<1;i++){
    if(Isleap(startyear) == 1){
        printf("The year %d is a leap year!\n", startyear);
    }
    else printf("The year %d is not a leap year!", startyear);
    startyear++;
    }

return 0;
}

int Isleap(int year) {
    if(((year % 4) == 0 && (year % 100) != 0) || (year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}
