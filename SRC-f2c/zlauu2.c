/* zlauu2.f -- translated by f2c (version 20100827).
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

static doublecomplex c_b1 = {1.,0.};
static integer c__1 = 1;

/* > \brief \b ZLAUU2 computes the product UUH or LHL, where U and L are upper or lower triangular matrices (u
nblocked algorithm). */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download ZLAUU2 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/zlauu2.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/zlauu2.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/zlauu2.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE ZLAUU2( UPLO, N, A, LDA, INFO ) */

/*       .. Scalar Arguments .. */
/*       CHARACTER          UPLO */
/*       INTEGER            INFO, LDA, N */
/*       .. */
/*       .. Array Arguments .. */
/*       COMPLEX*16         A( LDA, * ) */
/*       .. */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > ZLAUU2 computes the product U * U**H or L**H * L, where the triangular */
/* > factor U or L is stored in the upper or lower triangular part of */
/* > the array A. */
/* > */
/* > If UPLO = 'U' or 'u' then the upper triangle of the result is stored, */
/* > overwriting the factor U in A. */
/* > If UPLO = 'L' or 'l' then the lower triangle of the result is stored, */
/* > overwriting the factor L in A. */
/* > */
/* > This is the unblocked form of the algorithm, calling Level 2 BLAS. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] UPLO */
/* > \verbatim */
/* >          UPLO is CHARACTER*1 */
/* >          Specifies whether the triangular factor stored in the array A */
/* >          is upper or lower triangular: */
/* >          = 'U':  Upper triangular */
/* >          = 'L':  Lower triangular */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the triangular factor U or L.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX*16 array, dimension (LDA,N) */
/* >          On entry, the triangular factor U or L. */
/* >          On exit, if UPLO = 'U', the upper triangle of A is */
/* >          overwritten with the upper triangle of the product U * U**H; */
/* >          if UPLO = 'L', the lower triangle of A is overwritten with */
/* >          the lower triangle of the product L**H * L. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= max(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0: successful exit */
/* >          < 0: if INFO = -k, the k-th argument had an illegal value */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complex16OTHERauxiliary */

/*  ===================================================================== */
/* Subroutine */ int zlauu2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;
    doublecomplex z__1;

    /* Local variables */
    static integer i__;
    static doublereal aii;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen);
    static logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen), zdscal_(
	    integer *, doublereal *, doublecomplex *, integer *), zlacgv_(
	    integer *, doublecomplex *, integer *);


/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", (ftnlen)1, (ftnlen)1);
    if (! upper && ! lsame_(uplo, "L", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZLAUU2", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    if (upper) {

/*        Compute the product U * U**H. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__ + i__ * a_dim1;
	    aii = a[i__2].r;
	    if (i__ < *n) {
		i__2 = i__ + i__ * a_dim1;
		i__3 = *n - i__;
		zdotc_(&z__1, &i__3, &a[i__ + (i__ + 1) * a_dim1], lda, &a[
			i__ + (i__ + 1) * a_dim1], lda);
		d__1 = aii * aii + z__1.r;
		a[i__2].r = d__1, a[i__2].i = 0.;
		i__2 = *n - i__;
		zlacgv_(&i__2, &a[i__ + (i__ + 1) * a_dim1], lda);
		i__2 = i__ - 1;
		i__3 = *n - i__;
		z__1.r = aii, z__1.i = 0.;
		zgemv_("No transpose", &i__2, &i__3, &c_b1, &a[(i__ + 1) * 
			a_dim1 + 1], lda, &a[i__ + (i__ + 1) * a_dim1], lda, &
			z__1, &a[i__ * a_dim1 + 1], &c__1, (ftnlen)12);
		i__2 = *n - i__;
		zlacgv_(&i__2, &a[i__ + (i__ + 1) * a_dim1], lda);
	    } else {
		zdscal_(&i__, &aii, &a[i__ * a_dim1 + 1], &c__1);
	    }
/* L10: */
	}

    } else {

/*        Compute the product L**H * L. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__ + i__ * a_dim1;
	    aii = a[i__2].r;
	    if (i__ < *n) {
		i__2 = i__ + i__ * a_dim1;
		i__3 = *n - i__;
		zdotc_(&z__1, &i__3, &a[i__ + 1 + i__ * a_dim1], &c__1, &a[
			i__ + 1 + i__ * a_dim1], &c__1);
		d__1 = aii * aii + z__1.r;
		a[i__2].r = d__1, a[i__2].i = 0.;
		i__2 = i__ - 1;
		zlacgv_(&i__2, &a[i__ + a_dim1], lda);
		i__2 = *n - i__;
		i__3 = i__ - 1;
		z__1.r = aii, z__1.i = 0.;
		zgemv_("Conjugate transpose", &i__2, &i__3, &c_b1, &a[i__ + 1 
			+ a_dim1], lda, &a[i__ + 1 + i__ * a_dim1], &c__1, &
			z__1, &a[i__ + a_dim1], lda, (ftnlen)19);
		i__2 = i__ - 1;
		zlacgv_(&i__2, &a[i__ + a_dim1], lda);
	    } else {
		zdscal_(&i__, &aii, &a[i__ + a_dim1], lda);
	    }
/* L20: */
	}
    }

    return 0;

/*     End of ZLAUU2 */

} /* zlauu2_ */

