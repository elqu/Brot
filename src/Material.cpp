#include "Material.hpp"

Vec3 MatLambert::emit(const Vec3&) const {
    return emit_v;
}

Vec3 MatLambert::bsdf(const Vec3&, const Vec3&) const {
    return color;
}
