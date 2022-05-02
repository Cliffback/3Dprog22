#pragma once
#include "scene.h"
class Route;
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
	void createRoutes();

private:
	std::unordered_map<std::string, Route*> mRoutes;
	bool mMove{ true };     //Check if triangle should move
};

