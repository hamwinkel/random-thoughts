/* 	Driver to find days between calendar dates in C,  v1.05     */

#include <stdio.h>
#include <stdlib.h>

int leapyeartest(double yearX, int Feb);
int daycounter(int year0, int year1, int mon0, int mon1, int day0, int day1);
int sameyearproblem(int year0, int brac0);

int main (void)
{
    int year0, year1, mon0, mon1, day0, day1, dayo;
    float daysD, daysT0, daysT1;

    printf("Enter Starting YYYY,MM,DD  ");
    scanf("%d, %d, %d", &year0, &mon0, &day0);
    puts("");

    printf("Enter   Ending YYYY,MM,DD  "); 
    scanf("%d, %d, %d", &year1, &mon1, &day1);
    puts("\n");

/* temporary rem-out .....
    daysT0 = year0 * 365.2421897 + (mon0 - 1) * 30.43684914 + day0;
    daysT1 = year1 * 365.2421897 + (mon1 - 1) * 30.43684914 + day1;

    printf("Total days of daysT0 = %.10g      Total days of dayT1 = %.10g\n", daysT0, daysT1);

    daysD = (daysT1 - daysT0);

    dayo = (int)(daysD + 0.5);

    printf("\nDifference by days between dates as a 0.5 rounded-up integer = %i\n", dayo);
...... */

    dayo = daycounter(year0, year1, mon0, mon1, day0, day1);

    printf("\nA rigorous count of days (returned to the calling func) = %i\n", dayo);

    return 0;
}





int daycounter(int year0, int year1, int mon0, int mon1, int day0, int day1) 	/* ==== Count days, to year's start AND to year's end ====== */
{
    int i, Feb, brac0, brac1, dayo;
    double yearX;
    int yer[2] = {0, 0};
 
	        /* Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */
  /*  int MoC[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	This is here only for reference. */

    int Mos0C[12] = {365, 334, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31};	/* Left Bracket--> count afterward, to end of year */
    int Mos0L[12] = {366, 335, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31};	/* Delta0 = Mos0_(n) - day0   */

 //   int Mos1C[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};	/* Right Bracket<-- count forward to start of year */
 //   int Mos1L[13] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};	/* Delta1 = Mos1_(n-1) + day1 (it needs a left-0 cushion) */

    yer[0] = year0;
    yer[1] = year1;

			    /* Loop below finds [Left0-> and <-Right1] brackets of days, using array(s) */
    for(i = 0; i < 2; i++) {

         yearX = yer[i];

         Feb = leapyeartest(yearX, Feb);

         if(Feb == 28) {
              if(i == 0) brac0 = Mos0C[mon0-1] - day0; 	   /* [Left Bracket from array-> (Common years) */
              else; brac1 = 365 - (Mos0C[mon1-1] - day1);  /* Compute <-Right] Bracket from [Left-> array */
         //     else; brac1 = Mos1C[mon1-1] + day1; 	   /* <-Right Bracket] from its own array */
         }
         else; if(Feb == 29) {
              if(i == 0) brac0 = Mos0L[mon0-1] - day0; 	   /* [Left Bracket from array-> (Leap years) */
              else; brac1 = 366 - (Mos0L[mon1-1] - day1);  /* Compute <-Right Bracket from [Left-> array */
         //     else; brac1 = Mos1L[mon1-1] + day1; 	   /* <-Right Bracket] from its own array */
         }
         printf("yearX = %.7g         February = %d\n", yearX, Feb);
    }

    printf("\nRemaining days of Left Bracket = [%i\n", brac0);
    printf("\nPreceding days of Right Bracket = %i]\n", brac1);

			/* Below, we test for same or diffrent start-end years */
    if(year0 != year1) {
         printf("\nThe exact count of days [between the two dates in CONSECUTIVE YEARS] = %d\n", brac0+brac1);
         dayo = brac0 + brac1;
    }
    else; if(year0 == year1) {
         brac0 = sameyearproblem(year0, brac0);
         printf("\nThe exact count of days [between the two dates inside THE SAME YEAR] = %d\n", brac1-brac0);
         dayo = brac1 - brac0;
    }

    return dayo;
}




int sameyearproblem(int year0, int brac0) 	/* ====== Analyze day-count within the same year ====== */
{
    int i, Feb;
    double yearX;

    yearX = year0;

    Feb = leapyeartest(yearX, Feb);

         if(Feb == 28) {
              brac0 = 365 - brac0;
         }
         else; if(Feb == 29) {
              brac0 = 366 - brac0;
        }
   
    return brac0;
}





int leapyeartest(double yearX, int Feb) 	/* ========== Leap Year recognizer function ========= */
{
    Feb = 28;

    if(yearX/4000 == (int)(yearX/4000)) Feb = 28;
    else if(yearX/400 == (int)(yearX/400)) Feb = 29;
    else if(yearX/100 == (int)(yearX/100)) Feb = 28;
    else if(yearX/4 == (int)(yearX/4)) Feb = 29;

    return Feb;
}







/* ======= NOTES ========================


Start my Julian Days on: -4713/11/24   (Not 4714 BC. Plus 1 yr BC, because I use a Yr 0.  And remember; J.Days increment at noon UT.)


*/
