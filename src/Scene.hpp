#ifndef BROT_SCENE_H
#define BROT_SCENE_H

#include "Tri.hpp"
#include "Brot.hpp"

#include <limits>
#include <vector>

struct RayTriIntersect {
    RayTriIntersect()
        : dist{std::numeric_limits<Real>::max()}, tri{nullptr} {};
    RayTriIntersect(Real dist, const Tri* tri, Real u, Real v)
        : dist{dist}, tri{tri}, u{u}, v{v} {};
    Real dist;
    const Tri* tri; // TODO: this should have an std::optional<Tri&> instead of a Tri*
    Real u, v;
};

class Scene {
    public:
        void add_tri(const Tri& tri) {tris.push_back(tri);};
        void load(); // Placeholder for proper load
        RayTriIntersect intersect(const Vec3& ray_orig, const Vec3& ray_dir) const;
    private:
        std::vector<Tri> tris;
};

#endif
