/* cheev_2stage.f -- translated by f2c (version 20100827).
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

static integer c__17 = 17;
static integer c_n1 = -1;
static integer c__18 = 18;
static integer c__19 = 19;
static integer c__20 = 20;
static integer c__0 = 0;
static real c_b28 = 1.f;
static integer c__1 = 1;

/* > \brief <b> CHEEV_2STAGE computes the eigenvalues and, optionally, the left and/or right eigenvectors for 
HE matrices</b> */

/*  @generated from zheev_2stage.f, fortran z -> c, Sat Nov  5 23:18:06 2016 */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CHEEV_2STAGE + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/cheev_2
stage.f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/cheev_2
stage.f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/cheev_2
stage.f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CHEEV_2STAGE( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, */
/*                                RWORK, INFO ) */

/*       IMPLICIT NONE */

/*       .. Scalar Arguments .. */
/*       CHARACTER          JOBZ, UPLO */
/*       INTEGER            INFO, LDA, LWORK, N */
/*       .. */
/*       .. Array Arguments .. */
/*       REAL               RWORK( * ), W( * ) */
/*       COMPLEX            A( LDA, * ), WORK( * ) */
/*       .. */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CHEEV_2STAGE computes all eigenvalues and, optionally, eigenvectors of a */
/* > complex Hermitian matrix A using the 2stage technique for */
/* > the reduction to tridiagonal. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] JOBZ */
/* > \verbatim */
/* >          JOBZ is CHARACTER*1 */
/* >          = 'N':  Compute eigenvalues only; */
/* >          = 'V':  Compute eigenvalues and eigenvectors. */
/* >                  Not available in this release. */
/* > \endverbatim */
/* > */
/* > \param[in] UPLO */
/* > \verbatim */
/* >          UPLO is CHARACTER*1 */
/* >          = 'U':  Upper triangle of A is stored; */
/* >          = 'L':  Lower triangle of A is stored. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension (LDA, N) */
/* >          On entry, the Hermitian matrix A.  If UPLO = 'U', the */
/* >          leading N-by-N upper triangular part of A contains the */
/* >          upper triangular part of the matrix A.  If UPLO = 'L', */
/* >          the leading N-by-N lower triangular part of A contains */
/* >          the lower triangular part of the matrix A. */
/* >          On exit, if JOBZ = 'V', then if INFO = 0, A contains the */
/* >          orthonormal eigenvectors of the matrix A. */
/* >          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L') */
/* >          or the upper triangle (if UPLO='U') of A, including the */
/* >          diagonal, is destroyed. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= max(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] W */
/* > \verbatim */
/* >          W is REAL array, dimension (N) */
/* >          If INFO = 0, the eigenvalues in ascending order. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX array, dimension (MAX(1,LWORK)) */
/* >          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */
/* > \endverbatim */
/* > */
/* > \param[in] LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >          The length of the array WORK. LWORK >= 1, when N <= 1; */
/* >          otherwise */
/* >          If JOBZ = 'N' and N > 1, LWORK must be queried. */
/* >                                   LWORK = MAX(1, dimension) where */
/* >                                   dimension = max(stage1,stage2) + (KD+1)*N + N */
/* >                                             = N*KD + N*max(KD+1,FACTOPTNB) */
/* >                                               + max(2*KD*KD, KD*NTHREADS) */
/* >                                               + (KD+1)*N + N */
/* >                                   where KD is the blocking size of the reduction, */
/* >                                   FACTOPTNB is the blocking used by the QR or LQ */
/* >                                   algorithm, usually FACTOPTNB=128 is a good choice */
/* >                                   NTHREADS is the number of threads used when */
/* >                                   openMP compilation is enabled, otherwise =1. */
/* >          If JOBZ = 'V' and N > 1, LWORK must be queried. Not yet available */
/* > */
/* >          If LWORK = -1, then a workspace query is assumed; the routine */
/* >          only calculates the optimal size of the WORK array, returns */
/* >          this value as the first entry of the WORK array, and no error */
/* >          message related to LWORK is issued by XERBLA. */
/* > \endverbatim */
/* > */
/* > \param[out] RWORK */
/* > \verbatim */
/* >          RWORK is REAL array, dimension (max(1, 3*N-2)) */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit */
/* >          < 0:  if INFO = -i, the i-th argument had an illegal value */
/* >          > 0:  if INFO = i, the algorithm failed to converge; i */
/* >                off-diagonal elements of an intermediate tridiagonal */
/* >                form did not converge to zero. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complexHEeigen */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >  All details about the 2stage techniques are available in: */
/* > */
/* >  Azzam Haidar, Hatem Ltaief, and Jack Dongarra. */
/* >  Parallel reduction to condensed forms for symmetric eigenvalue problems */
/* >  using aggregated fine-grained and memory-aware kernels. In Proceedings */
/* >  of 2011 International Conference for High Performance Computing, */
/* >  Networking, Storage and Analysis (SC '11), New York, NY, USA, */
/* >  Article 8 , 11 pages. */
/* >  http://doi.acm.org/10.1145/2063384.2063394 */
/* > */
/* >  A. Haidar, J. Kurzak, P. Luszczek, 2013. */
/* >  An improved parallel singular value algorithm and its implementation */
/* >  for multicore hardware, In Proceedings of 2013 International Conference */
/* >  for High Performance Computing, Networking, Storage and Analysis (SC '13). */
/* >  Denver, Colorado, USA, 2013. */
/* >  Article 90, 12 pages. */
/* >  http://doi.acm.org/10.1145/2503210.2503292 */
/* > */
/* >  A. Haidar, R. Solca, S. Tomov, T. Schulthess and J. Dongarra. */
/* >  A novel hybrid CPU-GPU generalized eigensolver for electronic structure */
/* >  calculations based on fine-grained memory aware tasks. */
/* >  International Journal of High Performance Computing Applications. */
/* >  Volume 28 Issue 2, Pages 196-209, May 2014. */
/* >  http://hpc.sagepub.com/content/28/2/196 */
/* > */
/* > \endverbatim */

/*  ===================================================================== */
/* Subroutine */ int cheev_2stage__(char *jobz, char *uplo, integer *n, 
	complex *a, integer *lda, real *w, complex *work, integer *lwork, 
	real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;
    real r__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer ib, kd;
    static real eps;
    static integer inde;
    static real anrm;
    static integer imax;
    static real rmin, rmax;
    extern /* Subroutine */ int chetrd_2stage__(char *, char *, integer *, 
	    complex *, integer *, real *, real *, complex *, complex *, 
	    integer *, complex *, integer *, integer *, ftnlen, ftnlen);
    static real sigma;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static integer iinfo;
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *);
    static integer lhtrd, lwmin;
    static logical lower;
    static integer lwtrd;
    static logical wantz;
    extern doublereal clanhe_(char *, char *, integer *, complex *, integer *,
	     real *, ftnlen, ftnlen);
    static integer iscale;
    extern /* Subroutine */ int clascl_(char *, integer *, integer *, real *, 
	    real *, integer *, integer *, complex *, integer *, integer *, 
	    ftnlen);
    extern doublereal slamch_(char *, ftnlen);
    static real safmin;
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    static real bignum;
    static integer indtau, indwrk;
    extern /* Subroutine */ int csteqr_(char *, integer *, real *, real *, 
	    complex *, integer *, real *, integer *, ftnlen), cungtr_(char *, 
	    integer *, complex *, integer *, complex *, complex *, integer *, 
	    integer *, ftnlen), ssterf_(integer *, real *, real *, integer *);
    static integer llwork;
    static real smlnum;
    static logical lquery;
    static integer indhous;



/*  -- LAPACK driver routine (version 3.7.0) -- */
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
    --w;
    --work;
    --rwork;

    /* Function Body */
    wantz = lsame_(jobz, "V", (ftnlen)1, (ftnlen)1);
    lower = lsame_(uplo, "L", (ftnlen)1, (ftnlen)1);
    lquery = *lwork == -1;

    *info = 0;
    if (! lsame_(jobz, "N", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (! (lower || lsame_(uplo, "U", (ftnlen)1, (ftnlen)1))) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    }

    if (*info == 0) {
	kd = ilaenv_(&c__17, "CHETRD_2STAGE", jobz, n, &c_n1, &c_n1, &c_n1, (
		ftnlen)13, (ftnlen)1);
	ib = ilaenv_(&c__18, "CHETRD_2STAGE", jobz, n, &kd, &c_n1, &c_n1, (
		ftnlen)13, (ftnlen)1);
	lhtrd = ilaenv_(&c__19, "CHETRD_2STAGE", jobz, n, &kd, &ib, &c_n1, (
		ftnlen)13, (ftnlen)1);
	lwtrd = ilaenv_(&c__20, "CHETRD_2STAGE", jobz, n, &kd, &ib, &c_n1, (
		ftnlen)13, (ftnlen)1);
	lwmin = *n + lhtrd + lwtrd;
	work[1].r = (real) lwmin, work[1].i = 0.f;

	if (*lwork < lwmin && ! lquery) {
	    *info = -8;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHEEV_2STAGE ", &i__1, (ftnlen)13);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    if (*n == 1) {
	i__1 = a_dim1 + 1;
	w[1] = a[i__1].r;
	work[1].r = 1.f, work[1].i = 0.f;
	if (wantz) {
	    i__1 = a_dim1 + 1;
	    a[i__1].r = 1.f, a[i__1].i = 0.f;
	}
	return 0;
    }

/*     Get machine constants. */

    safmin = slamch_("Safe minimum", (ftnlen)12);
    eps = slamch_("Precision", (ftnlen)9);
    smlnum = safmin / eps;
    bignum = 1.f / smlnum;
    rmin = sqrt(smlnum);
    rmax = sqrt(bignum);

/*     Scale matrix to allowable range, if necessary. */

    anrm = clanhe_("M", uplo, n, &a[a_offset], lda, &rwork[1], (ftnlen)1, (
	    ftnlen)1);
    iscale = 0;
    if (anrm > 0.f && anrm < rmin) {
	iscale = 1;
	sigma = rmin / anrm;
    } else if (anrm > rmax) {
	iscale = 1;
	sigma = rmax / anrm;
    }
    if (iscale == 1) {
	clascl_(uplo, &c__0, &c__0, &c_b28, &sigma, n, n, &a[a_offset], lda, 
		info, (ftnlen)1);
    }

/*     Call CHETRD_2STAGE to reduce Hermitian matrix to tridiagonal form. */

    inde = 1;
    indtau = 1;
    indhous = indtau + *n;
    indwrk = indhous + lhtrd;
    llwork = *lwork - indwrk + 1;

    chetrd_2stage__(jobz, uplo, n, &a[a_offset], lda, &w[1], &rwork[inde], &
	    work[indtau], &work[indhous], &lhtrd, &work[indwrk], &llwork, &
	    iinfo, (ftnlen)1, (ftnlen)1);

/*     For eigenvalues only, call SSTERF.  For eigenvectors, first call */
/*     CUNGTR to generate the unitary matrix, then call CSTEQR. */

    if (! wantz) {
	ssterf_(n, &w[1], &rwork[inde], info);
    } else {
	cungtr_(uplo, n, &a[a_offset], lda, &work[indtau], &work[indwrk], &
		llwork, &iinfo, (ftnlen)1);
	indwrk = inde + *n;
	csteqr_(jobz, n, &w[1], &rwork[inde], &a[a_offset], lda, &rwork[
		indwrk], info, (ftnlen)1);
    }

/*     If matrix was scaled, then rescale eigenvalues appropriately. */

    if (iscale == 1) {
	if (*info == 0) {
	    imax = *n;
	} else {
	    imax = *info - 1;
	}
	r__1 = 1.f / sigma;
	sscal_(&imax, &r__1, &w[1], &c__1);
    }

/*     Set WORK(1) to optimal complex workspace size. */

    work[1].r = (real) lwmin, work[1].i = 0.f;

    return 0;

/*     End of CHEEV_2STAGE */

} /* cheev_2stage__ */

