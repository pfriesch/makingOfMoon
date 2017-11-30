cmake_minimum_required(VERSION 3.5)
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework GLUT") # compiler version and compiler flags.
endif()
if(UNIX AND NOT APPLE)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()


project(makingOfMoon)


set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")


set(SOURCE_FILES
        ${SRC_DIR}/util/util.cpp
        ${SRC_DIR}/util/util.hpp
        ${SRC_DIR}/util/Camera.cpp
        ${SRC_DIR}/util/Camera.hpp
        ${SRC_DIR}/util/Sphere.hpp
        ${SRC_DIR}/util/sphereGLUT.hpp
        ${SRC_DIR}/util/sphereGLUT.cpp
        ${SRC_DIR}/common.hpp
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/sim/ParticleSimI.hpp
        ${SRC_DIR}/sim/GravitySim.hpp
        ${SRC_DIR}/sim/GravitySim.cpp
        ${SRC_DIR}/util/Timer.hpp
        ${SRC_DIR}/util/Timer.cpp
        ${SRC_DIR}/sim/Particle.hpp
        ${SRC_DIR}/sim/StaticVecFieldRndSim.cpp
        ${SRC_DIR}/sim/StaticVecFieldRndSim.hpp src/util/StaticSphere.cpp src/util/StaticSphere.hpp src/util/ParticleSphere.cpp src/util/ParticleSphere.hpp src/sim/RndAccelFieldSim.cpp src/sim/RndAccelFieldSim.hpp)


add_executable(makingOfMoon ${SOURCE_FILES})

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
include_directories(${GLAD_DIR}/include)
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")


# glm
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}")
target_link_libraries(${PROJECT_NAME} "glm" "${GLM_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}/include")


# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} glfw)