#include "Tracer.hpp"
#include "Material.hpp"
#include "Scene.hpp"

#include <Eigen/Geometry>

#include <algorithm>

Color Tracer::trace(const std::size_t depth, const double score, const Vec3& ray_orig, const Vec3& ray_dir) {
    auto intersect = scene.intersect(ray_orig, ray_dir);
    if(intersect.tri == nullptr)
        return {0., 0., 0.};

    const TriMat& tri = *intersect.tri;

    Vec3 basis_u = tri[1] - tri[0];
    Vec3 basis_v = tri[2] - tri[0];

    Vec3 normal = basis_u.cross(basis_v);
    normal.normalize();

    if(normal.dot(ray_dir) > 0.)
        normal *= -1.;

    const Material* mat = scene.get_mat(tri);
    Color reflected{0., 0., 0.};

    if(rand_gen() > p_return || depth < 1) {
        // Both options are valid. The current one should be slower but more
        // accurate. The accuracy might be unnecessary.
        // Vec3 new_ray_orig = ray_orig + ray_dir * intersect.dist;
        Vec3 new_ray_orig = tri[0] + intersect.u * basis_u + intersect.v * basis_v;

        // A normalized basis will be necessary from here on out
        basis_u.normalize();
        basis_v.normalize();

        std::size_t n_rays = std::max<std::size_t>(8 * score, 1);

        for(std::size_t i = 0; i < n_rays; ++i) {
            auto new_ray_dir = mat->importance_dir(rand_gen(), rand_gen(), normal, basis_u, -ray_dir);

            auto bsdf_v = mat->importance_bsdf(normal, new_ray_dir, -ray_dir);
            auto l_in = trace(depth + 1, score * bsdf_v.maxCoeff() / n_rays, new_ray_orig, new_ray_dir);
            reflected += l_in.cwiseProduct(bsdf_v);
        }

        reflected *= 2. * pi / n_rays;
        if(depth >= 1)
            reflected /= (1. - p_return);
    }

    return mat->emit(normal, -ray_dir) + reflected;
}
