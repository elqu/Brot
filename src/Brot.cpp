#include "Scene.hpp"
#include "Tracer.hpp"
#include "Brot.hpp"

#include <Eigen/Geometry>

#include <png++/png.hpp>

#include <array>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstdlib>

png::byte real_to_byte(double real) {
    if(real > 1.)
        real = 1.;
    if(real < 0.)
        real = 0.;

    if(real <= 0.0031308)
        real *= 12.92;
    else
        real = 1.055 * std::pow(real, 1./2.4) - 0.055;

    return 255. * real;
}

int main(int argc, char** argv) {
    printf("Brot v%d.%d.%d\n",
            BROT_VERSION_MAJOR,
            BROT_VERSION_MINOR,
            BROT_VERSION_PATCH);

    const std::size_t n_samples = argc > 1 ? std::strtoul(argv[1], nullptr, 10)
                                           : 20;

    Vec3 p_orig = {0., 0., 8.};
    Vec3 p_dir = {0., 0., -1};
    Vec3 p_up = {0., 1., 0.};
    Vec3 p_right = p_dir.cross(p_up);

    Scene scene;
    scene.load();

    Tracer tracer{scene, 1./6.};
    RandGenerator rand_gen;

    png::image<png::rgb_pixel> image(512, 512);
    for(png::uint_32 y = 0; y < image.get_height(); ++y) {
        for(png::uint_32 x = 0; x < image.get_width(); ++x) {
            std::array<double, 3> real_color{{0., 0., 0.}};
            for(std::size_t i = 0; i < n_samples; ++i) {
                double lambda_x = (((double )x + 0.8 * rand_gen() + 0.1) / image.get_width() - .5) * .036;
                double lambda_y = (.5 - ((double )y + 0.8 * rand_gen() + 0.1) / image.get_height()) * .036;
                Vec3 dir = lambda_x * p_right + lambda_y * p_up + .05 * p_dir;
                dir.normalize();

                auto temp = tracer.trace(0, 1., p_orig, dir);
                real_color[0] += temp[0] / n_samples;
                real_color[1] += temp[1] / n_samples;
                real_color[2] += temp[2] / n_samples;
            }

            image[y][x] = png::rgb_pixel(
                    real_to_byte(real_color[0]),
                    real_to_byte(real_color[1]),
                    real_to_byte(real_color[2])
            );
        }
    }

    image.write("shesh.png");

    return 0;
}
