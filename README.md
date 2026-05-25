# Four-Body Integration Project

This repository is a cleaned archive of a legacy four-body gravitational
integration project from 2002-2003. It contains the source code, initial
condition data, and Mathematica notebooks needed to understand and reproduce
the original numerical experiments.

## What is here

- `4BodyIntegrator/` - a Visual C++ DLL wrapper around Fortran routines.
  `4BodyIntegrator.cpp` exports `fnMy4BodyIntegrator`, which calls the RA15
  integrator.
- `4BodyIntegrator/Radu15.for` - E. Everhart's 15th-order Radau integrator.
- `4BodyIntegrator/Force.for` - the planar Newtonian four-body force routine.
- `FourBody/` - a console runner that reads `initialcond.txt`, advances the
  system, checks energy conservation, and writes `result1.txt`.
- `WinForInitCond/` - an MFC dialog front end for entering initial conditions
  and generating `result.txt`.
- `FourBody/*.xls` and `ListInitialConditions.xls` - legacy initial-condition
  spreadsheets.
- `FourBody/*.nb`, `FourBody/Results/`, `FourBody/RsultsForComparison/`, and
  `Workingfolder/OrbitPlotter.nb` - Mathematica notebooks for plotting and
  checking orbit radii/symmetry.

## Input format

`FourBody/initialcond.txt` is read as:

1. 8 position values: `x1 y1 x2 y2 x3 y3 x4 y4`
2. 8 velocity values: `vx1 vy1 vx2 vy2 vx3 vy3 vx4 vy4`
3. 4 mass values: `m1 m2 m3 m4`
4. integration time `T`

The current sample uses four equal masses and a symmetric planar setup.

## Legacy build notes

The original project files are Visual Studio 6 / Microsoft Developer Studio
files (`.dsw`, `.dsp`). The DLL project also expects a compatible Fortran
compiler, historically exposed as `df.exe`.

Build order:

1. Build `4BodyIntegrator`.
2. Build `FourBody` or `WinForInitCond`.
3. Put `4BodyIntegrator.dll` beside the executable before running.

The clean repo keeps the old project files, but the absolute import-library
paths have been changed to relative paths:

- `..\4BodyIntegrator\Debug\4BodyIntegrator.lib`
- `..\4BodyIntegrator\Release\4BodyIntegrator.lib`

These project files have not been modernized or verified with a contemporary
compiler.

## Running notes

The console runner writes every integration step to `result1.txt`. With the
current settings it can generate a large file, so reduce the loop count or
step output frequency before doing exploratory runs.

The Mathematica notebooks contain hard-coded historical paths such as
`D:/STAFF/pk21220/4BIntegrationProject/FourBody/result1.txt`. Update those
paths before running the notebooks on a new machine.

## Repository hygiene

Old executables, DLLs, import libraries, debugger databases, precompiled
headers, object files, and Developer Studio user/cache files were intentionally
left out. See `docs/cleanup-notes.md` for the cleanup rationale.

No license file is included yet. Add one before publishing publicly if you want
to grant reuse rights.
