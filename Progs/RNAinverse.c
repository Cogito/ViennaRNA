/*

                   interactive access to inverse.c
*/
/* Last changed Time-stamp: <95/11/24 14:12:32 ivo> */
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "inverse.h"
#include "fold_vars.h"
#include "fold.h"
#include "part_func.h"
#include "utils.h"

#define  PUBLIC
#define  PRIVATE   static

char  scale[] = "....,....1....,....2....,....3....,....4"
                "....,....5....,....6....,....7....,....8";

#define  REPEAT_DEFAULT  100
#define  INFINITY        100000

PRIVATE void usage(void);
extern int pf_dangl;

int main(int argc, char *argv[])
{
   char *string, *start, *structure, *str2, *line;
   int   i,j,length1, length2, l, hd;
   float energy, kT, p;
   int   pf, mfe, istty, rstart=0;
   int   repeat, found;

   do_backtrack = 0; pf = 0; mfe = 1;
   repeat = 0;
   init_rand();
   strcpy(symbolset,"GCAU");
   string=NULL;
   for (i=1; i<argc; i++) {
      if (argv[i][0]=='-')
	 switch ( argv[i][1] ) {
	  case 'a':
	    i++;
	    strcpy(symbolset,argv[i]);
	    break;
	  case 'T':  if (argv[i][2]!='\0') usage();
	    sscanf(argv[++i], "%f", &temperature);
	    break;
	  case 'F':
	    mfe = 0; pf = 0;
	    for(j=2;j<strlen(argv[i]);j++){
	       switch( argv[i][j] ) {
		case 'm' :  mfe = 1;
		  break;
		case 'p' :  pf = 1; /* dangles=0; old version */
		  break;
		  default : usage();
	       }
	    }
	    break;
	  case 'R': repeat = REPEAT_DEFAULT;
            if(++i<argc) sscanf(argv[i], "%d", &repeat);
	    break;
	  case 'n':
	    if ( strcmp(argv[i], "-noGU" )==0) noGU=1;
	    break;
	  case '4':
	    tetra_loop=0;
	    break;
	  case 'e':
	    sscanf(argv[++i],"%d", &energy_set);
	    break;
	  case 'd': dangles=0;
	    break;
	 case 'f': sscanf(argv[++i],"%f", &final_cost);
 	    break;
	  default: usage();
	 }
   }

   kT = (temperature+273.15)*1.98717/1000.0;

   istty = (isatty(fileno(stdout))&&isatty(fileno(stdin)));

   give_up = (repeat<0);

   do {
      if (istty) {
	 printf("\nInput structure & start string"
		" (lower case letters for const positions)\n"
		"    @ to quit, and 0 for random start string\n");
	 printf("%s\n", scale);
      }
      
      if ((line = get_line(stdin))==NULL) break;

      /* skip comment lines and get filenames */
      while ((*line=='*')||(*line=='\0')||(*line=='>')) {
	 printf("%s\n", line);
	 free(line);
	 if ((line = get_line(stdin))==NULL) line = "@";
      } 

      if (strcmp(line, "@") == 0) break;

      structure = (char *) space(strlen(line)+1);
      sscanf(line,"%s",structure);
      free(line);
      
      length2    = strlen(structure);
      str2 = (char *) space(length2+1);

      if ((line = get_line(stdin))==NULL) break;

      /* skip comment lines and get filenames */
      while ((*line=='*')||(*line=='\0')||(*line=='>')) {
	 printf("%s\n", line);
	 free(line);
	 if ((line = get_line(stdin))==NULL) line = "@";
      } 
      
      if (strcmp(line, "@") == 0) break;

      string = (char *) space(strlen(line)+1);
      sscanf(line,"%s",string);
      free(line);
      length1 = strlen(string);

      if (string[0]=='0') {
	 rstart = 1;
	 length1 = length2;
      }

      if(length1!=length2)
	 nrerror("Sequence and Structure have unequal length.");

      for (l = 0; l < strlen(symbolset); l++)
	 symbolset[l] = toupper(symbolset[l]);
      if (istty) printf("length = %d\n", length1);

      start = (char *) space(sizeof(char)*(length2+1));
      if (!rstart) strcpy(start, string);

      if (repeat!=0) found = (repeat>0)? repeat : (-repeat);
      else found = 1;

      if (mfe) initialize_fold(length2);
      if (pf)  init_pf_fold(length2);
      while(found>0){
	 if (rstart) {
	    free(string);
	    string = random_string(length2, symbolset);
	    strcpy(start, string);
	 } else
	    strcpy(string, start);
	 
	 if (mfe) {
            energy = inverse_fold(string, structure);
            if( (repeat>=0) || (energy==0.0) ) {
	       found--;
               hd = hamming(start, string);
	       printf("%s  %3d", string, hd);
	       if (energy>0.) {
	          printf("   d= %g\n", energy);
                  if(istty) {
                     energy = fold(string,str2);
	             printf("%s\n", str2);
                  }
               } else printf("\n");
            }
	 }
	 if (pf) {
	    if( (!mfe) || (repeat >= 0) || (energy==0.) ) {
	       if (dangles) pf_dangl = 1;
	       energy = inverse_pf_fold(string, structure);
	       p = exp(-energy/kT);
	       hd = hamming(start, string);
	       printf("%s  %3d  (%g)\n", string, hd, p);
	       if (dangles) pf_dangl = 0;
	    }
	    if (!mfe) found--;
	 }
	 fflush(stdout);
      }
      if (mfe) free_arrays();
      if (pf)  free_pf_arrays();

      free(string);
      free(structure);
      free(str2);
      free(start);
      fflush(stdout);
   } while (1);
   return 0;
}


PRIVATE void usage(void)
{
  nrerror("usage: RNAinverse [-F[mp]] [-a ALPHABET] [-R [repeats]]\n"
          "                  [-T temp] [-4] [-noGU] [-e e_set] [-f final]");
}
