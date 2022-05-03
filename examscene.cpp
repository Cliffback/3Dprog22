#include <chrono>

#include "examscene.h"
#include "camera.h"
#include "heightmap.h"
#include "shaderhandler.h"
#include "interactiveobject.h"
#include "renderwindow.h"
#include "light.h"
#include "octahedronball.h"
#include "obj.h"
#include "npc.h"
#include "route.h"
#include "skybox.h"
#include "bomb.h"
#include "token.h"
#include "cube.h"
#include "fence.h"
#include "billboard.h"
#include "enemy.h"

ExamScene::ExamScene(std::vector<Scene*> scenes, ShaderHandler* handler, RenderWindow& renderWindow, float size) : Scene(scenes, handler, renderWindow, size)
{
	//mCamera = new Camera(this);
	mCamera = new Camera(this, new OBJ(*this, mShaderHandler->mShaderProgram[2], "../3Dprog22/Assets/models/camera_model.obj", "../3Dprog22/Assets/models/camera_texture.bmp"));

	quadDrawHeight = 5.f;
	createRoutes();
	createObjects();
	initQuadTre();

}

ExamScene::~ExamScene()
{
}

void ExamScene::createObjects()
{
	VisualObject* temp;

	//mObjects.push_back(temp = new OBJ(*this, mShaderHandler->mShaderProgram[2], "../3Dprog22/Assets/models/avokado.obj", "../3Dprog22/Assets/models/avokado.bmp"));
	//temp->setName("avokado");

	// Oppgave 2 - Heightmap
	mObjects.push_back(temp = new HeightMap(*this, mShaderHandler->mShaderProgram[2], new Texture("../3Dprog22/Assets/heightmap.bmp"),1,0.06f,0.5f,0.f));
	temp->setName("heightmap");
	temp->loadTexture(new Texture("../3Dprog22/Assets/grass.bmp"));
	mapSize = dynamic_cast<HeightMap*>(temp)->getSize() / 2;

	// Oppgave 3 - Lys
	mObjects.push_back(temp = new Light(*this, mShaderHandler->mShaderProgram[0], new OctahedronBall(*this, mShaderHandler->mShaderProgram[0],3)));
	temp->setName("light");
	temp->mMatrix.translate(-6.f, -6.f, 10.f);
	temp->mMatrix.scale(10.f);
	dynamic_cast<Light*>(temp)->bMove = true;

	// Oppgave 4 - Spiller
	mObjects.push_back(temp = new InteractiveObject(*this, mShaderHandler->mShaderProgram[2], new OBJ(*this, mShaderHandler->mShaderProgram[2], "../3Dprog22/Assets/character/character_model.obj", "../3Dprog22/Assets/character/character_texture.bmp")));
	temp->setName("player");
//	temp->calculateNormals();
	dynamic_cast<AABB*>(temp->bShape)->extent = glm::vec3{ 1.f, 1.f, 2.1f };
	temp->collisionOffset = glm::vec3(0.f, 0.f, 2.2f);

	// Oppgave 7 - Enemy
	mObjects.push_back(temp = new NPC(*this, mShaderHandler->mShaderProgram[0], mRoutes["route1"],.1f, 1.f, true, true));
	temp->setName("NPC1");
	temp->move(0.f, 0.f, 15.f);

	mObjects.push_back(temp = new SkyBox(*this, mShaderHandler->mShaderProgram[3]));
	temp->setName("skybox");
	temp->move(5.f, 5.f, 20.f);

	Cube* fenceTemp{ nullptr };
	fenceTemp = new Cube(*this, mShaderHandler->mShaderProgram[0], -0.3, 0.3, -5.0f, 5.0f, -2.f, 2.f);

	mObjects.push_back(temp = new Fence(*this, mShaderHandler->mShaderProgram[0], fenceTemp));
	temp->setName("fence1");
	temp->move(5.f, 5.f, 5.f);

	// Oppgave 9
	mObjects.push_back(temp = new Enemy(*this, mShaderHandler->mShaderProgram[2], new OBJ(*this, mShaderHandler->mShaderProgram[2], "../3Dprog22/Assets/character/enemy_model.obj", "../3Dprog22/Assets/character/enemy_texture.bmp")));
	temp->setName("enemy");

	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
		mMap.insert(std::pair<std::string, VisualObject*>((*it)->getName(), *it));

	dynamic_cast<InteractiveObject*>(mMap["player"])->setHeightmap(dynamic_cast<HeightMap*>(mMap["heightmap"]));
	dynamic_cast<Enemy*>(mMap["enemy"])->setHeightmap(dynamic_cast<HeightMap*>(mMap["heightmap"]));
	mMap["enemy"]->move(5.f, 5.f, 0.f);

	tokenSpawner();
}

