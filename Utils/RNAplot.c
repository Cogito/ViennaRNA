/*
  Plot RNA structures using different layout algorithms
  Last changed Time-stamp: <1999-02-27 18:33:28 ivo> 
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "PS_dot.h"

#define PRIVATE static

PRIVATE char  scale[] = ".........1.........2.........3.........4.........5.........6.........7.........8";

PRIVATE void usage(void);


/*--------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   
   char *string=NULL, *line;
   char *structure=NULL;
   char  fname[13], ffname[20];
   int   i, r;
   float energy;
   int   istty;
   int gml=0;
   
   string=NULL;
   for (i=1; i<argc; i++) {
     if (argv[i][0]=='-') 
	switch ( argv[i][1] ) {
	 case 't':
	   r = sscanf(argv[++i], "%d", &rna_plot_type);
	   if (r!=1) usage();
	   break;
	case 'g':
	  gml = 1;
	  break;
	default: usage(); 
	} 
   }
   
   istty = isatty(fileno(stdin));

   do {				/* main loop: continue until end of file */
      if (istty) {
	 printf("\nInput sequence and structure; @ to quit\n");
	 printf("%s\n", scale);
      }
      fname[0]='\0';
      if ((line = get_line(stdin))==NULL) break;

      /* skip comment lines and get filenames */
      while ((*line=='*')||(*line=='\0')||(*line=='>')) {
	 if (*line=='>')
	    sscanf(line, ">%12s", fname);
	 printf("%s\n", line);
	 free(line);
	 if ((line = get_line(stdin))==NULL) line = "@";
      } 

      if (strcmp(line, "@") == 0) break;

      string = (char *) space(strlen(line)+1);
      sscanf(line,"%s",string);
      free(line);

      if ((line = get_line(stdin))==NULL) break;
      structure = (char *) space(strlen(line)+1);
      sscanf(line,"%s (%f)", structure, &energy);
      free(line);
      
      if (gml) {
	if (fname[0]!='\0') {
	  strcpy(ffname, fname);
	  strcat(ffname, "_ss.gml");
	} else
	  strcpy(ffname, "rna.gml");
	gmlRNA(string, structure, ffname, 'x');
      } else {
	if (fname[0]!='\0') {
	  strcpy(ffname, fname);
	  strcat(ffname, "_ss.ps");
	} else
	  strcpy(ffname, "rna.ps");
	PS_rna_plot(string, structure, ffname);
      }
      fflush(stdout);
      free(string);
      free(structure); 
   } while (1);
   return 0;
}

PRIVATE void usage(void)
{
   nrerror("usage: RNAplot [-t 0|1] -g");
}

