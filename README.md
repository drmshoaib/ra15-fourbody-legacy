# Four-Body Integration Project

This repository is a cleaned archive of a legacy four-body gravitational
integration project from 2002-2003. It contains the source code, initial
condition data, and Mathematica notebooks used to integrate and inspect planar
four-body orbits.

The original code is preserved as a historical project. It has not yet been
modernized for contemporary compilers.

## Mathematical model

The code integrates four point masses moving in a plane. Body `i` has position

```text
r_i = (x_i, y_i)
```

velocity

```text
v_i = (vx_i, vy_i)
```

and mass `m_i`. The source uses gravitational units with `G = 1`.

For each body,

```math
\ddot r_i =
\sum_{\substack{j=1 \\ j \ne i}}^4
m_j \frac{r_j - r_i}{\lVert r_j - r_i \rVert^3}.
```

Expanded component-wise, this is

```math
\ddot x_i =
\sum_{\substack{j=1 \\ j \ne i}}^4
m_j \frac{x_j - x_i}
{\left((x_j-x_i)^2 + (y_j-y_i)^2\right)^{3/2}},
```

```math
\ddot y_i =
\sum_{\substack{j=1 \\ j \ne i}}^4
m_j \frac{y_j - y_i}
{\left((x_j-x_i)^2 + (y_j-y_i)^2\right)^{3/2}}.
```

The force routine is implemented in `4BodyIntegrator/Force.for`. It describes
the coordinates as coplanar barycentric coordinates, although the code itself
does not explicitly re-center the state during integration.

The diagnostic energy used by both front ends is

```math
E = K - U,
```

where

```math
K = \frac{1}{2}\sum_{i=1}^4 m_i \lVert v_i \rVert^2
```

and

```math
U =
\sum_{1 \le i < j \le 4}
\frac{m_i m_j}{\lVert r_i-r_j \rVert}.
```

## Numerical method

The integration method is Everhart's RA15 Radau integrator, implemented in
`4BodyIntegrator/Radu15.for`. RA15 is a high-order implicit Runge-Kutta style
method based on Gauss-Radau spacings. The comments in `Radu15.for` describe it
as a 15th-order version of Everhart's RADAU integrator.

The C++ DLL wrapper is `4BodyIntegrator/4BodyIntegrator.cpp`. The exported
function

```cpp
fnMy4BodyIntegrator(double *X, double *V, double T, double *M)
```

calls:

```cpp
RA15(X, V, &T, &XL, &LL, &NV, &NCLASS, &NOR, M);
```

with these parameters:

| Parameter | Value | Meaning |
| --- | --- | --- |
| `NV` | `8` | Eight second-order coordinate variables: `x1 y1 ... x4 y4`. |
| `NCLASS` | `-2` | RA15 second-order mode, `y'' = F(y,t)`. |
| `NOR` | `15` | Fifteenth-order RA15 integration. |
| `XL` | `0.001` | Constant RA15 sequence size. |
| `LL` | `-1` | Negative `LL` tells RA15 to use constant sequence size `XL`. |

`X` and `V` are updated in place. One call to `fnMy4BodyIntegrator` advances the
system by the time interval supplied as `T`.

## Repository layout

- `4BodyIntegrator/` - Visual C++ DLL wrapper plus Fortran integrator and force
  routine.
- `FourBody/` - console runner for batch integration.
- `WinForInitCond/` - MFC dialog front end for entering initial conditions.
- `FourBody/*.xls` and `ListInitialConditions.xls` - legacy initial-condition
  spreadsheets.
- `FourBody/*.nb` - Mathematica notebooks for plotting or checking orbits.
- `FourBody/Results/` and `FourBody/RsultsForComparison/` - historical
  Mathematica result/comparison notebooks.
- `Workingfolder/` - small historical working copy containing an initial
  condition file and an orbit plotting notebook.

## Input format

`FourBody/initialcond.txt` is read as 21 numeric values:

1. 8 position values: `x1 y1 x2 y2 x3 y3 x4 y4`
2. 8 velocity values: `vx1 vy1 vx2 vy2 vx3 vy3 vx4 vy4`
3. 4 mass values: `m1 m2 m3 m4`
4. 1 final/integration time value: `T`

The current sample is:

```text
positions:  1.31 0  1.14 0  -1.31 0  -1.14 0
velocities: 0 0.6  0 0.9  0 -0.6  0 -0.9
masses:     1 1 1 1
T:          1000000
```

In the current console program, `T` is read but the main loop uses a hard-coded
`timestep = 0.001` and `1,000,000` iterations. That means the simulated output
time reaches approximately `1000`, regardless of the `T` value in the input
file. The commented code suggests an earlier intent to set
`timestep = T / 100000.0`.

## Console runner output

`FourBody/FourBody.cpp` writes `result1.txt`.

It currently writes every step because the output guard is:

```cpp
if(fmod(i,1)==0)
```

The output line has 18 whitespace-separated columns:

| Column | Meaning |
| --- | --- |
| 1 | `time` |
| 2-9 | `x1 y1 x2 y2 x3 y3 x4 y4` |
| 10-17 | `vx1 vy1 vx2 vy2 vx3 vy3 vx4 vy4` |
| 18 | energy `E = K - U` |

Each value is printed with `%.20f` precision.

The console runner computes the initial energy `E0` and stops early if:

```math
\left|\frac{E - E_0}{E_0}\right| > 10^{-9}.
```

On failure it appends:

```text
0    0      0        0
```

then closes `result1.txt` and exits with `-1`.

## GUI output

`WinForInitCond/WinForInitCondDlg.cpp` writes `result.txt`.

The GUI reads state values from edit controls, reads integration time from
`IDC_TIME`, then reads the actual timestep from `IDC_STEPSIZE`. It writes one
line per step with 9 whitespace-separated columns:

| Column | Meaning |
| --- | --- |
| 1 | `time` |
| 2-9 | `x1 y1 x2 y2 x3 y3 x4 y4` |

The GUI also checks energy conservation, but with a looser threshold:

```math
\left|\frac{E - E_0}{E_0}\right| > 10^{-2}.
```

On failure it shows an MFC message box and writes:

```text
The energy conservation fails!
```

## Mathematica notebooks

The notebooks post-process `result.txt` or `result1.txt`, split the trajectory
columns into individual body coordinates, plot the orbits, and inspect symmetry
or radii such as `r1` and `r2`.

Several notebooks contain hard-coded historical paths such as:

```text
D:/STAFF/pk21220/4BIntegrationProject/FourBody/result1.txt
```

Update those paths before running the notebooks on a new machine.

Some notebooks expect an 18-column result file even when the filename is
`result.txt`. Check the notebook import cell against the output produced by the
program you actually ran.

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
current settings that can create a large output file. Reduce the loop count or
output frequency before exploratory runs.

Near-collision states can make the force terms large because the denominator is
`||r_i-r_j||^3`; the legacy code does not include collision regularization.

## Repository hygiene

Old executables, DLLs, import libraries, debugger databases, precompiled
headers, object files, and Developer Studio user/cache files were intentionally
left out. See `docs/cleanup-notes.md` for the cleanup rationale.

No license file is included yet. Add one before publishing publicly if you want
to grant reuse rights.
