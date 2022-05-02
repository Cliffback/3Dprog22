#pragma once
#include "visualobject.h"
class Camera;
class Billboard : public VisualObject
{
public: 
	Billboard(Scene &scene, Shader* shaderProgram, Camera* camera);
	~Billboard();

	void init() override;
	void draw() override;
	void createObject();
	void rotate();

	Camera* mCamera{ nullptr };

	glm::vec3 squareVertices;
	glm::vec3 billboardSize;
	glm::vec3 billboardCenter;

};

