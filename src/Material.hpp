#ifndef BROT_MATERIAL_H
#define BROT_MATERIAL_H

#include "Brot.hpp"

class Material {
    public:
        virtual ~Material() = default;
        virtual Color emit(const Vec3& normal, const Vec3& dir_out) const = 0;
        virtual Color bsdf(const Vec3& normal,
                          const Vec3& dir_in,
                          const Vec3& dir_out) const = 0;
        virtual Color importance_bsdf(const Vec3& normal,
                                     const Vec3& dir_in,
                                     const Vec3& dir_out) const;
        virtual Vec3 importance_dir(Real rand_phi,
                                    Real rand_theta,
                                    const Vec3& normal,
                                    const Vec3& basis_u,
                                    const Vec3& dir_in) const;
        virtual Real importance_phi(Real rand_var) const;
        virtual Real importance_theta(Real rand_var) const;
};

class MatLambert : public Material {
    public:
        MatLambert(Color color, Color emit = Vec3::Zero())
            : color{color / (2. * pi)}, emit_v{std::move(emit)} {};
        virtual Color emit(const Vec3&, const Vec3&) const;
        virtual Color bsdf(const Vec3& normal,
                          const Vec3& dir_in,
                          const Vec3&) const;
        virtual Color importance_bsdf(const Vec3&,
                                     const Vec3&,
                                     const Vec3&) const;
        virtual Real importance_theta(Real rand_var) const;
    private:
        Color color, emit_v;
};

class MatReflect : public Material {
    public:
        MatReflect(Color color, Color emit = Vec3::Zero())
            : color{color / (2. * pi)}, emit_v{std::move(emit)} {};
        virtual Color emit(const Vec3&, const Vec3&) const;
        virtual Color bsdf(const Vec3&, const Vec3&, const Vec3&) const;
        virtual Color importance_bsdf(const Vec3&,
                                     const Vec3&,
                                     const Vec3&) const;
        virtual Vec3 importance_dir(Real, Real,
                                    const Vec3& normal,
                                    const Vec3&,
                                    const Vec3& dir_in) const;
    private:
        Color color, emit_v;
};

#endif
