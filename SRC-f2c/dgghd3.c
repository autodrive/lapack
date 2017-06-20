/* dgghd3.f -- translated by f2c (version 20100827).
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
static integer c_n1 = -1;
static doublereal c_b14 = 0.;
static doublereal c_b15 = 1.;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__16 = 16;

/* > \brief \b DGGHD3 */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download DGGHD3 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/dgghd3.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/dgghd3.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/dgghd3.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE DGGHD3( COMPQ, COMPZ, N, ILO, IHI, A, LDA, B, LDB, Q, */
/*                          LDQ, Z, LDZ, WORK, LWORK, INFO ) */

/*       .. Scalar Arguments .. */
/*       CHARACTER          COMPQ, COMPZ */
/*       INTEGER            IHI, ILO, INFO, LDA, LDB, LDQ, LDZ, N, LWORK */
/*       .. */
/*       .. Array Arguments .. */
/*       DOUBLE PRECISION   A( LDA, * ), B( LDB, * ), Q( LDQ, * ), */
/*      $                   Z( LDZ, * ), WORK( * ) */
/*       .. */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > DGGHD3 reduces a pair of real matrices (A,B) to generalized upper */
/* > Hessenberg form using orthogonal transformations, where A is a */
/* > general matrix and B is upper triangular.  The form of the */
/* > generalized eigenvalue problem is */
/* >    A*x = lambda*B*x, */
/* > and B is typically made upper triangular by computing its QR */
/* > factorization and moving the orthogonal matrix Q to the left side */
/* > of the equation. */
/* > */
/* > This subroutine simultaneously reduces A to a Hessenberg matrix H: */
/* >    Q**T*A*Z = H */
/* > and transforms B to another upper triangular matrix T: */
/* >    Q**T*B*Z = T */
/* > in order to reduce the problem to its standard form */
/* >    H*y = lambda*T*y */
/* > where y = Z**T*x. */
/* > */
/* > The orthogonal matrices Q and Z are determined as products of Givens */
/* > rotations.  They may either be formed explicitly, or they may be */
/* > postmultiplied into input matrices Q1 and Z1, so that */
/* > */
/* >      Q1 * A * Z1**T = (Q1*Q) * H * (Z1*Z)**T */
/* > */
/* >      Q1 * B * Z1**T = (Q1*Q) * T * (Z1*Z)**T */
/* > */
/* > If Q1 is the orthogonal matrix from the QR factorization of B in the */
/* > original equation A*x = lambda*B*x, then DGGHD3 reduces the original */
/* > problem to generalized Hessenberg form. */
/* > */
/* > This is a blocked variant of DGGHRD, using matrix-matrix */
/* > multiplications for parts of the computation to enhance performance. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] COMPQ */
/* > \verbatim */
/* >          COMPQ is CHARACTER*1 */
/* >          = 'N': do not compute Q; */
/* >          = 'I': Q is initialized to the unit matrix, and the */
/* >                 orthogonal matrix Q is returned; */
/* >          = 'V': Q must contain an orthogonal matrix Q1 on entry, */
/* >                 and the product Q1*Q is returned. */
/* > \endverbatim */
/* > */
/* > \param[in] COMPZ */
/* > \verbatim */
/* >          COMPZ is CHARACTER*1 */
/* >          = 'N': do not compute Z; */
/* >          = 'I': Z is initialized to the unit matrix, and the */
/* >                 orthogonal matrix Z is returned; */
/* >          = 'V': Z must contain an orthogonal matrix Z1 on entry, */
/* >                 and the product Z1*Z is returned. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrices A and B.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] ILO */
/* > \verbatim */
/* >          ILO is INTEGER */
/* > \endverbatim */
/* > */
/* > \param[in] IHI */
/* > \verbatim */
/* >          IHI is INTEGER */
/* > */
/* >          ILO and IHI mark the rows and columns of A which are to be */
/* >          reduced.  It is assumed that A is already upper triangular */
/* >          in rows and columns 1:ILO-1 and IHI+1:N.  ILO and IHI are */
/* >          normally set by a previous call to DGGBAL; otherwise they */
/* >          should be set to 1 and N respectively. */
/* >          1 <= ILO <= IHI <= N, if N > 0; ILO=1 and IHI=0, if N=0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is DOUBLE PRECISION array, dimension (LDA, N) */
/* >          On entry, the N-by-N general matrix to be reduced. */
/* >          On exit, the upper triangle and the first subdiagonal of A */
/* >          are overwritten with the upper Hessenberg matrix H, and the */
/* >          rest is set to zero. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= max(1,N). */
/* > \endverbatim */
/* > */
/* > \param[in,out] B */
/* > \verbatim */
/* >          B is DOUBLE PRECISION array, dimension (LDB, N) */
/* >          On entry, the N-by-N upper triangular matrix B. */
/* >          On exit, the upper triangular matrix T = Q**T B Z.  The */
/* >          elements below the diagonal are set to zero. */
/* > \endverbatim */
/* > */
/* > \param[in] LDB */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array B.  LDB >= max(1,N). */
/* > \endverbatim */
/* > */
/* > \param[in,out] Q */
/* > \verbatim */
/* >          Q is DOUBLE PRECISION array, dimension (LDQ, N) */
/* >          On entry, if COMPQ = 'V', the orthogonal matrix Q1, */
/* >          typically from the QR factorization of B. */
/* >          On exit, if COMPQ='I', the orthogonal matrix Q, and if */
/* >          COMPQ = 'V', the product Q1*Q. */
/* >          Not referenced if COMPQ='N'. */
/* > \endverbatim */
/* > */
/* > \param[in] LDQ */
/* > \verbatim */
/* >          LDQ is INTEGER */
/* >          The leading dimension of the array Q. */
/* >          LDQ >= N if COMPQ='V' or 'I'; LDQ >= 1 otherwise. */
/* > \endverbatim */
/* > */
/* > \param[in,out] Z */
/* > \verbatim */
/* >          Z is DOUBLE PRECISION array, dimension (LDZ, N) */
/* >          On entry, if COMPZ = 'V', the orthogonal matrix Z1. */
/* >          On exit, if COMPZ='I', the orthogonal matrix Z, and if */
/* >          COMPZ = 'V', the product Z1*Z. */
/* >          Not referenced if COMPZ='N'. */
/* > \endverbatim */
/* > */
/* > \param[in] LDZ */
/* > \verbatim */
/* >          LDZ is INTEGER */
/* >          The leading dimension of the array Z. */
/* >          LDZ >= N if COMPZ='V' or 'I'; LDZ >= 1 otherwise. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is DOUBLE PRECISION array, dimension (LWORK) */
/* >          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */
/* > \endverbatim */
/* > */
/* > \param[in]  LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >          The length of the array WORK.  LWORK >= 1. */
/* >          For optimum performance LWORK >= 6*N*NB, where NB is the */
/* >          optimal blocksize. */
/* > */
/* >          If LWORK = -1, then a workspace query is assumed; the routine */
/* >          only calculates the optimal size of the WORK array, returns */
/* >          this value as the first entry of the WORK array, and no error */
/* >          message related to LWORK is issued by XERBLA. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit. */
/* >          < 0:  if INFO = -i, the i-th argument had an illegal value. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date January 2015 */

/* > \ingroup doubleOTHERcomputational */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >  This routine reduces A to Hessenberg form and maintains B in */
/* >  using a blocked variant of Moler and Stewart's original algorithm, */
/* >  as described by Kagstrom, Kressner, Quintana-Orti, and Quintana-Orti */
/* >  (BIT 2008). */
/* > \endverbatim */
/* > */
/*  ===================================================================== */
/* Subroutine */ int dgghd3_(char *compq, char *compz, integer *n, integer *
	ilo, integer *ihi, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *q, integer *ldq, doublereal *z__, integer *
	ldz, doublereal *work, integer *lwork, integer *info, ftnlen 
	compq_len, ftnlen compz_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, q_dim1, q_offset, z_dim1, 
	    z_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8;
    doublereal d__1;

    /* Local variables */
    static doublereal c__;
    static integer i__, j, k;
    static doublereal s, c1, c2;
    static integer j0;
    static doublereal s1, s2;
    static integer nb, jj, nh, nx, pw, nnb, len, top, ppw, n2nb;
    static logical blk22;
    static integer cola, jcol, ierr;
    static doublereal temp;
    extern /* Subroutine */ int drot_(integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *);
    static integer jrow, topq, ppwo;
    static doublereal temp1, temp2, temp3;
    static integer kacc22;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, ftnlen, ftnlen);
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    static integer nbmin;
    extern /* Subroutine */ int dorm22_(char *, char *, integer *, integer *, 
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, integer *, ftnlen, ftnlen);
    static integer nblst;
    static logical initq, wantq;
    extern /* Subroutine */ int dtrmv_(char *, char *, char *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, ftnlen, ftnlen, 
	    ftnlen);
    static logical initz, wantz;
    static char compq2[1], compz2[1];
    extern /* Subroutine */ int dgghrd_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    ftnlen, ftnlen), dlaset_(char *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, integer *, ftnlen), dlartg_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen), dlacpy_(
	    char *, integer *, integer *, doublereal *, integer *, doublereal 
	    *, integer *, ftnlen);
    static integer lwkopt;
    static logical lquery;


