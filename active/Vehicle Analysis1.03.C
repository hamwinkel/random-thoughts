/* VEHICLE PERFORMANCE ANALYSIS  	v1.03  	by George Winkel*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 16

void splashscrnintro(void);
void enterer(void);
void outputter(int year0, int year1, int mon0, int mon1, int day0, int day1);
int daycounter(int year0, int year1, int mon0, int mon1, int day0, int day1);
char car$[256];
char *get_line (char *s$, size_t n, FILE *f);

char stub$t[256];
float inf[8] = {0,0,0,0,0,0,0,0};
float pnf[8] = {0,0,0,0,0,0,0,0};
char *analysis_data_block[8] = {"Enter Starting Date (yyyy,mm,dd)   @,@,",
"Enter Starting Odometer Milage   =  ", "* Enter Gallons of Fuel          =  ",
"* Enter Cost of Fuel             = $", "* Enter Other Costs              = $",
"Enter Total Qts. of Oil          =  ", "Enter Ending Odometer Milage     =  ",
"Enter Ending Date (yyyy,mm,dd)     @,@,"};

char *output_data_block[8] = {"Total Costs This Period          = $",
"Days in Current Period           =  ", "Miles Driven in Current Period   =  ",
"Miles Per Gallon                 =  ", "Miles Per Qt. Of Oil             =  ",
"Miles Per Month                  =  ", "Miles Per Dollar                 =  ",
"Cost Per Month                   = $"};



int main(void) 		/* ==================== MAIN Program Control function ================== */
{

    splashscrnintro();

    system("pause");

    enterer();

    system("pause");

    return 0;
}




void splashscrnintro(void) 	/* ========== Opening Splash-Screen, Intro-Instaructions =========== */
{
    int i;

    system("cls");

    puts("     VEHICLE PERFORMANCE ANALYSIS");
    puts("\t\t\t\t\t(C) George A. Winkel 2014\n\t\tINPUT");
    for(i = 0; i < 8; ++i) {
         printf("%s0", analysis_data_block[i]);
         puts("");
    }
    puts("\n\t\tOUTPUT");
    for(i = 0; i < 8; ++i) {
         printf("%s0", output_data_block[i]);
         puts("");
    }
    puts("\n\n");

    puts("Enter indicated data.\n\nFirst and last fuelings should be to a FULL gas tank.\n"
         "\nBe sure to START with the FIRST fueling AFTER 'beginning' date and milage."
         "\nAfter last '* -type' (summed) data, Enter zero (0) to continue.");
}




void enterer(void)	/* ======================= INputting function ==================== */
{
    int year0, year1, mon0, mon1, day0, day1;
    float num;

    system("cls");
    puts("     VEHICLE PERFORMANCE ANALYSIS\n\n");
    printf("\nIdentify this vehicle:  ");
    gets(car$);

    system("cls");

    puts("     VEHICLE PERFORMANCE ANALYSIS\n");
    printf("\t    %s\n", car$);
    puts("\n\t\tINPUT");

    printf("Enter Starting Date (yyyy,mm,dd):   ");
    scanf("%d, %d, %d", &year0, &mon0, &day0);
    puts("");

    printf("%s", analysis_data_block[1]); 	/* Starting Odometer Milage */
    scanf("%f", &inf[1]);
         puts("\n");

    puts("* Enter Gallons of Fuel\t\t (Enter 0's to end.)"); 	/* Add-up: Gallons Fuel */
    puts("\t\t   * Enter Cost of $Fuel"); 			/* Add-up: Cost of Fuel */
    do {
         printf("\tGallons =  ");
         scanf("%f", &num); inf[2] = inf[2] + num;
         printf("\t\t\t    Cost = $");
         scanf("%f", &num); inf[3] = inf[3] + num;
    } while(num != 0);
    puts("\n");

    printf("%s", analysis_data_block[4]); 	/* Add-up: Other Costs */
    do {
         if(inf[4] != 0) printf("\t\t\t    Cost = $");
         scanf("%f", &num);
         inf[4] = inf[4] + num;
    } while(num != 0);
    puts("");

    printf("%s", analysis_data_block[5]); 	/* Tot. quarts of oil */
    scanf("%f", &inf[5]);
    puts("");

    printf("%s", analysis_data_block[6]); 	/* Ending Odometer Milage */
    scanf("%f", &inf[6]);
         puts("");

    printf("Enter Ending Date (yyyy,mm,dd):     ");
    scanf("%d, %d, %d", &year1, &mon1, &day1);
    puts("\n");

    pnf[1] = daycounter(year0, year1, mon0, mon1, day0, day1);

    outputter(year0, year1, mon0, mon1, day0, day1);

}