void ExamScene::createRoutes()
{
	std::vector<Vertex> route1Points;
	route1Points.push_back(Vertex{ 1.f,2.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 3.f,5.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 4.f,3.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 6.f,6.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 8.f,2.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 9.f,5.f,0.f, 0,1,0 });
	route1Points.push_back(Vertex{ 10.f,4.f,0.f, 0,1,0 });
	mRoutes.insert(std::pair<std::string, Route*>{"route1", new Route{ *this, mShaderHandler->mShaderProgram[0], route1Points, -0.072f,0.92628f,1.59003f, -20.f, 35.f }});

	std::vector<Vertex> route2Points;
	route2Points.push_back(Vertex{ 1.f,3.f,0.f, 1,0,0 });
	route2Points.push_back(Vertex{ 3.f,5.f,0.f, 1,0,0 });
	route2Points.push_back(Vertex{ 4.f,2.f,0.f, 1,0,0 });
	route2Points.push_back(Vertex{ 6.f,6.f,0.f, 1,0,0 });
	mRoutes.insert(std::pair<std::string, Route*>{"route2", new Route{ *this, mShaderHandler->mShaderProgram[0], 0.59999f,-6.13333f,17.73332f, -9.2f, 1.0f, 6.0f }});

}

void ExamScene::tokenSpawner()
{
	// Oppgave 8 - Tokens
	srand(time(NULL));
	Cube* cubeTemp{ nullptr };
	QVector3D colorTemp;


	Token* tempToken;
	int max = (int)mapSize*2;
	int min = -(int)mapSize;

	// Setting the height of the tokens
	glm::vec3 tempPos{ 0.f,0.f,0.f };
	float tempHeight{ 0.f };
	float tempOffset{ 2.f };

	colorTemp = QVector3D{ 1,0,0 };
	for (int i = 0; i < 10; ++i)
	{

		cubeTemp = new Cube(*this, mShaderHandler->mShaderProgram[0], 0.5f, colorTemp);

		tempToken = new PlayerToken(*this, mShaderHandler->mShaderProgram[0], cubeTemp);

		tempToken->setName("playertoken" + std::to_string(i));

		tempPos = glm::vec3{
			rand() % max + min,
			rand() % max + min,
			0.f };

		tempHeight = dynamic_cast<HeightMap*>(mMap["heightmap"])->getHeight(tempPos) + tempOffset;

		tempToken->move(tempPos.x, tempPos.y, tempHeight);

		mPlayerTokens.push_back(tempToken);
	}

	// NPC tokens
	colorTemp = QVector3D{ 0,0,1 };

	for (int i = 0; i < 10; ++i)
	{
		std::cout << " rand: " << rand() % max + min << std::endl;

		cubeTemp = new Cube(*this, mShaderHandler->mShaderProgram[0], 0.5f, colorTemp);

		tempToken = new NPCToken(*this, mShaderHandler->mShaderProgram[0], cubeTemp);

		tempToken->setName("npctoken" + std::to_string(i));

		tempPos = glm::vec3{
			rand() % max + min,
			rand() % max + min,
			tempHeight };

		tempHeight = dynamic_cast<HeightMap*>(mMap["heightmap"])->getHeight(tempPos) + tempOffset;

		tempToken->move(tempPos.x, tempPos.y, tempHeight);

		mEnemyTokens.push_back(tempToken);
	}


}

void ExamScene::bombSpawner()
{
	if (dynamic_cast<NPC*>(mMap["NPC1"])->bSpawn)
	{
		Bomb* temp;
		QVector3D npcPos{ mMap["NPC1"]->getXYZ('x'), mMap["NPC1"]->getXYZ('y'),  mMap["NPC1"]->getXYZ('z') };
		mBombs.push_back(temp = new Bomb(*this, mShaderHandler->mShaderProgram[0], QVector3D{ npcPos.x(),npcPos.y(),npcPos.z() }));
		temp->setName("bomb");
		//temp->setName("bomb" + std::to_string(bombNumber));
		temp->move(0.f, 0.f, 5.f);

		dynamic_cast<NPC*>(mMap["NPC1"])->bSpawn = false;
	}

	if (!mBombs.empty())
		for (auto it = mBombs.begin(); it != mBombs.end(); it++)
		{
			(*it)->draw();
			// Code for removing the bomb, using a timer in the Bomb class
			if ((*it)->remove)
				bombDeleteCount++;
		}



}

