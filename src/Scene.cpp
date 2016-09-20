#include "Scene.hpp"

#include <Eigen/Geometry>

RayTriIntersect Scene::intersect(const Vec3& ray_orig, const Vec3& ray_dir) const {
    constexpr double epsilon = 0.000001;
    RayTriIntersect closest_intersect;

    for(const Tri& tri : tris) {
        Vec3 edge1 = tri[1] - tri[0];
        Vec3 edge2 = tri[2] - tri[0];

        Vec3 p = ray_dir.cross(edge2);

        double det = p.dot(edge1);
        if(-epsilon < det && det < epsilon)
            continue;

        Vec3 t = ray_orig - tri[0];

        double u = t.dot(p) / det;
        if(u < 0. || 1. < u)
            continue;

        Vec3 q = t.cross(edge1);

        double v = ray_dir.dot(q) / det;
        if(v < 0. || 1. < u + v)
            continue;

        double new_dist = edge2.dot(q) / det;
        if(new_dist < closest_intersect.dist && new_dist > epsilon)
            closest_intersect = {new_dist, &tri, u, v};
    }

    return closest_intersect;
}

void Scene::load() {
    // Top, light
    add_tri({
            {-2., 2., -2.},
            {2., 2., -2.},
            {-2., 2., 2.},
    });
    add_tri({
            {2., 2., 2.},
            {2., 2., -2.},
            {-2., 2., 2.},
    });
    // Left
    add_tri({
            {-2., 2., -2.},
            {-2., 2., 2.},
            {-2., -2., 2.},
    });
    add_tri({
            {-2., 2., -2.},
            {-2., -2., 2.},
            {-2., -2., -2.},
    });
    // Back
    add_tri({
            {-2., 2., -2.},
            {-2., -2., -2.},
            {2., 2., -2.},
    });
    add_tri({
            {2., -2., -2.},
            {-2., -2., -2.},
            {2., 2., -2.},
    });
    // Bottom
    add_tri({
            {-2., -2., -2.},
            {-2., -2., 2.},
            {2., -2., -2.},
    });
    add_tri({
            {2., -2., 2.},
            {-2., -2., 2.},
            {2., -2., -2.},
    });
    // Right
    add_tri({
            {2., -2., 2.},
            {2., -2., -2.},
            {2., 2., 2.},
    });
    add_tri({
            {2., -2., -2.},
            {2., 2., -2.},
            {2., 2., 2.},
    });
    // Floating
    add_tri({
            {-0.8, -1.4, 1.},
            {0.6, -1.6, 1.2},
            {0.1, -1.2, -0.6},
    });

}

