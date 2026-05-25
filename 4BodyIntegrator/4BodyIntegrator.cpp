// 4BodyIntegrator.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "4BodyIntegrator.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
MY4BODYINTEGRATOR_API int nMy4BodyIntegrator=0;

// This is an example of an exported function.
MY4BODYINTEGRATOR_API int fnMy4BodyIntegrator(double *X, double *V, double T, double *M)
{
	double XL = 0.001, LL=-1;
	int NV=8, NCLASS=-2, NOR=15;

	RA15(X,V,&T,&XL,&LL,&NV, &NCLASS, &NOR, M);

	return 0;
}

// This is the constructor of a class that has been exported.
// see 4BodyIntegrator.h for the class definition
CMy4BodyIntegrator::CMy4BodyIntegrator()
{ 
	return; 
}

