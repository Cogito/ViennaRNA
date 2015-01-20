#define STRUC     1000

extern char *b2HIT(char *);         /* Full   -> HIT    [incl. root]        */
extern char *b2C(char *);           /* Full   -> Coarse [incl. root]        */
extern char *b2Shapiro(char *);     /* Full   -> weighted Shapiro [i.r.]    */
extern char *add_root(char *);      /* {Tree} -> ({Tree}R)                  */

extern char  *expand_Shapiro(char *);  /* adds S for stacks to coarse struct */
extern char  *expand_Full(char *);     /* Full   -> FFull                    */
extern char  *unexpand_Full(char *);   /* FFull  -> Full                     */
extern char  *unweight(char *);

extern void   unexpand_aligned_F(char *align[2]);

extern void   parse_structure(char *); /* guess !!! */

extern int    loop_size[STRUC];       /* loop sizes of a structure */
extern int    helix_size[STRUC];      /* helix sizes of a structure */
extern int    loop_degree[STRUC];     /* loop degrees of a structure */
extern int    loops;                  /* n of loops and stacks */
extern int    unpaired, pairs;        /* n of unpaired digits and pairs */

/*
  Example:
  .((..(((...)))..((..)))).   is the bracket or full tree
  becomes expanded:   - expand_Full() -
  ((U)(((U)(U)((((U)(U)(U)P)P)P)(U)(U)(((U)(U)P)P)P)P)(U)R)
  HIT:                - b2HIT() -
  ((U1)((U2)((U3)P3)(U2)((U2)P2)P2)(U1)R) 
  Coarse:             - b2C() -
  ((H)((H)M)R)
  becomes expanded:   - expand_Shapiro() -
  (((((H)S)((H)S)M)S)R)
  weighted Shapiro:   - b2Shapiro() -
  ((((((H3)S3)((H2)S2)M4)S2)E2)R)
*/
/*  Global variables for Distance-Package */

extern int   edit_backtrack;  /* set to 1 if you want backtracking */ 
   
extern char *aligned_line[2]; /* containes alignment after backtracking */

extern int  cost_matrix;     /* 0 usual costs (default), 1 Shapiro's costs */

/*  Global type defs for Distance-Package */

typedef struct {
                 int  type; 
                 int  weight;
                 int  father;
                 int  sons;
                 int  leftmostleaf;                 
               } Postorder_list;

typedef struct {
                 Postorder_list *postorder_list; 
                 int            *keyroots; 
               } Tree;

typedef struct {
                 int    type;
                 int    sign;
                 float  weight; 
               } swString;
extern float  fold(char *string, char *structure);
extern float  energy_of_struct(char *string, char *structure);
extern void   free_arrays(void);
extern void   initialize_fold(int length);
extern void   update_fold_params(void);
extern int  noGU;           /* GU not allowed at all */
extern int  no_closingGU;   /* GU allowed only inside stacks */
extern int  tetra_loop;     /* Fold with specially stable 4-loops */
extern int  energy_set;     /* 0 = BP; 1=any mit GC; 2=any mit AU-parameter */
extern float temperature;

struct bond {         /* bonding list */
   int i;
   int j;
};
            
extern struct bond  *base_pair;

extern float *pr;              /* base pairing prob. matrix */
extern int   *iindx;           /* pr[i,j] -> pr[iindx[i]-j] */
extern float  pf_scale;        /* scaling factor to avoid float overflows*/
extern int    fold_constrained;
extern int    do_backtrack;    /* calculate pair prob matrix in part_func() */
extern char backtrack_type;    /* usually 'F'; 'C' require (1,N) to be bonded;
				  'M' seq is part of s multi loop */ 
extern char symbolset[];    /* alphabet default is "AUGC" */
/* the found sequence is given back in start,
   return value for inverse_fold is
          energy_of_struct(start, target) - fold(start, structure),
   that is 0. if search was successful;
   for inverse_pf_fold
          energy_of_struct(start, target) - part_func(start, structure)
   that is the frequency of target in the ensemble of strucures is
          p = exp(-inverse_pf_fold/kT);
*/
extern float inverse_fold(char *start, char *target);  
extern float inverse_pf_fold(char *start, char *target);
extern int give_up;   /* default 0: try to minimize structure distance even if 
			 no exact solution can be found */

