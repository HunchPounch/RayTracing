cmake_minimum_required(VERSION 2.8)

project(RayTracing)

set(Second4_src CBox.cpp CSphere.cpp CTetra.cpp functions.cpp main.cpp)
set(Second4_hdr CBox.h CSphere.h CTetra.h functions.h CFactory.h CFactoryBox.h CFactorySphere.h CFactoryTetra.h template.h stb_image_write.h CObject.h CLight.h)

add_executable(${PROJECT_NAME} ${RayTracing_src} ${RayTracing_hdr})