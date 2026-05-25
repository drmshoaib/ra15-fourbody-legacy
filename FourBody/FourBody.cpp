// FourBody.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

__declspec(dllimport) int fnMy4BodyIntegrator(double *X, double *V, double T, double *M);

double CalcEnergy(double *X,double *V, double *M);

int main(int argc, char* argv[])
{
	int i;

	double X[9], V[9], M[9], T, E0;
	FILE *in, *out;

	double timestep,time=0.0;

	in = fopen("initialcond.txt","rt");

	if(in==NULL)
	{
		printf("Can't find the input file!\n");
		scanf("%d",&i);
		return -1;
	}

	for(i=0;i<8;i++)
		fscanf(in,"%lf",X+i);

	for(i=0;i<8;i++)
		fscanf(in,"%lf",V+i);

	for(i=0;i<4;i++)
		fscanf(in,"%lf",M+i);

	fscanf(in,"%lf",&T);

	fclose(in);

	out = fopen("result1.txt","wt");

	timestep = 0.001; //T/100000.0;

	E0 = CalcEnergy(X,V,M);

	for(i=0;i<1000000.0;i++)
	{
		if(fmod(i,1)==0)
		{
			fprintf(out,"%.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f %.20f \n", time, X[0], 
			X[1], X[2], X[3], X[4], X[5], X[6], X[7], V[0], V[1], V[2], V[3], V[4], V[5],
			V[6], V[7] , CalcEnergy(X,V,M));
		}

		fnMy4BodyIntegrator(X, V, timestep, M);

		if( fabs((CalcEnergy(X,V,M)-E0)/E0) > 0.000000001)
		{
			fprintf(out,"0    0      0        0");
			fclose(out);
			return -1;
		}

        // check if the syst is still close to symm
		// if not do sg

		time=time+timestep;
	}

	fclose(out);


	return 0;
}

double CalcEnergy(double *x, double *v, double *m)
{
	double U, K;

	U = m[0]*m[1]/sqrt((x[0] - x[2])*(x[0] - x[2]) + (x[1] - x[3])*(x[1] - x[3])) +
		m[0]*m[2]/sqrt((x[0] - x[4])*(x[0] - x[4]) + (x[1] - x[5])*(x[1] - x[5])) +
		m[0]*m[3]/sqrt((x[0] - x[6])*(x[0] - x[6]) + (x[1] - x[7])*(x[1] - x[7])) +
		m[1]*m[2]/sqrt((x[2] - x[4])*(x[2] - x[4]) + (x[3] - x[5])*(x[3] - x[5])) +
		m[1]*m[3]/sqrt((x[2] - x[6])*(x[2] - x[6]) + (x[3] - x[7])*(x[3] - x[7])) +
		m[2]*m[3]/sqrt((x[4] - x[6])*(x[4] - x[6]) + (x[5] - x[7])*(x[5] - x[7]));

	K = 0.5*m[0]*(v[0]*v[0]+v[1]*v[1]) +
		0.5*m[1]*(v[2]*v[2]+v[3]*v[3]) +
		0.5*m[2]*(v[4]*v[4]+v[5]*v[5]) +
		0.5*m[3]*(v[6]*v[6]+v[7]*v[7]);
		
	return K - U; 
}


