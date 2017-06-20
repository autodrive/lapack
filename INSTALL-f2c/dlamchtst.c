/* dlamchtst.f -- translated by f2c (version 20100827).
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
static integer c__5 = 5;

/* > \brief \b DLAMCHTST */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/*  Definition: */
/*  =========== */

/*      PROGRAM DLAMCHTST */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup auxOTHERauxiliary */

/*  =====================================================================      PROGRAM DLAMCHTST */

/*  -- LAPACK test routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */

/* ===================================================================== */

/*     .. Local Scalars .. */
/* Main program */ int MAIN__(void)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal t, rnd, eps, base, emin, prec, emax, rmin, rmax, sfmin;
    extern doublereal dlamch_(char *, ftnlen);

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 6, 0, 0, 0 };
    static cilist io___12 = { 0, 6, 0, 0, 0 };
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 6, 0, 0, 0 };
    static cilist io___15 = { 0, 6, 0, 0, 0 };
    static cilist io___16 = { 0, 6, 0, 0, 0 };
    static cilist io___17 = { 0, 6, 0, 0, 0 };
    static cilist io___18 = { 0, 6, 0, 0, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };
    static cilist io___21 = { 0, 6, 0, 0, 0 };


/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    eps = dlamch_("Epsilon", (ftnlen)7);
    sfmin = dlamch_("Safe minimum", (ftnlen)12);
    base = dlamch_("Base", (ftnlen)4);
    prec = dlamch_("Precision", (ftnlen)9);
    t = dlamch_("Number of digits in mantissa", (ftnlen)28);
    rnd = dlamch_("Rounding mode", (ftnlen)13);
    emin = dlamch_("Minimum exponent", (ftnlen)16);
    rmin = dlamch_("Underflow threshold", (ftnlen)19);
    emax = dlamch_("Largest exponent", (ftnlen)16);
    rmax = dlamch_("Overflow threshold", (ftnlen)18);

    s_wsle(&io___11);
    do_lio(&c__9, &c__1, " Epsilon                      = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&eps, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___12);
    do_lio(&c__9, &c__1, " Safe minimum                 = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&sfmin, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___13);
    do_lio(&c__9, &c__1, " Base                         = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&base, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___14);
    do_lio(&c__9, &c__1, " Precision                    = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&prec, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___15);
    do_lio(&c__9, &c__1, " Number of digits in mantissa = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&t, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___16);
    do_lio(&c__9, &c__1, " Rounding mode                = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&rnd, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___17);
    do_lio(&c__9, &c__1, " Minimum exponent             = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&emin, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___18);
    do_lio(&c__9, &c__1, " Underflow threshold          = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&rmin, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___19);
    do_lio(&c__9, &c__1, " Largest exponent             = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&emax, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___20);
    do_lio(&c__9, &c__1, " Overflow threshold           = ", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&rmax, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___21);
    do_lio(&c__9, &c__1, " Reciprocal of safe minimum   = ", (ftnlen)32);
    d__1 = 1 / sfmin;
    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    e_wsle();

    return 0;
} /* MAIN__ */

