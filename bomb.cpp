#include "bomb.h"
#include "interactiveobject.h"

Bomb::Bomb(Scene& scene, Shader* shaderProgram, QVector3D spawnAt)
	: VisualObject(scene, shaderProgram), mx(spawnAt.x()),my(spawnAt.y()),mz(spawnAt.z())
{
    construct();
    VisualObject::move(mx, my, mz);
    init();

    // Code for removing the bomb after a certain time
    born = Clock::now();
    std::chrono::duration<int, std::ratio<20> > twenty_seconds(1);
    lifetime = twenty_seconds;
}

Bomb::~Bomb()
{

}

void Bomb::construct()
{
    float unit{ 0.5f };
    float xmin{ -unit }, xmax{ unit }, ymin{ -unit }, ymax{ unit }, zmin{ -unit }, zmax{ unit };

    //front
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0 }); // A
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); // C
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B

    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); // C
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); // D
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B

    //right
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); // D
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1 }); // H

    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1 }); // H
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); // D
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1 }); // F

    //left
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0 }); //A
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); //G
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); //C

    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); //G
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); //E
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); //C

    //back
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); // G
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1 }); //H
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); // E

    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); // E
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1 }); // H
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1 }); // F


    //top
    mVertices.push_back(Vertex{ xmin, ymax, zmin,  0,0,1 }); //C
    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); //E
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); //D

    mVertices.push_back(Vertex{ xmin, ymax, zmax,  0,1,0 }); //E
    mVertices.push_back(Vertex{ xmax, ymax, zmax,  1,1,1 }); //F
    mVertices.push_back(Vertex{ xmax, ymax, zmin,  1,0,1 }); //D

    //bottom
    mVertices.push_back(Vertex{ xmin, ymin, zmin,  0,0,0 }); // A
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B
    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); // G

    mVertices.push_back(Vertex{ xmin, ymin, zmax,  1,1,0 }); // G
    mVertices.push_back(Vertex{ xmax, ymin, zmin,  1,0,0 }); // B
    mVertices.push_back(Vertex{ xmax, ymin, zmax,  0,1,1 }); // H

    mMatrix.setToIdentity();

    bShape = new AABB();
    dynamic_cast<AABB*>(bShape)->extent = glm::vec3 { 1.f };
}

void Bomb::draw()
{

    current = Clock::now();

    if (current > lifetime + born)
        remove = true ;

	fall();

    if(!visible)
    {
        move(mx, my, -40.f);
    }
    else
    {
	    
		drawCollision();
		VisualObject::draw();
    }
}

void Bomb::fall()
{
    float speed{ 0.01f };
    mz -= speed;
	VisualObject::move(mx,my,mz);

    if (bShape)
        bShape->position = glm::vec3(mx, my, mz);
}

void Bomb::collision(VisualObject* player)
{


	dynamic_cast<InteractiveObject*>(player)->gotHit();

    visible = false;

}
