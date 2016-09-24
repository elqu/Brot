#include "Tracer.hpp"

#include <Eigen/Core>
#include <Eigen/Geometry>

Vec3 Tracer::trace(const double p_return, const Vec3& ray_orig, const Vec3& ray_dir) {
    auto intersect = scene.intersect(ray_orig, ray_dir);
    if(intersect.tri == nullptr)
        return {0., 0., 0.};

    const TriMat& tri = *intersect.tri;

    Vec3 basis_u = tri[1] - tri[0];
    Vec3 basis_v = tri[2] - tri[0];

    // Both options are valid. The current one should be slower but more
    // accurate. The accuracy might be unnecessary.
    // Vec3 new_ray_orig = ray_orig + ray_dir * intersect.dist;
    Vec3 new_ray_orig = tri[0] + intersect.u * basis_u + intersect.v * basis_v;

    Vec3 normal = basis_u.cross(basis_v);
    normal.normalize();

    if(normal.dot(ray_dir) > 0.)
        normal *= -1.;

    // A normalized basis will be necessary from here on out
    basis_u.normalize();
    basis_v.normalize();

    Eigen::AngleAxisd rot_theta{0.5 * std::acos(1. - 2. * rand_gen()), basis_u};
    Eigen::AngleAxisd rot_phi{2. * pi * rand_gen(), normal};
    Eigen::Quaterniond rot = rot_phi * rot_theta;
    Vec3 new_ray_dir = rot * normal;

    Vec3 reflected;
    if(rand_gen() > p_return)
        reflected = pi * trace(p_return, new_ray_orig, new_ray_dir);
    else
        reflected = {0., 0., 0.};

    reflected /= (1. - p_return);

    Material* mat = scene.get_mat(tri);
    Vec3 result = mat->emit(-ray_dir)
                  + mat->bsdf(new_ray_dir, -ray_dir).cwiseProduct(reflected);

    return result;
}
