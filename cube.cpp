#include "cube.h"

Cube::Cube(Scene& scene, Shader* shaderProgram) : VisualObject(scene, shaderProgram)
{

    float xmin{-0.5},  xmax{xmin * -1}, ymin{xmin}, ymax{xmin * -1}, zmin{xmin}, zmax{zmin * -1};
    construct(xmin,xmax,ymin,ymax,zmin,zmax);

    mMatrix.setToIdentity();
    bShape = new AABB();

}

Cube::Cube(Scene& scene, Shader* shaderProgram, float radius) : VisualObject(scene, shaderProgram)
{
    float xmin{radius * -1},  xmax{xmin * -1}, ymin{xmin}, ymax{xmin * -1}, zmin{xmin}, zmax{zmin * -1};
    construct(xmin,xmax,ymin,ymax,zmin,zmax);
    mMatrix.setToIdentity();
    bShape = new AABB();


}

Cube::Cube(Scene& scene, Shader* shaderProgram, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) : VisualObject(scene, shaderProgram)
{
    construct(xmin,xmax,ymin,ymax,zmin,zmax);
    mMatrix.setToIdentity();
    bShape = new AABB();


}

Cube::~Cube() {    }

void Cube::construct(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{

    //front
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0}); // A
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1}); // C
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B

    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1}); // C
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1}); // D
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B

    //right
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0}); // B
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1}); // D
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1}); // H

    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1}); // H
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1}); // D
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1}); // F

	//left
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0 }); //A
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); //G
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); //C

    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); //G
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); //E
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); //C

    //back
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0}); // G
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1}); //H
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0}); // E

    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0}); // E
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1}); // H
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1}); // F


    //top
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1}); //C
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0}); //E
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); //D

    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0}); //E
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1}); //F
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); //D

    //bottom
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0}); // A
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0}); // B
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0}); // G

    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0}); // G
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0}); // B
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1}); // H

}

void Cube::draw()
{
    VisualObject::draw();

    static float speed{1.f};
    mMatrix.rotate(speed, 1.f, 1.0f, 1.f);



}