/*  -- LAPACK computational routine (version 3.6.1) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     January 2015 */


/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/* ===================================================================== */

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

/*     Decode and test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1;
    q -= q_offset;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1;
    z__ -= z_offset;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DGGHD3", " ", n, ilo, ihi, &c_n1, (ftnlen)6, (ftnlen)
	    1);
/* Computing MAX */
    i__1 = *n * 6 * nb;
    lwkopt = max(i__1,1);
    work[1] = (doublereal) lwkopt;
    initq = lsame_(compq, "I", (ftnlen)1, (ftnlen)1);
    wantq = initq || lsame_(compq, "V", (ftnlen)1, (ftnlen)1);
    initz = lsame_(compz, "I", (ftnlen)1, (ftnlen)1);
    wantz = initz || lsame_(compz, "V", (ftnlen)1, (ftnlen)1);
    lquery = *lwork == -1;

    if (! lsame_(compq, "N", (ftnlen)1, (ftnlen)1) && ! wantq) {
	*info = -1;
    } else if (! lsame_(compz, "N", (ftnlen)1, (ftnlen)1) && ! wantz) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*ilo < 1) {
	*info = -4;
    } else if (*ihi > *n || *ihi < *ilo - 1) {
	*info = -5;
    } else if (*lda < max(1,*n)) {
	*info = -7;
    } else if (*ldb < max(1,*n)) {
	*info = -9;
    } else if (wantq && *ldq < *n || *ldq < 1) {
	*info = -11;
    } else if (wantz && *ldz < *n || *ldz < 1) {
	*info = -13;
    } else if (*lwork < 1 && ! lquery) {
	*info = -15;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGGHD3", &i__1, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Initialize Q and Z if desired. */

    if (initq) {
	dlaset_("All", n, n, &c_b14, &c_b15, &q[q_offset], ldq, (ftnlen)3);
    }
    if (initz) {
	dlaset_("All", n, n, &c_b14, &c_b15, &z__[z_offset], ldz, (ftnlen)3);
    }

/*     Zero out lower triangle of B. */

    if (*n > 1) {
	i__1 = *n - 1;
	i__2 = *n - 1;
	dlaset_("Lower", &i__1, &i__2, &c_b14, &c_b14, &b[b_dim1 + 2], ldb, (
		ftnlen)5);
    }

/*     Quick return if possible */

    nh = *ihi - *ilo + 1;
    if (nh <= 1) {
	work[1] = 1.;
	return 0;
    }

/*     Determine the blocksize. */

    nbmin = ilaenv_(&c__2, "DGGHD3", " ", n, ilo, ihi, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    if (nb > 1 && nb < nh) {

/*        Determine when to use unblocked instead of blocked code. */

/* Computing MAX */
	i__1 = nb, i__2 = ilaenv_(&c__3, "DGGHD3", " ", n, ilo, ihi, &c_n1, (
		ftnlen)6, (ftnlen)1);
	nx = max(i__1,i__2);
	if (nx < nh) {

/*           Determine if workspace is large enough for blocked code. */

	    if (*lwork < lwkopt) {

/*              Not enough workspace to use optimal NB:  determine the */
/*              minimum value of NB, and reduce NB or force use of */
/*              unblocked code. */

/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGGHD3", " ", n, ilo, ihi, &
			c_n1, (ftnlen)6, (ftnlen)1);
		nbmin = max(i__1,i__2);
		if (*lwork >= *n * 6 * nbmin) {
		    nb = *lwork / (*n * 6);
		} else {
		    nb = 1;
		}
	    }
	}
    }

    if (nb < nbmin || nb >= nh) {

/*        Use unblocked code below */

	jcol = *ilo;

    } else {

/*        Use blocked code */

	kacc22 = ilaenv_(&c__16, "DGGHD3", " ", n, ilo, ihi, &c_n1, (ftnlen)6,
		 (ftnlen)1);
	blk22 = kacc22 == 2;
	i__1 = *ihi - 2;
	i__2 = nb;
	for (jcol = *ilo; i__2 < 0 ? jcol >= i__1 : jcol <= i__1; jcol += 
		i__2) {
/* Computing MIN */
	    i__3 = nb, i__4 = *ihi - jcol - 1;
	    nnb = min(i__3,i__4);

/*           Initialize small orthogonal factors that will hold the */
/*           accumulated Givens rotations in workspace. */
/*           N2NB   denotes the number of 2*NNB-by-2*NNB factors */
/*           NBLST  denotes the (possibly smaller) order of the last */
/*                  factor. */

	    n2nb = (*ihi - jcol - 1) / nnb - 1;
	    nblst = *ihi - jcol - n2nb * nnb;
	    dlaset_("All", &nblst, &nblst, &c_b14, &c_b15, &work[1], &nblst, (
		    ftnlen)3);
	    pw = nblst * nblst + 1;
	    i__3 = n2nb;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		i__4 = nnb << 1;
		i__5 = nnb << 1;
		i__6 = nnb << 1;
		dlaset_("All", &i__4, &i__5, &c_b14, &c_b15, &work[pw], &i__6,
			 (ftnlen)3);
		pw += (nnb << 2) * nnb;
	    }

/*           Reduce columns JCOL:JCOL+NNB-1 of A to Hessenberg form. */

	    i__3 = jcol + nnb - 1;
	    for (j = jcol; j <= i__3; ++j) {

/*              Reduce Jth column of A. Store cosines and sines in Jth */
/*              column of A and B, respectively. */

		i__4 = j + 2;
		for (i__ = *ihi; i__ >= i__4; --i__) {
		    temp = a[i__ - 1 + j * a_dim1];
		    dlartg_(&temp, &a[i__ + j * a_dim1], &c__, &s, &a[i__ - 1 
			    + j * a_dim1]);
		    a[i__ + j * a_dim1] = c__;
		    b[i__ + j * b_dim1] = s;
		}

/*              Accumulate Givens rotations into workspace array. */

		ppw = (nblst + 1) * (nblst - 2) - j + jcol + 1;
		len = j + 2 - jcol;
		jrow = j + n2nb * nnb + 2;
		i__4 = jrow;
		for (i__ = *ihi; i__ >= i__4; --i__) {
		    c__ = a[i__ + j * a_dim1];
		    s = b[i__ + j * b_dim1];
		    i__5 = ppw + len - 1;
		    for (jj = ppw; jj <= i__5; ++jj) {
			temp = work[jj + nblst];
			work[jj + nblst] = c__ * temp - s * work[jj];
			work[jj] = s * temp + c__ * work[jj];
		    }
		    ++len;
		    ppw = ppw - nblst - 1;
		}

		ppwo = nblst * nblst + (nnb + j - jcol - 1 << 1) * nnb + nnb;
		j0 = jrow - nnb;
		i__4 = j + 2;
		i__5 = -nnb;
		for (jrow = j0; i__5 < 0 ? jrow >= i__4 : jrow <= i__4; jrow 
			+= i__5) {
		    ppw = ppwo;
		    len = j + 2 - jcol;
		    i__6 = jrow;
		    for (i__ = jrow + nnb - 1; i__ >= i__6; --i__) {
			c__ = a[i__ + j * a_dim1];
			s = b[i__ + j * b_dim1];
			i__7 = ppw + len - 1;
			for (jj = ppw; jj <= i__7; ++jj) {
			    temp = work[jj + (nnb << 1)];
			    work[jj + (nnb << 1)] = c__ * temp - s * work[jj];
			    work[jj] = s * temp + c__ * work[jj];
			}
			++len;
			ppw = ppw - (nnb << 1) - 1;
		    }
		    ppwo += (nnb << 2) * nnb;
		}

/*              TOP denotes the number of top rows in A and B that will */
/*              not be updated during the next steps. */

		if (jcol <= 2) {
		    top = 0;
		} else {
		    top = jcol;
		}

/*              Propagate transformations through B and replace stored */
/*              left sines/cosines by right sines/cosines. */

		i__5 = j + 1;
		for (jj = *n; jj >= i__5; --jj) {

/*                 Update JJth column of B. */

/* Computing MIN */
		    i__4 = jj + 1;
		    i__6 = j + 2;
		    for (i__ = min(i__4,*ihi); i__ >= i__6; --i__) {
			c__ = a[i__ + j * a_dim1];
			s = b[i__ + j * b_dim1];
			temp = b[i__ + jj * b_dim1];
			b[i__ + jj * b_dim1] = c__ * temp - s * b[i__ - 1 + 
				jj * b_dim1];
			b[i__ - 1 + jj * b_dim1] = s * temp + c__ * b[i__ - 1 
				+ jj * b_dim1];
		    }

/*                 Annihilate B( JJ+1, JJ ). */

		    if (jj < *ihi) {
			temp = b[jj + 1 + (jj + 1) * b_dim1];
			dlartg_(&temp, &b[jj + 1 + jj * b_dim1], &c__, &s, &b[
				jj + 1 + (jj + 1) * b_dim1]);
			b[jj + 1 + jj * b_dim1] = 0.;
			i__6 = jj - top;
			drot_(&i__6, &b[top + 1 + (jj + 1) * b_dim1], &c__1, &
				b[top + 1 + jj * b_dim1], &c__1, &c__, &s);
			a[jj + 1 + j * a_dim1] = c__;
			b[jj + 1 + j * b_dim1] = -s;
		    }
		}

/*              Update A by transformations from right. */
/*              Explicit loop unrolling provides better performance */
/*              compared to DLASR. */
/*               CALL DLASR( 'Right', 'Variable', 'Backward', IHI-TOP, */
/*     $                     IHI-J, A( J+2, J ), B( J+2, J ), */
/*     $                     A( TOP+1, J+1 ), LDA ) */

		jj = (*ihi - j - 1) % 3;
		i__5 = jj + 1;
		for (i__ = *ihi - j - 3; i__ >= i__5; i__ += -3) {
		    c__ = a[j + 1 + i__ + j * a_dim1];
		    s = -b[j + 1 + i__ + j * b_dim1];
		    c1 = a[j + 2 + i__ + j * a_dim1];
		    s1 = -b[j + 2 + i__ + j * b_dim1];
		    c2 = a[j + 3 + i__ + j * a_dim1];
		    s2 = -b[j + 3 + i__ + j * b_dim1];

		    i__6 = *ihi;
		    for (k = top + 1; k <= i__6; ++k) {
			temp = a[k + (j + i__) * a_dim1];
			temp1 = a[k + (j + i__ + 1) * a_dim1];
			temp2 = a[k + (j + i__ + 2) * a_dim1];
			temp3 = a[k + (j + i__ + 3) * a_dim1];
			a[k + (j + i__ + 3) * a_dim1] = c2 * temp3 + s2 * 
				temp2;
			temp2 = -s2 * temp3 + c2 * temp2;
			a[k + (j + i__ + 2) * a_dim1] = c1 * temp2 + s1 * 
				temp1;
			temp1 = -s1 * temp2 + c1 * temp1;
			a[k + (j + i__ + 1) * a_dim1] = c__ * temp1 + s * 
				temp;
			a[k + (j + i__) * a_dim1] = -s * temp1 + c__ * temp;
		    }
		}

		if (jj > 0) {
		    for (i__ = jj; i__ >= 1; --i__) {
			i__5 = *ihi - top;
			d__1 = -b[j + 1 + i__ + j * b_dim1];
			drot_(&i__5, &a[top + 1 + (j + i__ + 1) * a_dim1], &
				c__1, &a[top + 1 + (j + i__) * a_dim1], &c__1,
				 &a[j + 1 + i__ + j * a_dim1], &d__1);
		    }
		}

/*              Update (J+1)th column of A by transformations from left. */

		if (j < jcol + nnb - 1) {
		    len = j + 1 - jcol;

/*                 Multiply with the trailing accumulated orthogonal */
/*                 matrix, which takes the form */

/*                        [  U11  U12  ] */
/*                    U = [            ], */
/*                        [  U21  U22  ] */

/*                 where U21 is a LEN-by-LEN matrix and U12 is lower */
/*                 triangular. */

		    jrow = *ihi - nblst + 1;
		    dgemv_("Transpose", &nblst, &len, &c_b15, &work[1], &
			    nblst, &a[jrow + (j + 1) * a_dim1], &c__1, &c_b14,
			     &work[pw], &c__1, (ftnlen)9);
		    ppw = pw + len;
		    i__5 = jrow + nblst - len - 1;
		    for (i__ = jrow; i__ <= i__5; ++i__) {
			work[ppw] = a[i__ + (j + 1) * a_dim1];
			++ppw;
		    }
		    i__5 = nblst - len;
		    dtrmv_("Lower", "Transpose", "Non-unit", &i__5, &work[len 
			    * nblst + 1], &nblst, &work[pw + len], &c__1, (
			    ftnlen)5, (ftnlen)9, (ftnlen)8);
		    i__5 = nblst - len;
		    dgemv_("Transpose", &len, &i__5, &c_b15, &work[(len + 1) *
			     nblst - len + 1], &nblst, &a[jrow + nblst - len 
			    + (j + 1) * a_dim1], &c__1, &c_b15, &work[pw + 
			    len], &c__1, (ftnlen)9);
		    ppw = pw;
		    i__5 = jrow + nblst - 1;
		    for (i__ = jrow; i__ <= i__5; ++i__) {
			a[i__ + (j + 1) * a_dim1] = work[ppw];
			++ppw;
		    }

/*                 Multiply with the other accumulated orthogonal */
/*                 matrices, which take the form */

/*                        [  U11  U12   0  ] */
/*                        [                ] */
/*                    U = [  U21  U22   0  ], */
/*                        [                ] */
/*                        [   0    0    I  ] */

/*                 where I denotes the (NNB-LEN)-by-(NNB-LEN) identity */
/*                 matrix, U21 is a LEN-by-LEN upper triangular matrix */
/*                 and U12 is an NNB-by-NNB lower triangular matrix. */

		    ppwo = nblst * nblst + 1;
		    j0 = jrow - nnb;
		    i__5 = jcol + 1;
		    i__6 = -nnb;
		    for (jrow = j0; i__6 < 0 ? jrow >= i__5 : jrow <= i__5; 
			    jrow += i__6) {
			ppw = pw + len;
			i__4 = jrow + nnb - 1;
			for (i__ = jrow; i__ <= i__4; ++i__) {
			    work[ppw] = a[i__ + (j + 1) * a_dim1];
			    ++ppw;
			}
			ppw = pw;
			i__4 = jrow + nnb + len - 1;
			for (i__ = jrow + nnb; i__ <= i__4; ++i__) {
			    work[ppw] = a[i__ + (j + 1) * a_dim1];
			    ++ppw;
			}
			i__4 = nnb << 1;
			dtrmv_("Upper", "Transpose", "Non-unit", &len, &work[
				ppwo + nnb], &i__4, &work[pw], &c__1, (ftnlen)
				5, (ftnlen)9, (ftnlen)8);
			i__4 = nnb << 1;
			dtrmv_("Lower", "Transpose", "Non-unit", &nnb, &work[
				ppwo + (len << 1) * nnb], &i__4, &work[pw + 
				len], &c__1, (ftnlen)5, (ftnlen)9, (ftnlen)8);
			i__4 = nnb << 1;
			dgemv_("Transpose", &nnb, &len, &c_b15, &work[ppwo], &
				i__4, &a[jrow + (j + 1) * a_dim1], &c__1, &
				c_b15, &work[pw], &c__1, (ftnlen)9);
			i__4 = nnb << 1;
			dgemv_("Transpose", &len, &nnb, &c_b15, &work[ppwo + (
				len << 1) * nnb + nnb], &i__4, &a[jrow + nnb 
				+ (j + 1) * a_dim1], &c__1, &c_b15, &work[pw 
				+ len], &c__1, (ftnlen)9);
			ppw = pw;
			i__4 = jrow + len + nnb - 1;
			for (i__ = jrow; i__ <= i__4; ++i__) {
			    a[i__ + (j + 1) * a_dim1] = work[ppw];
			    ++ppw;
			}
			ppwo += (nnb << 2) * nnb;
		    }
		}
	    }

/*           Apply accumulated orthogonal matrices to A. */

	    cola = *n - jcol - nnb + 1;
	    j = *ihi - nblst + 1;
	    dgemm_("Transpose", "No Transpose", &nblst, &cola, &nblst, &c_b15,
		     &work[1], &nblst, &a[j + (jcol + nnb) * a_dim1], lda, &
		    c_b14, &work[pw], &nblst, (ftnlen)9, (ftnlen)12);
	    dlacpy_("All", &nblst, &cola, &work[pw], &nblst, &a[j + (jcol + 
		    nnb) * a_dim1], lda, (ftnlen)3);
	    ppwo = nblst * nblst + 1;
	    j0 = j - nnb;
	    i__3 = jcol + 1;
	    i__6 = -nnb;
	    for (j = j0; i__6 < 0 ? j >= i__3 : j <= i__3; j += i__6) {
		if (blk22) {

/*                 Exploit the structure of */

/*                        [  U11  U12  ] */
/*                    U = [            ] */
/*                        [  U21  U22  ], */

/*                 where all blocks are NNB-by-NNB, U21 is upper */
/*                 triangular and U12 is lower triangular. */

		    i__5 = nnb << 1;
		    i__4 = nnb << 1;
		    i__7 = *lwork - pw + 1;
		    dorm22_("Left", "Transpose", &i__5, &cola, &nnb, &nnb, &
			    work[ppwo], &i__4, &a[j + (jcol + nnb) * a_dim1], 
			    lda, &work[pw], &i__7, &ierr, (ftnlen)4, (ftnlen)
			    9);
		} else {

/*                 Ignore the structure of U. */

		    i__5 = nnb << 1;
		    i__4 = nnb << 1;
		    i__7 = nnb << 1;
		    i__8 = nnb << 1;
		    dgemm_("Transpose", "No Transpose", &i__5, &cola, &i__4, &
			    c_b15, &work[ppwo], &i__7, &a[j + (jcol + nnb) * 
			    a_dim1], lda, &c_b14, &work[pw], &i__8, (ftnlen)9,
			     (ftnlen)12);
		    i__5 = nnb << 1;
		    i__4 = nnb << 1;
		    dlacpy_("All", &i__5, &cola, &work[pw], &i__4, &a[j + (
			    jcol + nnb) * a_dim1], lda, (ftnlen)3);
		}
		ppwo += (nnb << 2) * nnb;
	    }

/*           Apply accumulated orthogonal matrices to Q. */

	    if (wantq) {
		j = *ihi - nblst + 1;
		if (initq) {
/* Computing MAX */
		    i__6 = 2, i__3 = j - jcol + 1;
		    topq = max(i__6,i__3);
		    nh = *ihi - topq + 1;
		} else {
		    topq = 1;
		    nh = *n;
		}
		dgemm_("No Transpose", "No Transpose", &nh, &nblst, &nblst, &
			c_b15, &q[topq + j * q_dim1], ldq, &work[1], &nblst, &
			c_b14, &work[pw], &nh, (ftnlen)12, (ftnlen)12);
		dlacpy_("All", &nh, &nblst, &work[pw], &nh, &q[topq + j * 
			q_dim1], ldq, (ftnlen)3);
		ppwo = nblst * nblst + 1;
		j0 = j - nnb;
		i__6 = jcol + 1;
		i__3 = -nnb;
		for (j = j0; i__3 < 0 ? j >= i__6 : j <= i__6; j += i__3) {
		    if (initq) {
/* Computing MAX */
			i__5 = 2, i__4 = j - jcol + 1;
			topq = max(i__5,i__4);
			nh = *ihi - topq + 1;
		    }
		    if (blk22) {

/*                    Exploit the structure of U. */

			i__5 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = *lwork - pw + 1;
			dorm22_("Right", "No Transpose", &nh, &i__5, &nnb, &
				nnb, &work[ppwo], &i__4, &q[topq + j * q_dim1]
				, ldq, &work[pw], &i__7, &ierr, (ftnlen)5, (
				ftnlen)12);
		    } else {

/*                    Ignore the structure of U. */

			i__5 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = nnb << 1;
			dgemm_("No Transpose", "No Transpose", &nh, &i__5, &
				i__4, &c_b15, &q[topq + j * q_dim1], ldq, &
				work[ppwo], &i__7, &c_b14, &work[pw], &nh, (
				ftnlen)12, (ftnlen)12);
			i__5 = nnb << 1;
			dlacpy_("All", &nh, &i__5, &work[pw], &nh, &q[topq + 
				j * q_dim1], ldq, (ftnlen)3);
		    }
		    ppwo += (nnb << 2) * nnb;
		}
	    }

/*           Accumulate right Givens rotations if required. */

	    if (wantz || top > 0) {

/*              Initialize small orthogonal factors that will hold the */
/*              accumulated Givens rotations in workspace. */

		dlaset_("All", &nblst, &nblst, &c_b14, &c_b15, &work[1], &
			nblst, (ftnlen)3);
		pw = nblst * nblst + 1;
		i__3 = n2nb;
		for (i__ = 1; i__ <= i__3; ++i__) {
		    i__6 = nnb << 1;
		    i__5 = nnb << 1;
		    i__4 = nnb << 1;
		    dlaset_("All", &i__6, &i__5, &c_b14, &c_b15, &work[pw], &
			    i__4, (ftnlen)3);
		    pw += (nnb << 2) * nnb;
		}

/*              Accumulate Givens rotations into workspace array. */

		i__3 = jcol + nnb - 1;
		for (j = jcol; j <= i__3; ++j) {
		    ppw = (nblst + 1) * (nblst - 2) - j + jcol + 1;
		    len = j + 2 - jcol;
		    jrow = j + n2nb * nnb + 2;
		    i__6 = jrow;
		    for (i__ = *ihi; i__ >= i__6; --i__) {
			c__ = a[i__ + j * a_dim1];
			a[i__ + j * a_dim1] = 0.;
			s = b[i__ + j * b_dim1];
			b[i__ + j * b_dim1] = 0.;
			i__5 = ppw + len - 1;
			for (jj = ppw; jj <= i__5; ++jj) {
			    temp = work[jj + nblst];
			    work[jj + nblst] = c__ * temp - s * work[jj];
			    work[jj] = s * temp + c__ * work[jj];
			}
			++len;
			ppw = ppw - nblst - 1;
		    }

		    ppwo = nblst * nblst + (nnb + j - jcol - 1 << 1) * nnb + 
			    nnb;
		    j0 = jrow - nnb;
		    i__6 = j + 2;
		    i__5 = -nnb;
		    for (jrow = j0; i__5 < 0 ? jrow >= i__6 : jrow <= i__6; 
			    jrow += i__5) {
			ppw = ppwo;
			len = j + 2 - jcol;
			i__4 = jrow;
			for (i__ = jrow + nnb - 1; i__ >= i__4; --i__) {
			    c__ = a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = 0.;
			    s = b[i__ + j * b_dim1];
			    b[i__ + j * b_dim1] = 0.;
			    i__7 = ppw + len - 1;
			    for (jj = ppw; jj <= i__7; ++jj) {
				temp = work[jj + (nnb << 1)];
				work[jj + (nnb << 1)] = c__ * temp - s * work[
					jj];
				work[jj] = s * temp + c__ * work[jj];
			    }
			    ++len;
			    ppw = ppw - (nnb << 1) - 1;
			}
			ppwo += (nnb << 2) * nnb;
		    }
		}
	    } else {

		i__3 = *ihi - jcol - 1;
		dlaset_("Lower", &i__3, &nnb, &c_b14, &c_b14, &a[jcol + 2 + 
			jcol * a_dim1], lda, (ftnlen)5);
		i__3 = *ihi - jcol - 1;
		dlaset_("Lower", &i__3, &nnb, &c_b14, &c_b14, &b[jcol + 2 + 
			jcol * b_dim1], ldb, (ftnlen)5);
	    }

/*           Apply accumulated orthogonal matrices to A and B. */

	    if (top > 0) {
		j = *ihi - nblst + 1;
		dgemm_("No Transpose", "No Transpose", &top, &nblst, &nblst, &
			c_b15, &a[j * a_dim1 + 1], lda, &work[1], &nblst, &
			c_b14, &work[pw], &top, (ftnlen)12, (ftnlen)12);
		dlacpy_("All", &top, &nblst, &work[pw], &top, &a[j * a_dim1 + 
			1], lda, (ftnlen)3);
		ppwo = nblst * nblst + 1;
		j0 = j - nnb;
		i__3 = jcol + 1;
		i__5 = -nnb;
		for (j = j0; i__5 < 0 ? j >= i__3 : j <= i__3; j += i__5) {
		    if (blk22) {

/*                    Exploit the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = *lwork - pw + 1;
			dorm22_("Right", "No Transpose", &top, &i__6, &nnb, &
				nnb, &work[ppwo], &i__4, &a[j * a_dim1 + 1], 
				lda, &work[pw], &i__7, &ierr, (ftnlen)5, (
				ftnlen)12);
		    } else {

/*                    Ignore the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = nnb << 1;
			dgemm_("No Transpose", "No Transpose", &top, &i__6, &
				i__4, &c_b15, &a[j * a_dim1 + 1], lda, &work[
				ppwo], &i__7, &c_b14, &work[pw], &top, (
				ftnlen)12, (ftnlen)12);
			i__6 = nnb << 1;
			dlacpy_("All", &top, &i__6, &work[pw], &top, &a[j * 
				a_dim1 + 1], lda, (ftnlen)3);
		    }
		    ppwo += (nnb << 2) * nnb;
		}

		j = *ihi - nblst + 1;
		dgemm_("No Transpose", "No Transpose", &top, &nblst, &nblst, &
			c_b15, &b[j * b_dim1 + 1], ldb, &work[1], &nblst, &
			c_b14, &work[pw], &top, (ftnlen)12, (ftnlen)12);
		dlacpy_("All", &top, &nblst, &work[pw], &top, &b[j * b_dim1 + 
			1], ldb, (ftnlen)3);
		ppwo = nblst * nblst + 1;
		j0 = j - nnb;
		i__5 = jcol + 1;
		i__3 = -nnb;
		for (j = j0; i__3 < 0 ? j >= i__5 : j <= i__5; j += i__3) {
		    if (blk22) {

/*                    Exploit the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = *lwork - pw + 1;
			dorm22_("Right", "No Transpose", &top, &i__6, &nnb, &
				nnb, &work[ppwo], &i__4, &b[j * b_dim1 + 1], 
				ldb, &work[pw], &i__7, &ierr, (ftnlen)5, (
				ftnlen)12);
		    } else {

/*                    Ignore the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = nnb << 1;
			dgemm_("No Transpose", "No Transpose", &top, &i__6, &
				i__4, &c_b15, &b[j * b_dim1 + 1], ldb, &work[
				ppwo], &i__7, &c_b14, &work[pw], &top, (
				ftnlen)12, (ftnlen)12);
			i__6 = nnb << 1;
			dlacpy_("All", &top, &i__6, &work[pw], &top, &b[j * 
				b_dim1 + 1], ldb, (ftnlen)3);
		    }
		    ppwo += (nnb << 2) * nnb;
		}
	    }

/*           Apply accumulated orthogonal matrices to Z. */

	    if (wantz) {
		j = *ihi - nblst + 1;
		if (initq) {
/* Computing MAX */
		    i__3 = 2, i__5 = j - jcol + 1;
		    topq = max(i__3,i__5);
		    nh = *ihi - topq + 1;
		} else {
		    topq = 1;
		    nh = *n;
		}
		dgemm_("No Transpose", "No Transpose", &nh, &nblst, &nblst, &
			c_b15, &z__[topq + j * z_dim1], ldz, &work[1], &nblst,
			 &c_b14, &work[pw], &nh, (ftnlen)12, (ftnlen)12);
		dlacpy_("All", &nh, &nblst, &work[pw], &nh, &z__[topq + j * 
			z_dim1], ldz, (ftnlen)3);
		ppwo = nblst * nblst + 1;
		j0 = j - nnb;
		i__3 = jcol + 1;
		i__5 = -nnb;
		for (j = j0; i__5 < 0 ? j >= i__3 : j <= i__3; j += i__5) {
		    if (initq) {
/* Computing MAX */
			i__6 = 2, i__4 = j - jcol + 1;
			topq = max(i__6,i__4);
			nh = *ihi - topq + 1;
		    }
		    if (blk22) {

/*                    Exploit the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = *lwork - pw + 1;
			dorm22_("Right", "No Transpose", &nh, &i__6, &nnb, &
				nnb, &work[ppwo], &i__4, &z__[topq + j * 
				z_dim1], ldz, &work[pw], &i__7, &ierr, (
				ftnlen)5, (ftnlen)12);
		    } else {

/*                    Ignore the structure of U. */

			i__6 = nnb << 1;
			i__4 = nnb << 1;
			i__7 = nnb << 1;
			dgemm_("No Transpose", "No Transpose", &nh, &i__6, &
				i__4, &c_b15, &z__[topq + j * z_dim1], ldz, &
				work[ppwo], &i__7, &c_b14, &work[pw], &nh, (
				ftnlen)12, (ftnlen)12);
			i__6 = nnb << 1;
			dlacpy_("All", &nh, &i__6, &work[pw], &nh, &z__[topq 
				+ j * z_dim1], ldz, (ftnlen)3);
		    }
		    ppwo += (nnb << 2) * nnb;
		}
	    }
	}
    }

/*     Use unblocked code to reduce the rest of the matrix */
/*     Avoid re-initialization of modified Q and Z. */

    *(unsigned char *)compq2 = *(unsigned char *)compq;
    *(unsigned char *)compz2 = *(unsigned char *)compz;
    if (jcol != *ilo) {
	if (wantq) {
	    *(unsigned char *)compq2 = 'V';
	}
	if (wantz) {
	    *(unsigned char *)compz2 = 'V';
	}
    }

    if (jcol < *ihi) {
	dgghrd_(compq2, compz2, n, &jcol, ihi, &a[a_offset], lda, &b[b_offset]
		, ldb, &q[q_offset], ldq, &z__[z_offset], ldz, &ierr, (ftnlen)
		1, (ftnlen)1);
    }
    work[1] = (doublereal) lwkopt;

    return 0;

/*     End of DGGHD3 */

} /* dgghd3_ */

