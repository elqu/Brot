configure_file(Brot.hpp.in Brot.hpp)

add_executable(brot Brot.cpp Material.cpp Scene.cpp Tracer.cpp)

target_compile_options(brot PRIVATE "-Wall" "-Wextra" "-pedantic" "-std=c++14" "-stdlib=libc++" "-O2")

target_link_libraries(brot png z)

set_target_properties(brot PROPERTIES LINK_FLAGS "-stdlib=libc++")
