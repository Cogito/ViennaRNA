/** @file RNAdistance_cmdl.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.6
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef RNADISTANCE_CMDL_H
#define RNADISTANCE_CMDL_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef RNADISTANCE_CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define RNADISTANCE_CMDLINE_PARSER_PACKAGE "RNAdistance"
#endif

#ifndef RNADISTANCE_CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define RNADISTANCE_CMDLINE_PARSER_PACKAGE_NAME "RNAdistance"
#endif

#ifndef RNADISTANCE_CMDLINE_PARSER_VERSION
/** @brief the program version */
#define RNADISTANCE_CMDLINE_PARSER_VERSION VERSION
#endif

/** @brief Where the command line options are stored */
struct RNAdistance_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *detailed_help_help; /**< @brief Print help, including all details and hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  char * distance_arg;	/**< @brief Specify the distance representation to be used in calculations.
 (default='f').  */
  char * distance_orig;	/**< @brief Specify the distance representation to be used in calculations.
 original value given at command line.  */
  const char *distance_help; /**< @brief Specify the distance representation to be used in calculations.
 help description.  */
  char * compare_arg;	/**< @brief Specify the comparison directive.
 (default='p').  */
  char * compare_orig;	/**< @brief Specify the comparison directive.
 original value given at command line.  */
  const char *compare_help; /**< @brief Specify the comparison directive.
 help description.  */
  int shapiro_flag;	/**< @brief Use the Bruce Shapiro's cost matrix for comparing coarse structures.
  
 (default=off).  */
  const char *shapiro_help; /**< @brief Use the Bruce Shapiro's cost matrix for comparing coarse structures.
  
 help description.  */
  char * backtrack_arg;	/**< @brief Print an \"alignment\" with gaps of the structures, to show matching substructures. The aligned structures are written to <filename>, if specified.
 (default='none').  */
  char * backtrack_orig;	/**< @brief Print an \"alignment\" with gaps of the structures, to show matching substructures. The aligned structures are written to <filename>, if specified.
 original value given at command line.  */
  const char *backtrack_help; /**< @brief Print an \"alignment\" with gaps of the structures, to show matching substructures. The aligned structures are written to <filename>, if specified.
 help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int detailed_help_given ;	/**< @brief Whether detailed-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int distance_given ;	/**< @brief Whether distance was given.  */
  unsigned int compare_given ;	/**< @brief Whether compare was given.  */
  unsigned int shapiro_given ;	/**< @brief Whether shapiro was given.  */
  unsigned int backtrack_given ;	/**< @brief Whether backtrack was given.  */

} ;

/** @brief The additional parameters to pass to parser functions */
struct RNAdistance_cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure RNAdistance_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure RNAdistance_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *RNAdistance_args_info_purpose;
/** @brief the usage string of the program */
extern const char *RNAdistance_args_info_usage;
/** @brief the description string of the program */
extern const char *RNAdistance_args_info_description;
/** @brief all the lines making the help output */
extern const char *RNAdistance_args_info_help[];
/** @brief all the lines making the detailed help output (including hidden options and details) */
extern const char *RNAdistance_args_info_detailed_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAdistance_cmdline_parser (int argc, char **argv,
  struct RNAdistance_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use RNAdistance_cmdline_parser_ext() instead
 */
int RNAdistance_cmdline_parser2 (int argc, char **argv,
  struct RNAdistance_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAdistance_cmdline_parser_ext (int argc, char **argv,
  struct RNAdistance_args_info *args_info,
  struct RNAdistance_cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAdistance_cmdline_parser_dump(FILE *outfile,
  struct RNAdistance_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int RNAdistance_cmdline_parser_file_save(const char *filename,
  struct RNAdistance_args_info *args_info);

/**
 * Print the help
 */
void RNAdistance_cmdline_parser_print_help(void);
/**
 * Print the detailed help (including hidden options and details)
 */
void RNAdistance_cmdline_parser_print_detailed_help(void);
/**
 * Print the version
 */
void RNAdistance_cmdline_parser_print_version(void);

/**
 * Initializes all the fields a RNAdistance_cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void RNAdistance_cmdline_parser_params_init(struct RNAdistance_cmdline_parser_params *params);

/**
 * Allocates dynamically a RNAdistance_cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized RNAdistance_cmdline_parser_params structure
 */
struct RNAdistance_cmdline_parser_params *RNAdistance_cmdline_parser_params_create(void);

/**
 * Initializes the passed RNAdistance_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void RNAdistance_cmdline_parser_init (struct RNAdistance_args_info *args_info);
/**
 * Deallocates the string fields of the RNAdistance_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void RNAdistance_cmdline_parser_free (struct RNAdistance_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int RNAdistance_cmdline_parser_required (struct RNAdistance_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RNADISTANCE_CMDL_H */
