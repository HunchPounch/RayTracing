cmake_minimum_required(VERSION 2.8)

project(RayTracing)

set(Second4_src CBox.cpp CSphere.cpp CTetra.cpp functions.cpp main.cpp)
set(Second4_hdr CBox.hpp CSphere.hpp CTetra.hpp functions.hpp CFactory.hpp CFactoryBox.hpp CFactorySphere.hpp CFactoryTetra.hpp template.hpp stb_image_write.h CObject.hpp CLight.hpp)

add_executable(${PROJECT_NAME} ${RayTracing_src} ${RayTracing_hdr})
