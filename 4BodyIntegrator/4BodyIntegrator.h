
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MY4BODYINTEGRATOR_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MY4BODYINTEGRATOR_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MY4BODYINTEGRATOR_EXPORTS
#define MY4BODYINTEGRATOR_API __declspec(dllexport)
#else
#define MY4BODYINTEGRATOR_API __declspec(dllimport)
#endif

// This class is exported from the 4BodyIntegrator.dll
class MY4BODYINTEGRATOR_API CMy4BodyIntegrator {
public:
	CMy4BodyIntegrator(void);
	// TODO: add your methods here.
};

extern MY4BODYINTEGRATOR_API int nMy4BodyIntegrator;

MY4BODYINTEGRATOR_API int fnMy4BodyIntegrator(double *X, double *V, double T, double *M);
extern "C" {void __stdcall FORCE(double *X,double *V,double *TM,double *F, double *MU);};
extern "C" {void __stdcall RA15(double *X,double *V,double *TF,double *XL,double *LL,int *NV,int *NCLASS,int *NOR,  double *MU)   ;};

