/* !* Headerfile
 *
 * \description Headerfile for useful functions -> edited for 01_170107_colorinvert.c
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at><sedi343@gmail.com>
 *
 * \version Rev.: 01, 17.12.2016 - Created
 *          Rev.: 02, 17.12.2016 - Adding function clear, clearNoHelp, clearString
 *
 */

#ifndef _myHeader_
#define _myHeader_

/*------------------------------------------------------------------*/
/* I N C L U D E   L I B R A R I E S                                */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*------------------------------------------------------------------*/
/* T E R M I N A L   A S C I I   F O R M A T I O N                  */
/*------------------------------------------------------------------*/

#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)

/* ---- ANSI FORMAT FOR TERMINAL ---- */

#define RESET   "\033[0m"
#define BLACK   "\033[30m"                 /* Black */
#define RED     "\033[31m"                 /* Red */
#define GREEN   "\033[32m"                 /* Green */
#define CYAN    "\033[36m"                 /* Cyan */
#define BOLD    "\033[1m"                  /* Bold */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif

#if defined(_WIN32) || defined(_WIN64)

/* ---- ANSI FORMAT NOT SUPPORTED IN WINDOWS ---- */

#define RESET   ""
#define BLACK   ""
#define RED     ""
#define GREEN   ""
#define CYAN    ""
#define BOLD    ""
#define BOLDRED     ""
#define BOLDGREEN   ""
#define BOLDBLACK   ""
#define BOLDCYAN    ""
#define BOLDWHITE   ""

#endif

#define DEBUG 0
#define TIME 0

struct ppmPixel
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

FILE* pFin;
FILE* pFout;
fpos_t position;

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E C L A R A T I O N                          */
/*------------------------------------------------------------------*/

void helpdesk_1(void);
void clear(void);
void clearNoHelp(void);
unsigned int clearString(char *input);
int removecomment(void);

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E F I N I T I O N                            */
/*------------------------------------------------------------------*/

void clear(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
    system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
    helpdesk_1();
}

void clearNoHelp(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
    system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

/* ---- FUNCTION BY HELMUT RESCH ---- */
unsigned int clearString(char *input)
{
    int i;
    
    for (i = 0; i < strlen(input); i++)
    {
        if (input[i] == '\r')
        {
            input[i] = '\0';
        }
        if (input[i] == '\n')
        {
            input[i] = '\0';
        }
        if (input[i] == '\t')
        {
            input[i] = '\0';
        }
    }
    
    return 0;
}

void helpdesk_1(void)
{
    printf("\n");
    printf(BOLD"COLOR INVERTER @ v1.0\n"RESET);
    printf(BOLD"Created by Sebastian Dichler, 2017\n"RESET);
    printf("Format input:\t"BOLD"./colreduce.out INFILE OUTFILE [CHANNELS]\n"RESET);
    printf("\t\t"BOLD"./colreduce.out INFILE OUTFILE"RESET" for RGB change.\n");
    printf("Examples for CHANNELS:\n");
    printf(BOLD"RGB"RESET"\tfor full color exchange\n");
    printf(BOLD"RB"RESET"\tfor red and blue exchange\n");
    printf(BOLD"G"RESET"\tfor only green exchange\n");
#if DEBUG
    printf(BOLDRED"DEBUG MODE ACTIVE!!!\n"RESET);
#endif
}

int removecomment(void)
{
    char comment[500];
    
    fgetpos(pFin,&position);
    
    fgets(comment, 500, pFin);
    
    if (comment[strlen(comment)-1] != '\n')
    {
        printf(BOLD"\nERROR: Header Comment in file to long.\n"RESET);
        return -1;
    }
    
    if (comment[0] != '#')
    {
        fsetpos(pFin,&position);
    }
    else
    {
        while (comment[0] == '#')
        {
            fgetpos(pFin,&position);
            fgets(comment, 500, pFin);
            
            if (comment[strlen(comment)-1] != '\n')
            {
                printf(BOLD"\nERROR: Header Comment in file to long.\n"RESET);
                return -1;
            }
            
            if (comment[0] != '#')
            {
                break;
            }
        }
    }
    
    fsetpos(pFin,&position);
    
    return 0;
}

#endif /* myHeader_h */
