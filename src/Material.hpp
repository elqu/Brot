#ifndef BROT_MATERIAL_H
#define BROT_MATERIAL_H

#include "Brot.hpp"

#include <Eigen/Core>

class Material {
    public:
        virtual ~Material() = default;
        virtual Vec3 emit(const Vec3& dir_out) const = 0;
        virtual Vec3 bsdf(const Vec3& dir_in, const Vec3& dir_out) const = 0;
};

class MatLambert : public Material {
    public:
        MatLambert(Vec3 color, Vec3 emit = Vec3::Zero())
            : color{color / pi}, emit_v{std::move(emit)} {};
        virtual Vec3 emit(const Vec3&) const;
        virtual Vec3 bsdf(const Vec3&, const Vec3&) const;
    private:
        Vec3 color, emit_v;
};

#endif
