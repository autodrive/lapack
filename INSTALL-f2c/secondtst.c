/* secondtst.f -- translated by f2c (version 20100827).
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

static integer c__1 = 1;
static integer c__1000 = 1000;

/* > \brief \b SECONDTST */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */


/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup auxOTHERcomputational */

/*  =====================================================================      PROGRAM SECONDTST */

/*  -- LAPACK test routine (version 3.7.0) -- */

/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */

/* ===================================================================== */

/*     .. Parameters .. */
/* Main program */ int MAIN__(void)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 Time for \002,g10.3,\002 SAXPY ops = "
	    "\002,g10.3,\002 seconds\002)";
    static char fmt_9998[] = "(\002 SAXPY performance rate        = \002,g10"
	    ".3,\002 mflops \002)";
    static char fmt_9994[] = "(\002 *** Warning:  Time for operations was le"
	    "ss or equal\002,\002 than zero => timing in TESTING might be dub"
	    "ious\002)";
    static char fmt_9997[] = "(\002 Including SECOND, time        = \002,g10"
	    ".3,\002 seconds\002)";
    static char fmt_9996[] = "(\002 Average time for SECOND       = \002,g10"
	    ".3,\002 milliseconds\002)";
    static char fmt_9995[] = "(\002 Equivalent floating point ops = \002,g10"
	    ".3,\002 ops\002)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j;
    static real x[1000], y[1000], t1, t2, avg, alpha, total;
    extern /* Subroutine */ int mysub_(integer *, real *, real *);
    extern doublereal second_(void);
    static real tnosec;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 6, 0, fmt_9999, 0 };
    static cilist io___11 = { 0, 6, 0, fmt_9998, 0 };
    static cilist io___12 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___13 = { 0, 6, 0, fmt_9997, 0 };
    static cilist io___15 = { 0, 6, 0, fmt_9996, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_9995, 0 };


/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*    .. Figure TOTAL flops .. */
    total = 1e8f;

/*     Initialize X and Y */

    for (i__ = 1; i__ <= 1000; ++i__) {
	x[i__ - 1] = 1.f / (real) i__;
	y[i__ - 1] = (real) (1000 - i__) / 1e3f;
/* L10: */
    }
    alpha = .315f;

/*     Time TOTAL SAXPY operations */

    t1 = second_();
    for (j = 1; j <= 50000; ++j) {
	for (i__ = 1; i__ <= 1000; ++i__) {
	    y[i__ - 1] += alpha * x[i__ - 1];
/* L20: */
	}
	alpha = -alpha;
/* L30: */
    }
    t2 = second_();
    tnosec = t2 - t1;
    s_wsfe(&io___10);
    do_fio(&c__1, (char *)&total, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&tnosec, (ftnlen)sizeof(real));
    e_wsfe();
    if (tnosec > 0.f) {
	s_wsfe(&io___11);
	r__1 = total / 1e6f / tnosec;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    } else {
	s_wsfe(&io___12);
	e_wsfe();
    }

/*     Time TOTAL SAXPY operations with SECOND in the outer loop */

    t1 = second_();
    for (j = 1; j <= 50000; ++j) {
	for (i__ = 1; i__ <= 1000; ++i__) {
	    y[i__ - 1] += alpha * x[i__ - 1];
/* L40: */
	}
	alpha = -alpha;
	t2 = second_();
/* L50: */
    }

/*     Compute the time used in milliseconds used by an average call */
/*     to SECOND. */

    s_wsfe(&io___13);
    r__1 = t2 - t1;
    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
    e_wsfe();
    avg = (t2 - t1 - tnosec) * 1e3f / 5e4f;
    if (avg > 0.f) {
	s_wsfe(&io___15);
	do_fio(&c__1, (char *)&avg, (ftnlen)sizeof(real));
	e_wsfe();
    }

/*     Compute the equivalent number of floating point operations used */
/*     by an average call to SECOND. */

    if (avg > 0.f && tnosec > 0.f) {
	s_wsfe(&io___16);
	r__1 = avg / 1000 * total / tnosec;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    }

    mysub_(&c__1000, x, y);
    return 0;
} /* MAIN__ */

/* Subroutine */ int mysub_(integer *n, real *x, real *y)
{
    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    return 0;
} /* mysub_ */

