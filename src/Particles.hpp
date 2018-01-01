#pragma once

#include "common.hpp"


class Particles {


public:
    explicit Particles(int numParticles) : numParticles(numParticles) {
        type = new TYPE[numParticles];
        particlePos = new glm::vec4[numParticles];
        particleVelo = new glm::vec4[numParticles];
        particleAccel = new glm::vec4[numParticles];
        radius = new GLfloat[numParticles];
        mass = new GLfloat[numParticles];
        shellDepthFraction = new GLfloat[numParticles];
        elasticSpringConstant = new GLfloat[numParticles];
        inelasticSpringForceReductionFactor = new GLfloat[numParticles];

    }

    int numParticles = 0;

    enum TYPE {
        IRON,
        SILICATE
    };

    TYPE *type = nullptr;

    /// can't use a std::vector, since the gl buffer mapping to cpu space gives an allocated pointer already,
    /// which has to be used.
    //unit: km
    glm::vec4 *particlePos = nullptr;
    //unit: km/s
    glm::vec4 *particleVelo = nullptr;
    //unit: km/s^2
    glm::vec4 *particleAccel = nullptr;
    GLfloat *radius = nullptr;

    //unit: kg
    GLfloat *mass = nullptr;

    GLfloat *shellDepthFraction = nullptr; //P: SDP
    GLfloat *&SDF = shellDepthFraction;

    //unit: kg /(m*s^2)
    GLfloat *elasticSpringConstant = nullptr; //P: K
    GLfloat *&K = elasticSpringConstant;

    GLfloat *inelasticSpringForceReductionFactor = nullptr; //P: KRP
    GLfloat *&KRF = inelasticSpringForceReductionFactor;


    void setParticleType(int particleNum, TYPE type, float radius) {
        this->radius[particleNum] = radius;
        switch (type) {
            case Particles::TYPE::SILICATE:
                this->mass[particleNum] = static_cast<GLfloat>(7.4161E19 * pow(radius / 188.39, 3));
                this->SDF[particleNum] = static_cast<GLfloat>(1 - 0.001);
                this->K[particleNum] = 7.2785E10; // TODO: Should probably scale with radius somehow
                this->KRF[particleNum] = 0.01;
                break;
            case Particles::TYPE::IRON:
                this->mass[particleNum] = static_cast<GLfloat>(1.9549E20 * pow(radius / 188.39, 3));
                this->SDF[particleNum] = static_cast<GLfloat>(1 - 0.01);
                this->K[particleNum] = 2.9114E11; // TODO: Should probably scale with radius somehow
                this->KRF[particleNum] = 0.02;
                break;
        }
    }

    void clear() {
        delete[] type;
        delete[] particlePos;
        delete[] particleVelo;
        delete[] particleAccel;
        delete[] radius;
        delete[] shellDepthFraction;
        delete[] elasticSpringConstant;
        delete[] inelasticSpringForceReductionFactor;

    }

};
