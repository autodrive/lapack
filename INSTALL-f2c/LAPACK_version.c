/* LAPACK_version.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;

/* > \brief \b LAPACK_VERSION */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/*  Definition: */
/*  =========== */

/*      PROGRAM LAPACK_VERSION */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup auxOTHERauxiliary */

/*  =====================================================================      PROGRAM LAPACK_VERSION */

/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */

/* Main program */ int MAIN__(void)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer patch, major, minor;
    extern /* Subroutine */ int ilaver_(integer *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 6, 0, 0, 0 };



    ilaver_(&major, &minor, &patch);
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "LAPACK ", (ftnlen)7);
    do_lio(&c__3, &c__1, (char *)&major, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, ".", (ftnlen)1);
    do_lio(&c__3, &c__1, (char *)&minor, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, ".", (ftnlen)1);
    do_lio(&c__3, &c__1, (char *)&patch, (ftnlen)sizeof(integer));
    e_wsle();

    return 0;
} /* MAIN__ */

