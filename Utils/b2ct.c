/* This program converts the bracket notation for RNA secondary structures
   produced by RNAfold to .ct files used by Michael Zukers Program.
   To compile enter:
                    cc -o b2ct b2ct.c
   And use as
                    b2ct < structure_file > ct_file.ct
   or
                    RNAfold < sequence_file | b2ct > ct_file.ct
*/

#include <stdio.h>
#define MAXLENGTH 10000

void write_ct_file(char *fname, char *sequence, char *structure, char *name,
		   float energy);
int  make_pair_table(char *structure, short *table);
void *space(unsigned size);
void nrerror(char *message);

main(void)
{
   char line[MAXLENGTH+1];
   char *string=NULL, *structure=NULL, *name=NULL;
   float energy;
   int n=0;
   
   while (gets(line)!=NULL) {
       if (strcmp(line,"@")==0) break;
      
      switch (line[0]) {
       case '>': name = (char *) space(strlen(line));
	 sscanf(line,"> %s", name);
	 break;
       case '.':
       case '(':
       case ')': structure = (char *) space(strlen(line));
	 sscanf(line,"%s (%f)", structure, &energy);
	 n++;
	 break;
       default: string = (char *) space(strlen(line)+1);
	 sscanf(line, "%s", string);
      }
      if (structure!=NULL) {
	 if (name==NULL) {
	    name = (char *) space(10);
	    sprintf(name,"%d",n);
	 }
	 write_ct_file("-", string, structure, name, energy);
      	 free(string); 
	 free(structure); 
	 free(name);
	 string = structure = name = NULL;
      }
   }
}

void write_ct_file(char *fname, char *sequence, char *structure, char *name,
		   float energy)
{
   int i,j,length;
   short *table;
   FILE *ct;

   length = strlen(structure);
   table = (short *) space(length*sizeof(short));
   if (make_pair_table(structure, table)!=0) {
      free(table);
      return;
   }
   if (length!=strlen(sequence))
      nrerror("sequence and structure have unequal length");
   
   if (strcmp(fname,"-")==0) 
      ct = stdout;
   else {
      ct = fopen(fname, "a");
      if (ct==NULL) nrerror("can't open .ct file");
   }

   fprintf(ct, "%5d ENERGY = %7.1f    %s\n", length, energy, name);
   for (i=0; i<length; i++) 
      fprintf(ct, "%5d %c   %5d %4d %4d %4d\n",
	      i+1, sequence[i], i, i+2, table[i]+1, i+1);
   if (strcmp(fname,"-"))
      fclose(ct);
   else fflush(ct);
   free(table);
}

int make_pair_table(char *structure, short *table)
{
   int i,j,hx;
   short *stack;
   
   hx=0;
   stack = (short *) space(sizeof(short)*(strlen(structure)+1));
             
   for (i=0; i<strlen(structure); i++) {
      switch (structure[i]) {
       case '.':
         table[i]= -1;
         break;
       case '(': 
         stack[hx++]=i;
         break;
       case ')':
         j = stack[--hx];
         if (hx<0) break;
         table[i]=j;
         table[j]=i;
         break;
       default: hx=1;
      }
   }
   free(stack);
   return hx;
}

void *space(unsigned size)
{
    void *pointer;
    
    if ( (pointer = (void *) calloc(1, size)) == NULL) {
       fprintf(stderr,"SPACE: requested size: %d\n", size);
       nrerror("SPACE allocation failure -> no memory");
    }
    return  pointer;
}


void nrerror(char *message)       /* output message upon error */
{
    fprintf(stderr, "\n%s\n", message);
    exit(0);
}

