/*
    include.h

    c 1994 Walter Fontana  
 */

#ifndef	__INCLUDE_H
#define	__INCLUDE_H

typedef int boolean;
typedef int bool;

#define BUFSIZE	  10000

#define TRUE	  1
#define true	  1
#define FALSE	  0
#define false	  0

#define PUBLIC
#define PRIVATE	  static
#define EXTERN	  extern

#define MIN(a,b)  ( ((a) < (b)) ? (a) : (b))

#endif /* __INCLUDE_H */