#define NBASES 8
static char Law_and_Order[] = "_ACGUXKI";
static int BP_pair[NBASES][NBASES]=
/* _  A  C  G  U  X  K  I */
{{ 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 5, 0, 0, 5},
 { 0, 0, 0, 1, 0, 0, 0, 0},
 { 0, 0, 2, 0, 3, 0, 0, 0},
 { 0, 6, 0, 4, 0, 0, 0, 6},
 { 0, 0, 0, 0, 0, 0, 2, 0},
 { 0, 0, 0, 0, 0, 1, 0, 0},
 { 0, 6, 0, 0, 5, 0, 0, 0}};

#define MAXALPHA 20       /* maximal length of alphabet */

static short alias[MAXALPHA+1];
static int pair[MAXALPHA+1][MAXALPHA+1];

#define ENCODE(C) (energy_set>0)?((C)-'A'+1): \
   ((strchr(Law_and_Order, (C))==0)?0:(strchr(Law_and_Order, (C))-Law_and_Order))

static void make_pair_matrix(void)
{
   int i,j;
   
   if (energy_set==0) {
      for (i=0; i<5; i++) alias[i] = i;
      alias[5] = 3; /* X <-> G */
      alias[6] = 2; /* K <-> C */
      alias[7] = 0; /* I <-> default base '@' */
      for (i=0; i<NBASES; i++) {
	 for (j=0; j<NBASES; j++) 
	    pair[i][j] = BP_pair[i][j];
      }
      if (noGU) pair[3][4] = pair[4][3] =0; 
   } else {
      for (i=0; i<=MAXALPHA; i++) {
	 for (j=0; j<=MAXALPHA; j++) 
	    pair[i][j] = 0;
      }
      if (energy_set==1) {
	 for (i=1; i<=MAXALPHA;) {
	    alias[i++] = 3;  /* A <-> G */
	    alias[i++] = 2;  /* B <-> C */
	 }
	 for (i=1; i<=MAXALPHA; i++) {
	    pair[i][i+1] = 2;    /* AB <-> GC */
	    i++;
	    pair[i][i-1] = 1;    /* BA <-> CG */
	 }
      }
      else if (energy_set==2) {
	 {
	    alias[i++] = 1;  /* A <-> A*/
	    alias[i++] = 4;  /* B <-> U */
	 }
	 for (i=1; i<=MAXALPHA; i++) {
	    pair[i][i+1] = 5;    /* AB <-> AU */
	    i++;
	    pair[i][i-1] = 6;    /* BA <-> UA */
	 }
      } else nrerror("What energy_set are YOU using??");
   }
}


extern float  pf_fold(char *sequence, char *structure);
extern void   init_part_fold(int length);
extern void   free_pf_arrays(void);
extern void   update_pf_params(int length);
extern char  *bppm_symbol(float *x);
extern float    profile_edit_distance(float **T1, float **T2);
extern float  **Make_bp_profile(int length);
extern void     sprint_aligned_bppm(float **T1, float **T2);
extern void     print_bppm(float **T);

extern float     string_edit_distance(swString *T1, swString *T2);
extern swString *Make_swString(char *string);
extern  Tree   *make_tree(char *struc);
extern  float   tree_edit_distance(Tree *T1, Tree *T2);
extern  void    print_tree(Tree *t);
extern  void    free_tree(Tree *t);
/* Header file for utils.c */

extern void  *space(unsigned int size);
extern void   nrerror(char *message);
extern double urn();
extern int    int_urn(int from, int to);
extern void   filecopy(FILE *from, FILE *to);
extern char  *time_stamp();
extern char  *random_string(int l, char *symbols);
extern int    hamming(char *s1, char *s2);
extern unsigned short xsubi[3];

