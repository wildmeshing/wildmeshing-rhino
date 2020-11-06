#pragma once

#include <tetrahedralize.hpp>

#ifdef WIN32
#define FTETWRAP __declspec(dllexport)
#else
#define FTETWRAP
#endif

namespace wildmeshing_rhino
{
    extern "C"
    {
        FTETWRAP wildmeshing_binding::Tetrahedralizer *MakeFTet(double *verts,
                                                                int vertsNum,
                                                                int *tris,
                                                                int trisNum,
                                                                int stopQuality = 10,
                                                                int max_its = 80,
                                                                int stage = 2,
                                                                int stop_p = -1,
                                                                double epsilon = 1e-3,
                                                                double edge_length_r = 1. / 20.,
                                                                bool skip_simplify = false,
                                                                bool coarsen = true);
        FTETWRAP wildmeshing_binding::Tetrahedralizer *Tetrahedralize(wildmeshing_binding::Tetrahedralizer *tet);
        FTETWRAP void GetTets(wildmeshing_binding::Tetrahedralizer *tet,
                              double **verts,
                              int *vertsNum,
                              int **tets,
                              int *tetsNum,
                              int **tris,
                              int *trisNum,
                              bool smoothOpenBoundary = false,
                              bool floodFill = false,
                              bool manifoldSurface = false,
                              bool use_input_for_wn = true,
                              bool correctSurfaceOrientation = false,
                              bool allMesh = false);

        FTETWRAP void DelTet(wildmeshing_binding::Tetrahedralizer *tet);
        // FTETWRAP void DelTris(int *array);
        // FTETWRAP void DelVerts(float *array);
    }
} // namespace wildmeshing_rhino