/* analysis_data_block[8]:~~~~~~~~~~~~~~~~~~~~*\
   [0] Enter Starting Date (yyyy,mm,dd)
inf[1] Starting Odometer Mileage
inf[2] * Enter Gallons of Fuel	(* do-while loop sum)
inf[3] * Enter Cost of Fuel 	(* do-while loop sum)
inf[4] * Enter Other Costs 	(* do-while loop sum)
inf[5] Enter Total Qts. of Oil
inf[6] Enter Ending Odometer Milage
   [7] Enter Ending Date (yyyy,mm,dd)

output_data_block[8]
pnf[0] Total Costs This Period
pnf[1] Days in Current Period
pnf[2] Miles Driven in Current Period
pnf[3] Miles Per Gallon
pnf[4] Miles Per Qt. Of Oil
pnf[5] Miles Per Month
pnf[6] Miles Per Dollar
pnf[7] Cost Per Month
_____________________________________________*/




	/* ======================= OUTputting function ==================== */
void outputter(int year0, int year1, int mon0, int mon1, int day0, int day1)
{
     system("cls");

		/* ===================== COMPUTATION SEGMENT =======================*/

    pnf[0] = inf[3] + inf[4]; 		/* Total Costs This Period */
    /* pnf[1] = daycounter(......);  	/_ Days in Current Period */
    pnf[2] = inf[6] - inf[1]; 		/* Miles Driven in Current Period */
    if(inf[2] != 0)
         pnf[3] = pnf[2] / inf[2]; 	/* Miles Per Gallon */
    else pnf[3] = 0;
    if(inf[5] != 0)
         pnf[4] = pnf[2] / inf[5]; 	/* Miles Per Qt. of Oil */
    else pnf[4] = 0;
    if(pnf[1] != 0)
         pnf[5] = pnf[2] * 30.43684914 / pnf[1]; 	/* Miles Per Month */
    else pnf[5] = 0;
    if(pnf[0] != 0)
         pnf[6] = pnf[2] / pnf[0]; 	/* Miles Per Dollar */
    else pnf[6] = 0;
    if(pnf[1] != 0)
         pnf[7] = pnf[0] * 30.43684914 / pnf[1]; 	/* Cost Per Month */
    else pnf[7] = 0;
		/* ===================== OUTPUT-DISPLAYING SEGMENT =======================*/

    puts("     VEHICLE PERFORMANCE ANALYSIS\n");
    printf("\t    %s\n", car$);
    puts("\n\t\tINPUT SUMMARY");

    printf("Enter Starting Date (yyyy,mm,dd):   %d-%.2i-%.2i\n", year0, mon0, day0);
    printf("%s%.7g\n", analysis_data_block[1], inf[1]);
    printf("%s%.7g\n", analysis_data_block[2], inf[2]);
    printf("%s%-8.2f\n", analysis_data_block[3], inf[3]);
    printf("%s%-8.2f\n", analysis_data_block[4], inf[4]);
    printf("%s%.7g\n", analysis_data_block[5], inf[5]);
    printf("%s%.7g\n", analysis_data_block[6], inf[6]);
    printf("Enter Ending Date  (yyyy,mm,dd):    %d-%.2i-%.2i\n", year1, mon1, day1);

    puts("\n\t\tOUTPUT-ANALYSIS");
    printf("%s%-8.2f\n", output_data_block[0], pnf[0]);
    printf("%s%.8g\n", output_data_block[1], pnf[1]);
    printf("%s%.7g\n", output_data_block[2], pnf[2]);
    printf("%s%-7.2f\n", output_data_block[3], pnf[3]);
    printf("%s%-7.2f\n", output_data_block[4], pnf[4]);
    printf("%s%-7.2f\n", output_data_block[5], pnf[5]);
    printf("%s%-7.3f\n", output_data_block[6], pnf[6]);
    printf("%s%-8.2f\n", output_data_block[7], pnf[7]);

    puts("");
}




