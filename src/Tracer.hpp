#ifndef BROT_TRACER_H
#define BROT_TRACER_H

#include "Brot.hpp"

#include <random>

// Forward declaration(s):
class Scene;

class RandGenerator {
    public:
        RandGenerator() : engine{(std::random_device{})()} {};
        RandGenerator(double a, double b) : engine{(std::random_device{})()}, dist{a, b} {};
        double operator()() {return dist(engine);};
    private:
        std::mt19937 engine;
        std::uniform_real_distribution<double> dist;
};

class Tracer {
    public:
        Tracer(const Scene& scene, double p_return)
            : scene{scene}, p_return{p_return} {};
        Color trace(std::size_t depth, double score, const Vec3& ray_orig, const Vec3& ray_dir);
    private:
        const Scene& scene;
        double p_return;
        RandGenerator rand_gen;
};

#endif
