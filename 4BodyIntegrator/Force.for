      SUBROUTINE FORCE(X,V,TM,F,UM)
C  This is the FORCE subroutine for a four body 
C  coplanar integration in barycentric coordinates.
C  The 4 bodies have M(1)...M(4)
C  It is FORCE.FOR
      IMPLICIT REAL*8 (A-H,L-Z)
      DIMENSION X(8),V(8),F(8),M(4),RH(4,4), UM(4)
C  DATA M/1.0D0, 1.0D0, 1.0D0, 1.0D0/

	M(1) = UM(1)
	M(2) = UM(2)
	M(3) = UM(3)
	M(4) = UM(4)

      DO 10 N=1,4
         J=(N-1)*2+1
         IF(N.EQ.4)  GO TO 10
         NA=N+1
         DO 9 L=NA,4
            K=(L-1)*2+1
            RH(N,L)=1.D0/DSQRT((X(J)-X(K))**2+
     A         (X(J+1)-X(K+1))**2)**3
            RH(L,N)=RH(N,L)
   9     CONTINUE 
  10  CONTINUE
      DO 20 N=1,4
         J=(N-1)*2+1
         F(J  )= 0.D0
         F(J+1)= 0.D0
         DO 30 L=1,4
            IF(L.EQ.N) GO TO 30
            K=(L-1)*2+1
            F(J  )=F(J  )+M(L)*(X(K  )-X(J  ))*RH(N,L)
            F(J+1)=F(J+1)+M(L)*(X(K+1)-X(J+1))*RH(N,L)
  30     CONTINUE
  20  CONTINUE
      RETURN
      END
