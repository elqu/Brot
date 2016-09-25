#ifndef BROT_SCENE_H
#define BROT_SCENE_H

#include "Brot.hpp"
#include "Tri.hpp"

#include <limits>
#include <vector>

// Forward declaration(s):
class Material;

struct RayTriIntersect {
    RayTriIntersect()
        : dist{std::numeric_limits<Real>::max()}, tri{nullptr} {};
    RayTriIntersect(Real dist, const TriMat* tri, Real u, Real v)
        : dist{dist}, tri{tri}, u{u}, v{v} {};
    Real dist;
    const TriMat* tri; // TODO: this should have an std::optional<Tri&> instead of a Tri*
    Real u, v;
};

class Scene {
    public:
        using MatIndex = std::size_t;
        Scene();
        ~Scene();
        void add_tri(const TriMat& tri) {tris.push_back(tri);};
        void add_tri(TriMat&& tri) {tris.push_back(std::move(tri));};
        void load(); // Placeholder for proper load
        RayTriIntersect intersect(const Vec3& ray_orig, const Vec3& ray_dir) const;
        template<typename Mat, typename... Args> MatIndex add_mat(Args&&... args);
        Material* get_mat(std::size_t index) const {return mats[index].get();};
        Material* get_mat(const TriMat& tri) const;
    private:
        Real epsilon = 0.000001;
        std::vector<TriMat> tris;
        std::vector<std::unique_ptr<Material>> mats;
};

template<typename Mat, typename... Args>
Scene::MatIndex Scene::add_mat(Args&&... args) {
    mats.push_back(std::make_unique<Mat>(std::forward<Args>(args)...));
    return mats.size() - 1;
}

#endif