/* =================== Dates Numberizing, Days Time function ================ */
int leapyeartest(double yearX, int Feb);
int intervenefullYears(int year0, int year1);
int daycounter(int year0, int year1, int mon0, int mon1, int day0, int day1)
{
    int i, Feb, brac0, brac1, dayo;
    double yearX;
    int yer[2] = {0, 0};
    int Mos0C[12] = {365, 334, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31};
    int Mos0L[12] = {366, 335, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31};

    yer[0] = year0;
    yer[1] = year1;

    for(i = 0; i < 2; i++) {
         yearX = yer[i];
         Feb = leapyeartest(yearX, Feb);
         if(Feb == 28) { 		/* COMMON YEARS */
              brac0 = Mos0C[mon0-1] - day0;
              brac1 = 365 - (Mos0C[mon1-1] - day1);
         }
         else if(Feb == 29) { 		/* LEAP YEARS */
              brac0 = Mos0L[mon0-1] - day0;
              brac1 = 366 - (Mos0L[mon1-1] - day1);
         }
    }
			/* Test for same or diffrent [START-END] years? */
    if(year0 != year1)
         dayo = brac0 + intervenefullYears(year0, year1) + brac1;

    else if(year0 == year1) {
         if(Feb == 28) dayo = brac0 + brac1 - 365;
         else if(Feb == 29) dayo = brac0 + brac1 - 366;
    }
    return dayo; 	/* Return the count of days */
}


int leapyeartest(double yearX, int Feb) 	/* ========== Leap Year recognizer function ========= */
{
    Feb = 28;

    if(yearX/4000 == (int)(yearX/4000)) Feb = 28; 	/* Unofficial refinement --Sir William Herschel's suggestion. */
    else if(yearX/400 == (int)(yearX/400)) Feb = 29;
    else if(yearX/100 == (int)(yearX/100)) Feb = 28;
    else if(yearX/4 == (int)(yearX/4)) Feb = 29;

    return Feb;
}


int intervenefullYears(int year0, int year1) 	/* ====== Intervening Full Years adder-up function ===== */
{
    int i, Feb, daysfy = 0;
    double yearX;

    if(year1 - year0 < 2) return daysfy;

    for(i = 1; i <= (year1 - year0 - 1); i++) {
         yearX = (year0 + i);
         daysfy = daysfy + 337 + leapyeartest(yearX, Feb); 	/*  common year-28=337  */
    }
    return daysfy;
}





