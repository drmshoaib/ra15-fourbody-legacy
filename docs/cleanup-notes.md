# Cleanup Notes

This clean repository was created from `4BIntegrationProject` while preserving
the original folder.

## Kept

- C++ and Fortran source files.
- Visual Studio 6 project/workspace files.
- MFC resource files and icon resources.
- Initial-condition text files and legacy Excel workbooks.
- Mathematica notebooks, including historical comparison/result notebooks.
- The `Workingfolder` initial condition file and notebook.

## Excluded

- `Debug/` and `Release/` directories.
- Compiled binaries: `*.exe`, `*.dll`.
- Build products: `*.obj`, `*.lib`, `*.exp`, `*.ilk`, `*.res`.
- Debug/precompiled files: `*.pdb`, `*.PDB`, `*.idb`, `*.pch`.
- Visual Studio user/cache/build-log files: `*.ncb`, `*.opt`, `*.plg`, `*.aps`.
- Generated orbit output files such as `result.txt` and `result1.txt`.
- `4BodyIntegrator/stares.txt`, which was empty.

## Duplicate findings

Exact duplicate file hashes found in the original folder:

- `FourBody/4BodyIntegrator.dll`
- `FourBody/Debug/4BodyIntegrator.dll`

Both were generated binaries and were excluded.

The only other exact duplicate hash was for empty files:

- `4BodyIntegrator/stares.txt`
- `WinForInitCond/Debug/WinForInitCond.exe`

Both were excluded.

## Intentional legacy oddities

- The directory name `FourBody/RsultsForComparison` is misspelled in the
  original archive and was kept unchanged to avoid breaking references.
- Several notebooks are variants of the same plotting/checking workflow, but
  they are not exact duplicate files and may preserve distinct historical
  outputs.
- Some notebooks still contain hard-coded old absolute paths.
