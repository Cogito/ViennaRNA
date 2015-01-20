/** @file RNAcofold_cmdl.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.3
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef RNACOFOLD_CMDL_H
#define RNACOFOLD_CMDL_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef RNACOFOLD_CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define RNACOFOLD_CMDLINE_PARSER_PACKAGE "RNAcofold"
#endif

#ifndef RNACOFOLD_CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define RNACOFOLD_CMDLINE_PARSER_PACKAGE_NAME "RNAcofold"
#endif

#ifndef RNACOFOLD_CMDLINE_PARSER_VERSION
/** @brief the program version */
#define RNACOFOLD_CMDLINE_PARSER_VERSION VERSION
#endif

/** @brief Where the command line options are stored */
struct RNAcofold_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *detailed_help_help; /**< @brief Print help, including all details and hidden options, and exit help description.  */
  const char *full_help_help; /**< @brief Print help, including hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  int constraint_flag;	/**< @brief Calculate structures subject to constraints.\n (default=off).  */
  const char *constraint_help; /**< @brief Calculate structures subject to constraints.\n help description.  */
  int noconv_flag;	/**< @brief Do not automatically substitude nucleotide \"T\" with \"U\"\n\n (default=off).  */
  const char *noconv_help; /**< @brief Do not automatically substitude nucleotide \"T\" with \"U\"\n\n help description.  */
  int noPS_flag;	/**< @brief Do not produce postscript output\n\n (default=off).  */
  const char *noPS_help; /**< @brief Do not produce postscript output\n\n help description.  */
  int partfunc_arg;	/**< @brief Calculate the partition function and base pairing probability matrix in addition to the mfe structure. Default is calculation of mfe structure only.\n (default='1').  */
  char * partfunc_orig;	/**< @brief Calculate the partition function and base pairing probability matrix in addition to the mfe structure. Default is calculation of mfe structure only.\n original value given at command line.  */
  const char *partfunc_help; /**< @brief Calculate the partition function and base pairing probability matrix in addition to the mfe structure. Default is calculation of mfe structure only.\n help description.  */
  int all_pf_flag;	/**< @brief Compute the partition function and free energies not only of the hetero-dimer consisting of the two input sequences (the \"AB dimer\"), but also of the homo-dimers AA and BB as well as A and B monomers.\n (default=off).  */
  const char *all_pf_help; /**< @brief Compute the partition function and free energies not only of the hetero-dimer consisting of the two input sequences (the \"AB dimer\"), but also of the homo-dimers AA and BB as well as A and B monomers.\n help description.  */
  int concentrations_flag;	/**< @brief In addition to everything listed under the -a option, read in initial monomer concentrations and compute the expected equilibrium concentrations of the 5 possible species (AB, AA, BB, A, B).\n (default=off).  */
  const char *concentrations_help; /**< @brief In addition to everything listed under the -a option, read in initial monomer concentrations and compute the expected equilibrium concentrations of the 5 possible species (AB, AA, BB, A, B).\n help description.  */
  char * concfile_arg;	/**< @brief Specify a file with initial concentrations for the to sequences..  */
  char * concfile_orig;	/**< @brief Specify a file with initial concentrations for the to sequences. original value given at command line.  */
  const char *concfile_help; /**< @brief Specify a file with initial concentrations for the to sequences. help description.  */
  double pfScale_arg;	/**< @brief In the calculation of the pf use scale*mfe as an estimate for the ensemble free energy (used to avoid overflows).\n.  */
  char * pfScale_orig;	/**< @brief In the calculation of the pf use scale*mfe as an estimate for the ensemble free energy (used to avoid overflows).\n original value given at command line.  */
  const char *pfScale_help; /**< @brief In the calculation of the pf use scale*mfe as an estimate for the ensemble free energy (used to avoid overflows).\n help description.  */
  double bppmThreshold_arg;	/**< @brief Set the threshold for base pair probabilities included in the postscript output\n (default='1e-5').  */
  char * bppmThreshold_orig;	/**< @brief Set the threshold for base pair probabilities included in the postscript output\n original value given at command line.  */
  const char *bppmThreshold_help; /**< @brief Set the threshold for base pair probabilities included in the postscript output\n help description.  */
  double temp_arg;	/**< @brief Rescale energy parameters to a temperature of temp C. Default is 37C.\n\n.  */
  char * temp_orig;	/**< @brief Rescale energy parameters to a temperature of temp C. Default is 37C.\n\n original value given at command line.  */
  const char *temp_help; /**< @brief Rescale energy parameters to a temperature of temp C. Default is 37C.\n\n help description.  */
  int noTetra_flag;	/**< @brief Do not include special stabilizing energies for certain tetra-loops. Mostly for testing.\n\n (default=off).  */
  const char *noTetra_help; /**< @brief Do not include special stabilizing energies for certain tetra-loops. Mostly for testing.\n\n help description.  */
  int dangles_arg;	/**< @brief How to treat \"dangling end\" energies for bases adjacent to helices in free ends and multi-loops\n (default='2').  */
  char * dangles_orig;	/**< @brief How to treat \"dangling end\" energies for bases adjacent to helices in free ends and multi-loops\n original value given at command line.  */
  const char *dangles_help; /**< @brief How to treat \"dangling end\" energies for bases adjacent to helices in free ends and multi-loops\n help description.  */
  int noLP_flag;	/**< @brief Produce structures without lonely pairs (helices of length 1).\n (default=off).  */
  const char *noLP_help; /**< @brief Produce structures without lonely pairs (helices of length 1).\n help description.  */
  int noGU_flag;	/**< @brief Do not allow GU pairs\n\n (default=off).  */
  const char *noGU_help; /**< @brief Do not allow GU pairs\n\n help description.  */
  int noClosingGU_flag;	/**< @brief Do not allow GU pairs at the end of helices\n\n (default=off).  */
  const char *noClosingGU_help; /**< @brief Do not allow GU pairs at the end of helices\n\n help description.  */
  char * paramFile_arg;	/**< @brief Read energy parameters from paramfile, instead of using the default parameter set.\n.  */
  char * paramFile_orig;	/**< @brief Read energy parameters from paramfile, instead of using the default parameter set.\n original value given at command line.  */
  const char *paramFile_help; /**< @brief Read energy parameters from paramfile, instead of using the default parameter set.\n help description.  */
  char * nsp_arg;	/**< @brief Allow other pairs in addition to the usual AU,GC,and GU pairs.\n.  */
  char * nsp_orig;	/**< @brief Allow other pairs in addition to the usual AU,GC,and GU pairs.\n original value given at command line.  */
  const char *nsp_help; /**< @brief Allow other pairs in addition to the usual AU,GC,and GU pairs.\n help description.  */
  int energyModel_arg;	/**< @brief Rarely used option to fold sequences from the artificial ABCD... alphabet, where A pairs B, C-D etc.  Use the energy parameters for GC (-e 1) or AU (-e 2) pairs.\n\n.  */
  char * energyModel_orig;	/**< @brief Rarely used option to fold sequences from the artificial ABCD... alphabet, where A pairs B, C-D etc.  Use the energy parameters for GC (-e 1) or AU (-e 2) pairs.\n\n original value given at command line.  */
  const char *energyModel_help; /**< @brief Rarely used option to fold sequences from the artificial ABCD... alphabet, where A pairs B, C-D etc.  Use the energy parameters for GC (-e 1) or AU (-e 2) pairs.\n\n help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int detailed_help_given ;	/**< @brief Whether detailed-help was given.  */
  unsigned int full_help_given ;	/**< @brief Whether full-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int constraint_given ;	/**< @brief Whether constraint was given.  */
  unsigned int noconv_given ;	/**< @brief Whether noconv was given.  */
  unsigned int noPS_given ;	/**< @brief Whether noPS was given.  */
  unsigned int partfunc_given ;	/**< @brief Whether partfunc was given.  */
  unsigned int all_pf_given ;	/**< @brief Whether all_pf was given.  */
  unsigned int concentrations_given ;	/**< @brief Whether concentrations was given.  */
  unsigned int concfile_given ;	/**< @brief Whether concfile was given.  */
  unsigned int pfScale_given ;	/**< @brief Whether pfScale was given.  */
  unsigned int bppmThreshold_given ;	/**< @brief Whether bppmThreshold was given.  */
  unsigned int temp_given ;	/**< @brief Whether temp was given.  */
  unsigned int noTetra_given ;	/**< @brief Whether noTetra was given.  */
  unsigned int dangles_given ;	/**< @brief Whether dangles was given.  */
  unsigned int noLP_given ;	/**< @brief Whether noLP was given.  */
  unsigned int noGU_given ;	/**< @brief Whether noGU was given.  */
  unsigned int noClosingGU_given ;	/**< @brief Whether noClosingGU was given.  */
  unsigned int paramFile_given ;	/**< @brief Whether paramFile was given.  */
  unsigned int nsp_given ;	/**< @brief Whether nsp was given.  */
  unsigned int energyModel_given ;	/**< @brief Whether energyModel was given.  */

} ;