/* =========== Q-BASIC.BAS BONEYARD =================================================

REM     /* VEHICLE PERFORMANCE ANALYSIS

	O$ = CHR$(255) + CHR$(10)
	DIM M(12), H$(10), D(10), F(10)  'Vehicle Performance Check
	GOSUB 650
	PRINT TAB(50); "(C) George A. Winkel (5-06-2007)"; O$; O$; O$; O$
	PRINT "Enter indicated data."; O$; O$; "First and last fuelings should be to a FULL gas tank."; O$; O$; "Be sure to START with the FIRST fueling AFTER 'beginning' date and milage."; O$
	PRINT "After last '* -type' (summed) data, Enter blank Return to continue."; O$; O$; O$
	INPUT "Identify Vehicle: ", N$
	N$ = "(" + N$ + ")"
	FOR Z = 0 TO 10
		READ H$(Z)
	NEXT
	FOR Z = 0 TO 4
		READ I$(Z)
	NEXT
	FOR Z = 1 TO 12
		READ M(Z)
	NEXT
	GOSUB 650 	'Print the header.
	PRINT O$; H$(0); TAB(36);
	INPUT D$(0)	'Enter starting date as a string: mm-dd-yy
	PRINT O$
	PRINT H$(1); TAB(36);
	INPUT D(1) 	'Enter starting odometer mileage
	PRINT O$; O$; TAB(10); H$(2); SPC(8); H$(3)
70      PRINT TAB(19);
	INPUT ; "", C
	D(2) = D(2) + C
	PRINT TAB(49); "$";
	INPUT "", E
	D(3) = D(3) + E
	IF C OR E THEN
		GOTO 70
	END IF
	PRINT
	C = 0
	FOR y = 4 TO 6
		PRINT H$(y); TAB(36);
90              PRINT TAB(36);
		INPUT D(y)
		IF y > 4 THEN
			GOTO 120
		END IF
		C = C + D(y)
		IF D(y) = 0 THEN
			F(y) = C
			GOSUB 600
			D(y) = F(y)
			C = 0
		END IF
		IF C THEN
			GOTO 90
		END IF
120             PRINT O$
	NEXT
	PRINT H$(7); TAB(36);
	INPUT D$(7)	'Enter ending date as a string: mm-dd-yy
	GOSUB 300
	M = D(6) - D(1)
	E = D(3) + D(4)
	J = D / 30.43685
	IF D(2) > 0 THEN
		F(0) = M / D(2)
	END IF
	D(8) = E
	D(9) = D
	D(10) = M
	IF E > 0 THEN
		F(3) = M / E
	END IF
	IF J > 0 THEN
		F(4) = E / J
		F(2) = M / J
	END IF
	IF D(5) > 0 THEN
		F(1) = M / D(5)
	END IF
	FOR y = 0 TO 4
		GOSUB 600
	NEXT
	CLS
	PRINT TAB(11); "VEHICLE PERFORMANCE ANALYSIS"; O$
	PRINT TAB(15); N$; O$
	PRINT TAB(21); "SUMMARY"; O$  'Summing-up routine --Output --End
	FOR y = 0 TO 10
		IF y = 0 OR y = 7 THEN
			PRINT H$(y); TAB(38);
			PRINT D$(y)
		   ELSE
			PRINT H$(y);
		END IF

		IF y = 1 OR y = 2 OR y = 5 OR y = 6 OR y = 9 OR y = 10 THEN
			PRINT TAB(36); "=  "; D(y)
		END IF
		IF y = 3 OR y = 4 OR y = 8 THEN
			PRINT TAB(36); "= $"; D(y)
		END IF
	NEXT
	PRINT O$; TAB(20); "PERFORMANCE"
	FOR y = 0 TO 4
		PRINT I$(y); TAB(36);
		IF y = 4 THEN
			PRINT "= $"; F(y)
		   ELSE
			PRINT "=  "; F(y)
		END IF
	NEXT
	PRINT CHR$(11);
	END


300     D1$ = D$(0)  'Day-counting subroutine
	GOSUB 400
	M1 = D1(1)
	D1 = D1(2)
	Y1 = D1(3)
	D1$ = D$(7)
	GOSUB 400
	D2 = D1(2)
	M2 = D1(1)
	Y2 = D1(3)
	I = M1 - 1
	D = 0
	y = Y1 - 1
	GOSUB 450
330     I = I + 1
	IF I > 12 THEN
		I = 0
		GOSUB 450
	END IF
	D = D + M(I)
	IF I < M2 OR y < Y2 THEN
		GOTO 330
	ELSE
		D = D - D1 + D2 - M(M2)
	END IF
	RETURN


400     L = LEN(D1$)  'Date numberizing subroutine (i.e., convert date-strings to numbers)
	E = 1
	D3$ = D1$
	FOR C = 1 TO L
		X$ = MID$(D1$, C, 1)
		IF X$ = "-" OR X$ = "/" THEN
			D3$ = RIGHT$(D1$, L - C)
			E = E + 1
		END IF
		D1(E) = VAL(D3$)	(VAL function works L-R.  It stops at the first non-digit.)
	NEXT
	RETURN 		'[D1(1)=mm; D1(2)=dd; D1(3)=yy; integers]


450     y = y + 1  'Leapyear finding subroutine
	M(2) = 28
	IF y / 400 = INT(y / 400) THEN
		GOTO 450
	ELSE
		IF y / 4 = INT(y / 4) THEN
			M(2) = 29
		END IF
	END IF
	RETURN


600     C = 100  'Rounding subroutine
	Q = FIX(F(y))
	F(y) = Q + CINT(C * (F(y) - Q)) / C
	C = 0
	RETURN


650     CLS  'Title header
	PRINT TAB(26); "VEHICLE PERFOMANCE ANALYSIS"; O$
	PRINT TAB(33); N$; O$
	RETURN


REM  Data Block
	DATA Enter Starting Date (mm-dd-yy), Enter Starting Odometer Milage, * Enter Gallons of Fuel, * Enter Cost of Fuel $, * Enter Other Costs $, Enter Total Qts. of Oil, Enter Ending Odometer Milage, Enter Ending Date (mm-dd-yy)
	DATA Total Costs This Period, Days in Current Period, Miles Driven in Current Period
	DATA Miles Per Gallon,Miles Per Qt. Of Oil,Miles Per Month,Miles Per Dollar,Cost Per Month
	DATA 31,28,31,30,31,30,31,31,30,31,30,31



========== Q-BASIC PROGRAM EXPLANATIONS =============================

N$ == (Vehicle I.D.)

H$[10] == string data-block data\
     H$(0) == Enter Starting Date (mm-dd-yy)
     H$(1) == Enter Starting Odometer Milage
     H$(2) == * Enter Gallons of Fuel
     H$(3) == * Enter Cost of Fuel $
     H$(4) == * Enter Other Costs $
     H$(5) == Enter Total Qts. of Oil
     H$(6) == Enter Ending Odometer Milage
     H$(7) == Enter Ending Date (mm-dd-yy)
     H$(8) == Total Costs This Period
     H$(9) == Days in Current Period
     H$(10) == Miles Driven in Current Period

I$[5] == string data-block data [undeclared]\
     I$(0) == Miles Per Gallon
     I$(1) == Miles Per Qt. Of Oil
     I$(2) == Miles Per Month
     I$(3) == Miles per Dollar
     I$(4) == Cost Per Month

M[12] == float number data [days in months]\
     M(1) == 31
     M(2) == 28 [|== 29 in leap years]
     M(3) == 31
     M(4) == 30
     M(5) == 31
     M(6) == 30
     M(7) == 31
     M(8) == 31
     M(9) == 30
     M(10) == 31
     M(11) == 30
     M(12) == 31

D[10] float number data\
     D(1) == Starting odometer milage _
     D(2) == Gallons of Fuel _
     D(3) == Cost of Fuel $ _
     D(4) == Other Costs $ _
     D(5) == Total Qts. of Oil _
     D(6) == Ending Odometer Milage _

     D(8) == E ==D(3) + D(4) ==Total Costs This Period
     D(9) == D
     D(10) == H

D1[3] == integer array [undeclared] (in SUBR-400)\
     D1(1) == mm
     D1(2) == dd
     D1(3) == yyyy

D$[2] == string array [undeclared]\
     D$(0) == starting date (input)
     D$(7) == ending date (input)


Working String Constants\
D1$ = D$(0) = starting date string 		(in SUBR-300)
D1$ = D$(7) = ending date string 		(in SUBR-300)
D3$ = D1$ = starting/ending date string 	(in SUBR-400)



------ */
