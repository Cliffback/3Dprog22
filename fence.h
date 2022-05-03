#pragma once
#include "visualobject.h"
class Cube;
class Fence :
    public VisualObject
{
public:
    Fence(Scene& scene, Shader* shaderProgram);
    Fence(Scene& scene, Shader* shaderProgram, Cube* cube);

    void init() override;
    void draw() override;
    void move(float x, float y, float z) override;

protected:
    Cube* mCube;

};

