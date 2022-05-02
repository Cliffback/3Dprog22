#include "examscene.h"
#include "camera.h"
#include "heightmap.h"
#include "shaderhandler.h"
#include "interactiveobject.h"
#include "renderwindow.h"
#include "light.h"
#include "octahedronball.h"

ExamScene::ExamScene(std::vector<Scene*> scenes, ShaderHandler* handler, RenderWindow& renderWindow, float size) : Scene(scenes, handler, renderWindow, size)
{
	mCamera = new Camera(this);
	quadDrawHeight = 0.7f;
	createObjects();
	initQuadTre();

}

ExamScene::~ExamScene()
{
}

void ExamScene::createObjects()
{
	VisualObject* temp;


	// Oppgave 2 - Heightmap
	mObjects.push_back(temp = new HeightMap(*this, mShaderHandler->mShaderProgram[2], new Texture("../3Dprog22/Assets/heightmap.bmp"),1,0.06f,0.5f,-30.f));
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
	mObjects.push_back(temp = new InteractiveObject(*this, mShaderHandler->mShaderProgram[0]));
	temp->setName("player");
	temp->calculateNormals();

	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
		mMap.insert(std::pair<std::string, VisualObject*>((*it)->getName(), *it));

	dynamic_cast<InteractiveObject*>(mMap["player"])->setHeightmap(static_cast<HeightMap*>(mMap["heightmap"]));
}

void ExamScene::init()
{

	for (auto it = mMap.begin(); it != mMap.end(); it++)
		(*it).second->init();

}

void ExamScene::renderObjects()
{
	mShaderHandler->mShaderProgram[0]->init(mCamera);
	mShaderHandler->mShaderProgram[1]->init(mCamera);
	dynamic_cast<PhongShader*>(mShaderHandler->mShaderProgram[2])->init(dynamic_cast<Light*>(mMap["light"]), mCamera);
	dynamic_cast<SkyBoxShader*>(mShaderHandler->mShaderProgram[3])->init(mCamera);

	for (auto it = mMap.begin(); it != mMap.end(); it++)
    (*it).second->draw();

	if (dynamic_cast<Light*>(mMap["light"])->bMove)
		dynamic_cast<Light*>(mMap["light"])->rotate(0.1f);

}

void ExamScene::renderCamera()
{
	mCamera->perspective(60, mRenderWindow.width() / mRenderWindow.height(), 0.1, 100.0); // verticalAngle, aspectRatio, nearPlane,farPlane
	mCamera->lookAt(QVector3D{ getPlayer()->getPosition2D().first,getPlayer()->getPosition2D().second - 10.f,20 }, QVector3D{ getPlayer()->getPosition2D().first,getPlayer()->getPosition2D().second,0 }, QVector3D{ 0,1,0 });

}

