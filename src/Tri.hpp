#ifndef BROT_TRI_H
#define BROT_TRI_H

#include "Brot.hpp"

#include <array>

class Tri {
    public:
        Tri(Vec3 a, Vec3 b, Vec3 c) : verts{{a, b, c}} {};
        Vec3 get_a() const {return verts[0];};
        Vec3 get_b() const {return verts[1];};
        Vec3 get_c() const {return verts[2];};
        Vec3 operator[](std::size_t i) const {return verts[i];};
        //std::shared_ptr<Material> get_mat() const {return mat;};

    private:
        std::array<Vec3, 3> verts;
};

#endif
