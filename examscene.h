#pragma once
#include "scene.h"
class ExamScene :
    public Scene
{
public: 
	ExamScene(std::vector<Scene*> scenes, ShaderHandler* handler, RenderWindow& renderWindow, float size = 0.f);
	~ExamScene();
	void init() override;
	void renderObjects() override;
	void renderCamera() override;
	void createObjects() override;
private:
	//Light* mLight{ nullptr };
	bool mMove{ true };     //Check if triangle should move
};

