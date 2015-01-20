/** @file ct2db_cmdl.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.5
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef CT2DB_CMDL_H
#define CT2DB_CMDL_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CT2DB_CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define CT2DB_CMDLINE_PARSER_PACKAGE "ct2db"
#endif

#ifndef CT2DB_CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define CT2DB_CMDLINE_PARSER_PACKAGE_NAME "ct2db"
#endif

#ifndef CT2DB_CMDLINE_PARSER_VERSION
/** @brief the program version */
#define CT2DB_CMDLINE_PARSER_VERSION "1.0"
#endif

/** @brief Where the command line options are stored */
struct ct2db_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  int removePK_flag;	/**< @brief Remove pseudoknots from structure
 (default=off).  */
  const char *removePK_help; /**< @brief Remove pseudoknots from structure
 help description.  */
  int verbose_flag;	/**< @brief Be verbose
 (default=off).  */
  const char *verbose_help; /**< @brief Be verbose
 help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int removePK_given ;	/**< @brief Whether removePK was given.  */
  unsigned int verbose_given ;	/**< @brief Whether verbose was given.  */

  char **inputs ; /**< @brief unamed options (options without names) */
  unsigned inputs_num ; /**< @brief unamed options number */
} ;

/** @brief The additional parameters to pass to parser functions */
struct ct2db_cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure ct2db_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure ct2db_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *ct2db_args_info_purpose;
/** @brief the usage string of the program */
extern const char *ct2db_args_info_usage;
/** @brief all the lines making the help output */
extern const char *ct2db_args_info_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int ct2db_cmdline_parser (int argc, char **argv,
  struct ct2db_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use ct2db_cmdline_parser_ext() instead
 */
int ct2db_cmdline_parser2 (int argc, char **argv,
  struct ct2db_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int ct2db_cmdline_parser_ext (int argc, char **argv,
  struct ct2db_args_info *args_info,
  struct ct2db_cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int ct2db_cmdline_parser_dump(FILE *outfile,
  struct ct2db_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int ct2db_cmdline_parser_file_save(const char *filename,
  struct ct2db_args_info *args_info);

/**
 * Print the help
 */
void ct2db_cmdline_parser_print_help(void);
/**
 * Print the version
 */
void ct2db_cmdline_parser_print_version(void);

/**
 * Initializes all the fields a ct2db_cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void ct2db_cmdline_parser_params_init(struct ct2db_cmdline_parser_params *params);

/**
 * Allocates dynamically a ct2db_cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized ct2db_cmdline_parser_params structure
 */
struct ct2db_cmdline_parser_params *ct2db_cmdline_parser_params_create(void);

/**
 * Initializes the passed ct2db_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void ct2db_cmdline_parser_init (struct ct2db_args_info *args_info);
/**
 * Deallocates the string fields of the ct2db_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void ct2db_cmdline_parser_free (struct ct2db_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int ct2db_cmdline_parser_required (struct ct2db_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CT2DB_CMDL_H */
