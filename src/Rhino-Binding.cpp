#include "Rhino-Binding.hpp"

#include <igl/boundary_facets.h>

namespace wildmeshing_rhino
{
    using namespace wildmeshing_binding;
    using namespace Eigen;

    FTETWRAP Tetrahedralizer *MakeFTet(double *verts,
                                       int vertsNum,
                                       int *tris,
                                       int trisNum,
                                       int stopQuality,
                                       int max_its,
                                       int stage,
                                       int stop_p,
                                       double epsilon,
                                       double edge_length_r,
                                       bool skip_simplify,
                                       bool coarsen)
    {
        Tetrahedralizer *tet = new Tetrahedralizer(stopQuality, max_its, stage, stop_p,
                                                   epsilon, edge_length_r, skip_simplify, coarsen);

        MatrixXd V = Map<MatrixXd>(verts, 3, vertsNum).transpose();
        MatrixXi F = Map<MatrixXi>(tris, 3, trisNum).transpose();

        tet->set_mesh(V, F, std::vector<double>());

        return tet;
    }

    FTETWRAP Tetrahedralizer *Tetrahedralize(Tetrahedralizer *tet)
    {
        tet->tetrahedralize();

        return tet;
    }

    FTETWRAP void GetTets(Tetrahedralizer *tet,
                          double **verts,
                          int *vertsNum,
                          int **tets,
                          int *tetsNum,
                          int **tris,
                          int *trisNum,
                          bool smoothOpenBoundary,
                          bool floodFill,
                          bool manifoldSurface,
                          bool use_input_for_wn,
                          bool correctSurfaceOrientation,
                          bool allMesh)
    {
        Eigen::MatrixXd tVerts, flags;
        Eigen::MatrixXi tetSets, triSets;

        tet->get_tet_mesh(smoothOpenBoundary,
                          floodFill,
                          manifoldSurface,
                          use_input_for_wn,
                          correctSurfaceOrientation,
                          allMesh,
                          tVerts,
                          tetSets,
                          flags);

        igl::boundary_facets(tetSets, triSets);
#ifdef WIN32
        *verts = (double *)::CoTaskMemAlloc(sizeof(double) * tVerts.size());

        // copy(map) the location in memory to keep it when loosing scope
        Map<MatrixXd>(*verts, tVerts.cols(), tVerts.rows()) = tVerts.transpose();
        *vertsNum = tVerts.size();

        //tets = tetSets.data();
        *tets = (int *)::CoTaskMemAlloc(sizeof(int) * tetSets.size());

        // copy(map) the location in memory to keep it when loosing scope
        Map<MatrixXi>(*tets, tetSets.cols(), tetSets.rows()) = tetSets.transpose();
        *tetsNum = tetSets.size();

        *tris = (int *)::CoTaskMemAlloc(sizeof(int) * triSets.size());

        // copy(map) the location in memory to keep it when loosing scope
        Map<MatrixXi>(*tris, triSets.cols(), triSets.rows()) = triSets.transpose();
        *trisNum = triSets.size();
#endif
    }

    FTETWRAP void DelTet(Tetrahedralizer *tet)
    {
        delete (tet);
    }
} // namespace wildmeshing_rhino
