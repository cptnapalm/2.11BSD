#if	!defined(lint) && defined(DOSCCS)
static char *sccsid = "@(#)num.c	4.2.1 (2.11BSD) 1997/7/29";
#endif

#include	<stdio.h>
#define		formfeed 0xc

/*
 * number - a cat like program which prints a file with line
 *	    numbers. Printing of numbers is suppressed on blank
 *	    lines.
 *
 * Original Version by William Joy, June 1977
 * Updated October 1979 by M. Kirk McKusick
 * Updated to version 4.2 10/13/82
 */
main(ac, av)
	int ac;
	char *av[];
	{
	register int argc = ac;
	register char **argv = av;
	register int lino;
	register char *lineptr;
	register FILE *STDOUT = stdout;
	register FILE *STDIN = stdin;
	char line[512];
	char stdobuf[BUFSIZ], stdibuf[BUFSIZ];

	argv++;
	argc--;
	lino = 1;
	setbuf(STDIN,stdibuf);
	setbuf(STDOUT,stdobuf);
	do
		{
		if (argc)
			if (freopen(*argv++, "r", STDIN) == NULL)
				{
				perror(*--argv);
				exit(1);
				}
		for(;;)
			{
			lineptr = line;
			*lineptr = 0;
			fscanf(STDIN,"%[^\n]",lineptr);
			if (feof(STDIN))
				break;
			if (*lineptr == formfeed)
				putc(*lineptr++,STDOUT);
			if (!*lineptr)
				putc('\n',STDOUT);
			else
				fprintf(STDOUT,"%6d  %s\n",lino,lineptr);
			lino++;
			getc(STDIN);
			}
		}
		while (--argc > 0);
	exit();
	}
