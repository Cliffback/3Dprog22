#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"
class Scene;

class Cube : public VisualObject
{
public:
    Cube(Scene& scene, Shader* shaderProgram);
    Cube(Scene& scene, Shader* shaderProgram, float radius);
    Cube(Scene& scene, Shader* shaderProgram, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

    ~Cube() override;
    void construct(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    void draw() override;

 };

#endif // CUBE_H