// Makes sure the bombs are deleted after a while
void ExamScene::bombDeleter()
{
	if (bombDeleteCount > 0 && !mBombs.empty())
		for (int i = 0; i < bombDeleteCount; ++i)
		{
			if (mBombs[i]->remove)
			{
				delete mBombs[0];
				mBombs.erase(mBombs.begin());
				bombNumber--;
				bombDeleteCount--;
			}
		}
}

// Oppgave 11
void ExamScene::billboardSpawner()
{
	QVector3D playerPos{ mMap["player"]->getXYZ('x'), mMap["player"]->getXYZ('y'),  mMap["player"]->getXYZ('z') };
	QVector3D offset{ 0.f,-2.f,0.f };
	QVector3D billboardPos{ playerPos + offset};

	Billboard* temp{ nullptr };

	if (bWonGame)
		temp = new Billboard(*this, mShaderHandler->mShaderProgram[1], mCamera, "../3Dprog22/Assets/youwin.bmp");

	else if (bLostGame)
		temp = new Billboard(*this, mShaderHandler->mShaderProgram[1], mCamera, "../3Dprog22/Assets/youloose.bmp");

	temp->setName("billboard");
	temp->move(billboardPos.x(),billboardPos.y(),billboardPos.z());
	//temp->move(0.f, -2.f, 3.f);
	temp->init();
	mMap.insert(std::pair<std::string, VisualObject*>(temp->getName(), temp));

}

// Oppgave 11 og 12
void ExamScene::checkWon()
{
	if (!bWonGame && dynamic_cast<InteractiveObject*>(mMap["player"])->myTokens >= 10)
	{
		bWonGame = true;
		billboardSpawner();
	}

	else if (!bLostGame && dynamic_cast<Enemy*>(mMap["enemy"])->myTokens >= 10)
	{
		bLostGame = true;
		billboardSpawner();
	}
}

void ExamScene::init()
{

	for (auto it = mMap.begin(); it != mMap.end(); it++)
		(*it).second->init();

	for (auto it = mPlayerTokens.begin(); it != mPlayerTokens.end(); it++)
		(*it)->init();

	for (auto it = mEnemyTokens.begin(); it != mEnemyTokens.end(); it++)
		(*it)->init();

}

void ExamScene::renderObjects()
{
	checkWon();
	bombSpawner();
	dynamic_cast<Enemy*>(mMap["enemy"])->getDestination(mEnemyTokens);

	mShaderHandler->mShaderProgram[0]->init(mCamera);
	mShaderHandler->mShaderProgram[1]->init(mCamera);
	dynamic_cast<PhongShader*>(mShaderHandler->mShaderProgram[2])->init(dynamic_cast<Light*>(mMap["light"]), mCamera);
	dynamic_cast<SkyBoxShader*>(mShaderHandler->mShaderProgram[3])->init(mCamera);

	for (auto it = mMap.begin(); it != mMap.end(); it++)
    (*it).second->draw();

	for (auto it = mPlayerTokens.begin(); it != mPlayerTokens.end(); it++)
		(*it)->draw();

	for (auto it = mEnemyTokens.begin(); it != mEnemyTokens.end(); it++)
		(*it)->draw();

	if (dynamic_cast<Light*>(mMap["light"])->bMove)
		dynamic_cast<Light*>(mMap["light"])->rotate(0.1f);

	bombDeleter();

}

void ExamScene::renderCamera()
{
	mCamera->perspective(60, mRenderWindow.width() / mRenderWindow.height(), 0.1, 100.0); // verticalAngle, aspectRatio, nearPlane,farPlane

	QVector3D playerPos{getPlayer()->getXYZ('x'),getPlayer()->getXYZ('y'),getPlayer()->getXYZ('z')};
	QVector3D camOff{ 0.f,-20.f,10.f }; // The offset of the camera from the player
	QVector3D camPos{ playerPos.x() + camOff.x(),playerPos.y() + camOff.y(),playerPos.z() + camOff.z() };
	QVector3D playerOffset{ 0.f, -2.f,0.f };
	playerPos = QVector3D{ playerPos.x() - playerOffset.x(), playerPos.y() - playerOffset.y() ,playerPos.z() - playerOffset.z() };
	mCamera->lookAt(camPos,playerPos, mCamera->mUp);

	typedef std::chrono::high_resolution_clock Clock;
	auto t2 = Clock::now();
	//std::cout << t2 - t1 << '\n';

}

