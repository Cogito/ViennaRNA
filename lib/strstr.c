/*
	strstr - public-domain implementation of standard C library function

	last edit:	24-Aug-1990	D A Gwyn

	This is an original implementation based on an idea by D M Sunday,
	essentially the "quick search" algorithm described in CACM V33 N8.
	Unlike Sunday's implementation, this one does not wander past the
	ends of the strings (which can cause malfunctions under certain
	circumstances), nor does it require the length of the searched
	text to be determined in advance.  There are numerous other subtle
	improvements too.  The code is intended to be fully portable, but in
	environments that do not conform to the C standard, you should check
	the sections below marked "configure as required".  There are also
	a few compilation options, as follows:

	#define ROBUST	to obtain sane behavior when invoked with a null
			pointer argument, at a miniscule cost in speed
	#define ZAP	to use memset() to zero the shift[] array; this may
			be faster in some implementations, but could fail on
			unusual architectures
	#define DEBUG	to enable assertions (bug detection)
	#define TEST	to enable the test program attached at the end
*/
#define ROBUST
#define	ZAP

#ifdef __STDC__

#include	<stddef.h>		/* defines size_t and NULL */
#include	<limits.h>		/* defines UCHAR_MAX */

#ifdef ZAP
typedef void	*pointer;
extern pointer	memset( pointer, int, size_t );
#endif

#else	/* normal UNIX-like C environment assumed; configure as required: */

typedef unsigned	size_t; 	/* type of result of sizeof */

#define	NULL		0		/* null pointer constant */

#define	UCHAR_MAX	255		/* largest value of unsigned char */
					/* 255 @ 8 bits, 65535 @ 16 bits */

#ifdef ZAP
typedef char	*pointer;
extern pointer	memset();
#endif

#define const	/* nothing */

#endif	/* __STDC__ */

#ifndef DEBUG
#define	NDEBUG
#endif
#include	<assert.h>

typedef const unsigned char	cuc;	/* char variety used in algorithm */

#define EOS	'\0'			/* C string terminator */

char *					/* returns -> leftmost occurrence,
					   or null pointer if not present */
strstr( s1, s2 )
	const char	*s1;		/* -> string to be searched */
	const char	*s2;		/* -> search-pattern string */
	{
	register cuc	*t;		/* -> text character being tested */
	register cuc	*p;		/* -> pattern char being tested */
	register cuc	*tx;		/* -> possible start of match */
	register size_t	m;		/* length of pattern */
#if UCHAR_MAX > 255			/* too large for auto allocation */
	static				/* not malloc()ed; that can fail! */
#endif					/* else allocate shift[] on stack */
		size_t	shift[UCHAR_MAX + 1];	/* pattern shift table */

#ifdef ROBUST				/* not required by C standard */
	if ( s1 == NULL || s2 == NULL )
		return NULL;		/* certainly, no match is found! */
#endif

	/* Precompute shift intervals based on the pattern;
	   the length of the pattern is determined as a side effect: */

#ifdef ZAP
	(void)memset( (pointer)&shift[1], 0, UCHAR_MAX * sizeof(size_t) );
#else
	{
	register unsigned char	c;

	c = UCHAR_MAX;
	do
		shift[c] = 0;
	while ( --c > 0 );
	}
#endif
	/* Note: shift[0] is undefined at this point (fixed later). */

	for ( m = 1, p = (cuc *)s2; *p != EOS; ++m, ++p )
		shift[(cuc)*p] = m;

	assert(s2[m - 1] == EOS);

	{
	register unsigned char	c;

	c = UCHAR_MAX;
	do
		shift[c] = m - shift[c];
	while ( --c > 0 );

	/* Note: shift[0] is still undefined at this point. */
	}

	shift[0] = --m; 		/* shift[EOS]; important details! */

	assert(s2[m] == EOS);

	/* Try to find the pattern in the text string: */

	for ( tx = (cuc *)s1; ; tx += shift[*t] )
		{
		for ( t = tx, p = (cuc *)s2; ; ++t, ++p )
			{
			if ( *p == EOS )       /* entire pattern matched */
				return (char *)tx;

			if ( *p != *t )
				break;
			}

		do	{
			assert(m > 0);
			assert(t - tx < m);

			if ( *t == EOS )
				return NULL;	/* no match */
			}
		while ( ++t - tx != m );	/* < */
		}
	}

#ifdef TEST

#ifdef __STDC__

#include	<stdlib.h>		/* defines exit, EXIT_* */

#else	/* normal UNIX-like C environment assumed; configure as required: */

extern void	exit();
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

#endif	/* __STDC__ */

#include	<stdio.h>

int
main( argc, argv )
	int		argc;
	char		*argv[];
	{
	register char	*p;

	if ( argc < 3 )
		{
		(void)fprintf( stderr, "usage: strstr text pattern\n" );
		exit( EXIT_FAILURE );
		}

	if ( (p = strstr( argv[1], argv[2] )) == NULL )
		(void)printf( "pattern not found\n" );
	else
		(void)printf( "pattern start: %s\n", p );

	return EXIT_SUCCESS;
	}

#endif	/* TEST */
