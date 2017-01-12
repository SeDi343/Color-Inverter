/* !* Color Inverter
 *
 * \description a color inverter which inverts the colors of an image.
 *              as an example (255-30 = 225).
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at>
 *
 * \version Rev.: 01, 07.01.2017 - Created
 *          Rev.: 02, 07.01.2017 - Added first parts of the program, input of file
 *          Rev.: 03, 07.01.2017 - Dynamic Memory for Pixels, reading first lines
 *                                 of file, put handle with comments
 *                                 (starting with #) into headline.
 *          Rev.: 04, 08.01.2017 - Fixing problems with program, creating a struct
 *                                 for rgb and userdefined color inversion.
 *                                 Writing everyting into output.
 *          Rev.: 05, 08.01.2017 - Tried to count ellapsed time with TIME, but
 *                                 only has a precision of 1 sec.
 *          Rev.: 06, 08.01.2017 - Fancy userinterface and message reply from
 *                                 programm.
 *          Rev.: 07, 10.01.2017 - Adding quit function if comment is too long
 *          Rev.: 08, 12.01.2017 - Move functions and struct into headerfile
 *          Rev.: 09, 12.01.2017 - Fixing some bugs
 *
 * \information Works only with ASCII P3 format.
 *              Tested on MacOS Sierra
 *
 */

#include "myHeader.h"

extern void helpdesk_1(void);
extern int removecomment (void);

int main (int argc, char *argv[])
{
    char id[80];
    unsigned int width;
    unsigned int height;
    unsigned int maxColor;
    struct ppmPixel *ppmPixelPointer = NULL;
    int i = 0;
#if DEBUG
    int p = 0;
#endif
    int redChannel = 0;
    int blueChannel = 0;
    int greenChannel = 0;
    
/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M                                  */
/*------------------------------------------------------------------*/
#if TIME
    time_t start = time(NULL);
#endif
    clear();
    
    if (argc < 3)
    {
        printf(BOLD"\nERROR: Parameter Input ./colinvert.out INFILE OUTFILE [CHANNELS]\n"RESET);
        return -1;
    }
    
    if (strcmp(argv[1], argv[2]) == 0)
    {
        printf(BOLD"\nERROR: Use another output file name, can't overwrite input file\n"RESET);
        return -1;
    }
    
/* ---- Opening Input file and output file ---- */
    
    pFin = fopen(argv[1], "rb");
    if (pFin == NULL)
    {
        printf(BOLD"\nERROR: Could not open file \"%s\" for reading.\n"RESET, argv[1]);
        return -1;
    }
    
    pFout = fopen(argv[2], "wb");
    if (pFout == NULL)
    {
        printf(BOLD"\nERROR: Could not open file \"%s\" for writing.\n"RESET, argv[2]);
        return -1;
    }
    
/*------------------------------------------------------------------*/
/* S T A R T   O F   P3                                             */
/*------------------------------------------------------------------*/
    
/* ---- Read datas ---- */
    
    fgets(id,80, pFin);
    if (id[0] == 'P' && id[1] == '3' && id[2] == '\n')
    {
        
/* ---- Removing comment between P3 and main information ---- */
        
        removecomment();
        
/* ---- Read main information ---- */
        
        fscanf(pFin, "%u", &width);
        fscanf(pFin, "%u", &height);
        
        removecomment();
        
        fscanf(pFin, "%u", &maxColor);
        
        removecomment();
        
#if DEBUG
        printf(RED"Width=%u, Hight=%u, MaxColor=%u\n\n"RESET, width, height, maxColor);
#endif
        
/* ---- Allocating memory for picture ---- */
        
        ppmPixelPointer = (struct ppmPixel *)malloc(width*height*sizeof(struct ppmPixel));
        if (ppmPixelPointer == NULL)
        {
            printf(BOLD"\nERROR: Could not get memory.\n"RESET);
            return -1;
        }
        
/* ---- Read Pixels ---- */
        
        printf("\n");
        printf(BOLD"Importing file...\n"RESET);
        
        for (i = 0; i < width*height; i++)
        {
            removecomment();
            
            fscanf(pFin, "%u", &(ppmPixelPointer+i)->r);
            fscanf(pFin, "%u", &(ppmPixelPointer+i)->g);
            fscanf(pFin, "%u", &(ppmPixelPointer+i)->b);
            
#if DEBUG
            p++;
            printf(RED"Pixel [%d] %u\t %u\t %u\n"RESET, p,
            (ppmPixelPointer+i)->r, (ppmPixelPointer+i)->g, (ppmPixelPointer+i)->b);
#endif
        }
        
        printf(BOLD"Done file import!\n\n"RESET);
        
/* ---- Check user input for inversion ---- */
        
        if (argc == 3)
        {
            redChannel = 1;
            blueChannel = 1;
            greenChannel = 1;
        }
        
        if (argc == 4)
        {
            if (argv[3][0] == 'R' || argv[3][1] == 'R' || argv[3][2] == 'R' ||
                argv[3][0] == 'r' || argv[3][1] == 'r' || argv[3][2] == 'r')
            {
                redChannel = 1;
            }
            if (argv[3][0] == 'B' || argv[3][1] == 'B' || argv[3][2] == 'B' ||
                argv[3][0] == 'b' || argv[3][1] == 'b' || argv[3][2] == 'b')
            {
                blueChannel = 1;
            }
            if (argv[3][0] == 'G' || argv[3][1] == 'G' || argv[3][2] == 'G' ||
                argv[3][0] == 'g' || argv[3][1] == 'g' || argv[3][2] == 'g')
            {
                greenChannel = 1;
            }
        }
        
/* ---- Color inversion ---- */

        printf(BOLD"Inverting color channels...\n"RESET);
        
        for (i = 0; i < width*height; i++)
        {
            if (redChannel == 1)
            {
                (ppmPixelPointer+i)->r = maxColor - (ppmPixelPointer+i)->r;
            }
            if (greenChannel == 1)
            {
                (ppmPixelPointer+i)->g = maxColor - (ppmPixelPointer+i)->g;
            }
            if (blueChannel == 1)
            {
                (ppmPixelPointer+i)->b = maxColor - (ppmPixelPointer+i)->b;
            }
        }
        
        printf(BOLD"Inverting process finished!\n\n"RESET);
        
/* ---- Write header into file output ---- */
        
        printf(BOLD"Writing file...\n"RESET);
        
        fprintf(pFout, "P3\n");
        fprintf(pFout, "#Color Inverter by Sebastian Dichler\n");
        fprintf(pFout, "%u %u\n", width, height);
        fprintf(pFout, "%u\n", maxColor);
        
/* ---- Write pixels into output file ---- */
        
        for (i = 0; i < width*height; i++)
        {
            fprintf(pFout, "%u %u %u\n",
            (ppmPixelPointer+i)->r, (ppmPixelPointer+i)->g, (ppmPixelPointer+i)->b);
        }
        
        printf(BOLD"Done writing output file!\n"RESET);
    }
    
/* ---- Unknown Dataformat (not P3) ---- */
    
    else
    {
        printf(BOLD"\nERROR: Wrong Dataformat...\n"RESET);
        return -1;
    }
    
    free(ppmPixelPointer);
    fclose(pFin);
    fclose(pFout);
#if TIME
    printf("Ellapsed time: "BOLD"%.2f"RESET" sec\n", (double)(time(NULL) - start));
#endif
    
    return 0;
}