/** @brief The additional parameters to pass to parser functions */
struct RNAcofold_cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure RNAcofold_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure RNAcofold_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *RNAcofold_args_info_purpose;
/** @brief the usage string of the program */
extern const char *RNAcofold_args_info_usage;
/** @brief all the lines making the help output */
extern const char *RNAcofold_args_info_help[];
/** @brief all the lines making the full help output (including hidden options) */
extern const char *RNAcofold_args_info_full_help[];
/** @brief all the lines making the detailed help output (including hidden options and details) */
extern const char *RNAcofold_args_info_detailed_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAcofold_cmdline_parser (int argc, char **argv,
  struct RNAcofold_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use RNAcofold_cmdline_parser_ext() instead
 */
int RNAcofold_cmdline_parser2 (int argc, char **argv,
  struct RNAcofold_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAcofold_cmdline_parser_ext (int argc, char **argv,
  struct RNAcofold_args_info *args_info,
  struct RNAcofold_cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAcofold_cmdline_parser_dump(FILE *outfile,
  struct RNAcofold_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAcofold_cmdline_parser_file_save(const char *filename,
  struct RNAcofold_args_info *args_info);

/**
 * Print the help
 */
void RNAcofold_cmdline_parser_print_help(void);
/**
 * Print the full help (including hidden options)
 */
void RNAcofold_cmdline_parser_print_full_help(void);
/**
 * Print the detailed help (including hidden options and details)
 */
void RNAcofold_cmdline_parser_print_detailed_help(void);
/**
 * Print the version
 */
void RNAcofold_cmdline_parser_print_version(void);

/**
 * Initializes all the fields a RNAcofold_cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void RNAcofold_cmdline_parser_params_init(struct RNAcofold_cmdline_parser_params *params);

/**
 * Allocates dynamically a RNAcofold_cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized RNAcofold_cmdline_parser_params structure
 */
struct RNAcofold_cmdline_parser_params *RNAcofold_cmdline_parser_params_create(void);

/**
 * Initializes the passed RNAcofold_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void RNAcofold_cmdline_parser_init (struct RNAcofold_args_info *args_info);
/**
 * Deallocates the string fields of the RNAcofold_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void RNAcofold_cmdline_parser_free (struct RNAcofold_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int RNAcofold_cmdline_parser_required (struct RNAcofold_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RNACOFOLD_CMDL_H */
