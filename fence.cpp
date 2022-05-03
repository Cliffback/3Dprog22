#include "fence.h"
#include "cube.h"
#include "interactiveobject.h"

Fence::Fence(Scene& scene, Shader* shaderProgram) : VisualObject(scene, shaderProgram)
{
}

Fence::Fence(Scene& scene, Shader* shaderProgram, Cube* cube) : VisualObject(scene, shaderProgram), mCube(cube)
{
	blockPlayer = true;
	bShape = new AABB();
	dynamic_cast<AABB*>(bShape)->extent = mCube->cubeSize * 1.2f;
}


void Fence::init()
{
	if (mCube)
		mCube->init();

	VisualObject::init();
}

void Fence::draw()
{
	drawCollision();
	if (mCube)
		mCube->draw();
	VisualObject::draw();
}

void Fence::move(float x, float y, float z)
{

	if (mCube)
		mCube->move(x,y,z);

	VisualObject::move(x, y, z);

}
