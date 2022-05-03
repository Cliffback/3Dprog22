#pragma once
#include "visualobject.h"
class Enemy :
    public VisualObject
{
public:
    Enemy(Scene& scene, Shader* shaderProgram);

    void draw() override;
    void move(float x, float y, float z) override;

    void getDestination();

	QVector3D test;

};

