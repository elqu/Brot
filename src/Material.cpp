#include "Material.hpp"

#include <Eigen/Geometry>

Vec3 Material::importance_bsdf(const Vec3& normal,
                               const Vec3& dir_in,
                               const Vec3& dir_out) const {
    return bsdf(normal, dir_in, dir_out);
};

Vec3 Material::importance_dir(Real rand_phi,
                              Real rand_theta,
                              const Vec3& normal,
                              const Vec3& basis_u,
                              const Vec3&) const {
    Eigen::AngleAxisd rot_theta{importance_theta(rand_phi), basis_u};
    Eigen::AngleAxisd rot_phi{importance_phi(rand_theta), normal};
    Eigen::Quaterniond rot = rot_phi * rot_theta;
    return rot * normal;
}

Real Material::importance_phi(Real rand_var) const {
    return 2. * pi * rand_var;
};
Real Material::importance_theta(Real rand_var) const {
    return pi / 2. * rand_var;
};


Vec3 MatLambert::emit(const Vec3&, const Vec3&) const {
    return emit_v;
}

Vec3 MatLambert::bsdf(const Vec3& normal, const Vec3& dir_in, const Vec3&) const {
    return 2. * color * normal.dot(dir_in);
}

Vec3 MatLambert::importance_bsdf(const Vec3&, const Vec3&, const Vec3&) const {
    return color;
}

Real MatLambert::importance_theta(Real rand_var) const {
    return 0.5 * std::acos(1. - 2. * rand_var);
}


Vec3 MatReflect::emit(const Vec3&, const Vec3&) const {
    return emit_v;
}

Vec3 MatReflect::bsdf(const Vec3&, const Vec3&, const Vec3&) const {
    return {0., 0., 0.}; // This really shouldn't be called
}

Vec3 MatReflect::importance_bsdf(const Vec3&, const Vec3&, const Vec3&) const {
    return color;
}

Vec3 MatReflect::importance_dir(Real,
                                Real,
                                const Vec3& normal,
                                const Vec3&,
                                const Vec3& dir_in) const {
    return 2. * normal.dot(dir_in) * normal - dir_in;
}
