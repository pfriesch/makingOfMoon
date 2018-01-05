#pragma once

#include "../../common.hpp"
#include "../../Renderer_I.hpp"
#include "../../Particles.hpp"
#include "../spritesRenderer/CameraRotateCenter.hpp"
#include "../../ShaderProgram.hpp"
#include "SphereRendererInputHandler.hpp"


#include "Camera.hpp"
#include "Model.hpp"

class SphereRenderer : public Renderer_I {
protected:

    Camera camera;
    SphereRendererInputHandler inputHandler;
    ShaderProgram shaderProgram;
    Model sphereModel;

    int numParticles;
    GLuint vboParticlesPos{};

    float cameraAzimuthAngle;
    float cameraPolarAngle;

    void updateCamera(float frameTime);

public:
    void init() override;

    explicit SphereRenderer(int windowWidth, int windowHeight);

    glm::vec4 *allocateParticlesAndInit_cpu(int numParticles, glm::vec4 *particlesPos) override;

    cudaGraphicsResource_t allocateParticlesAndInit_gpu(int numParticles, glm::vec4 *particlesPos) override;

    void render() override;

    void destroy() override;

    Camera_I *getCamera() override;

    InputHandler_I *getInputHandler() override;
};
