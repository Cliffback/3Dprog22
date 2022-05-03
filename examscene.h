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
	void tokenSpawner();
	void bombSpawner();
	void bombDeleter();
	void billboardSpawner();

	void checkWon();


private:
	std::unordered_map<std::string, Route*> mRoutes;
	bool mMove{ true };     //Check if triangle should move
	int bombDeleteCount{ 0 };
	int bombNumber{ 0 };
	bool bWonGame{ false };
	bool bLostGame{ false };

	//template<class T> void purge(std::vector<T>& v) {
	//	for (auto item : v) delete item;
	//	v.clear();
	//}

};

