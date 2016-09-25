#include "Scene.hpp"
#include "Material.hpp"

#include <Eigen/Geometry>

Scene::Scene() = default;
Scene::~Scene() = default;

Material* Scene::get_mat(const TriMat& tri) const {
    return mats[tri.get_mat()].get();
}

RayTriIntersect Scene::intersect(const Vec3& ray_orig, const Vec3& ray_dir) const {
    RayTriIntersect closest_intersect;

    for(const TriMat& tri : tris) {
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
    auto mat_light = add_mat<MatLambert>(Vec3{0., 0., 0.}, Vec3{0.9, 0.9, 0.9});
    auto mat_grey = add_mat<MatLambert>(Vec3{0.8, 0.8, 0.8});
    auto mat_red = add_mat<MatLambert>(Vec3{0.8, 0.07, 0.07});
    auto mat_green = add_mat<MatLambert>(Vec3{0.07, 0.8, 0.07});
    auto mat_pink = add_mat<MatReflect>(Vec3{0.9, 0.9, 0.9});
    // Top, light
    add_tri({mat_light,
            Vec3{-2., 2., -2.},
            Vec3{2., 2., -2.},
            Vec3{-2., 2., 2.}
    });
    add_tri({mat_light,
            Vec3{2., 2., 2.},
            Vec3{2., 2., -2.},
            Vec3{-2., 2., 2.}
    });
    // Left
    add_tri({mat_red,
            Vec3{-2., 2., -2.},
            Vec3{-2., 2., 2.},
            Vec3{-2., -2., 2.}
    });
    add_tri({mat_red,
            Vec3{-2., 2., -2.},
            Vec3{-2., -2., 2.},
            Vec3{-2., -2., -2.}
    });
    // Back
    add_tri({mat_grey,
            Vec3{-2., 2., -2.},
            Vec3{-2., -2., -2.},
            Vec3{2., 2., -2.}
    });
    add_tri({mat_grey,
            Vec3{2., -2., -2.},
            Vec3{-2., -2., -2.},
            Vec3{2., 2., -2.}
    });
    // Bottom
    add_tri({mat_grey,
            Vec3{-2., -2., -2.},
            Vec3{-2., -2., 2.},
            Vec3{2., -2., -2.}
    });
    add_tri({mat_grey,
            Vec3{2., -2., 2.},
            Vec3{-2., -2., 2.},
            Vec3{2., -2., -2.}
    });
    // Right
    add_tri({mat_green,
            Vec3{2., -2., 2.},
            Vec3{2., -2., -2.},
            Vec3{2., 2., 2.}
    });
    add_tri({mat_green,
            Vec3{2., -2., -2.},
            Vec3{2., 2., -2.},
            Vec3{2., 2., 2.}
    });
    // Floating
    add_tri({mat_pink,
            Vec3{-0.8, -1.4, 1.},
            Vec3{0.6, -1.6, 1.2},
            Vec3{0.1, -1., -0.6}
    });
    add_tri({mat_pink,
            Vec3{-0.7, -0.5, -0.5},
            Vec3{-0.7, 0.5, -0.5},
            Vec3{0.4, 0., 5.}
    });

}
