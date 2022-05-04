#include "enemy.h"
#include "heightmap.h"
#include "scene.h"
#include "token.h"

Enemy::Enemy(Scene& scene, Shader* shaderProgram) : VisualObject(scene, shaderProgram), mx{ 0.0f }, my{ 0.0f }, mz{ 0.0f }
{

	float unit{ 2.f };
	float xmin{ unit * -1 }, xmax{ xmin * -1 }, xmid{ xmin + xmax }, ymin{ xmin }, ymax{ ymin * -1 }, zmin{ unit / 2 * -1 }, zmax{ unit }, zmid{ xmid };

	mVertices.push_back(Vertex{ xmin, ymin, zmin, 0,1,0 }); // Bottom Left
	mVertices.push_back(Vertex{ xmax, ymin, zmin, 1,0,0 }); // Bottom right
	mVertices.push_back(Vertex{ xmid, ymax, zmid, 0,0,0 }); // Top

	mVertices.push_back(Vertex{ xmin, ymin, zmin, 0,1,0 }); // Bottom left
	mVertices.push_back(Vertex{ xmax, ymin, zmin, 1,0,1 }); // Bottom right
	mVertices.push_back(Vertex{ xmid, ymin, zmax , 0,0,1 }); // Rear

	mVertices.push_back(Vertex{ xmax, ymin, zmin, 1,0,0 }); // Bottom Right
	mVertices.push_back(Vertex{ xmid, ymax, zmid , 0,0,0 }); // Top
	mVertices.push_back(Vertex{ xmid, ymin, zmax , 0,0,1 }); // Rear

	mVertices.push_back(Vertex{ xmin, ymin, zmin, 0,1,0 }); // Bottom left
	mVertices.push_back(Vertex{ xmid, ymax, zmid , 0,0,0 }); // TOP
	mVertices.push_back(Vertex{ xmid, ymin, zmax , 0,0,1 }); // Rear

	mMatrix.setToIdentity();
	bShape = new AABB();
	std::chrono::duration<int, std::ratio<2> > two_seconds(1);
	cooldown = two_seconds;
	collisionOffset.z = 2.f;

}

Enemy::Enemy(Scene& scene, Shader* shaderProgram, VisualObject* model) : VisualObject(scene, shaderProgram), mModel(model),mx{ 0.0f }, my{ 0.0f }, mz{ 0.0f }
{
	bShape = new AABB();
	std::chrono::duration<int, std::ratio<2> > two_seconds(1);
	cooldown = two_seconds;
	collisionOffset.z = 2.f;
	dynamic_cast<AABB*>(bShape)->extent = glm::vec3(2.f,1.f,4.f);
}

void Enemy::init()
{
	if (mModel)
		mModel->init();

	else
		VisualObject::init();
}

void Enemy::draw()
{
	drawCollision();

	if (mModel)
		mModel->draw();
	else
		VisualObject::draw();
}

void Enemy::move(float x, float y, float z)
{
	//Oppgave 9 - Bomb NPC
	if (bCoolingDown == true)
	{
		current = Clock::now();
		if (current > cooldown + hit)
		{
			bCoolingDown = false;
			return;
		}
		else
			return;
	}

	mx += x * mSpeed;
	my += y * mSpeed;

	if (mHeightmap)
	{
		mz = mHeightmap->getHeight(glm::vec3(mx, my, mz) + 1.f);

		QVector4D pos{ mx,my,mz,1.0f };
		mPosition.setColumn(3, pos);
		mMatrix = mPosition;
		mModel->move(mx, my, mz);

		if (bShape)
			bShape->position = glm::vec3(mx + collisionOffset.x, my + collisionOffset.y, mz + collisionOffset.z);
	}


}

void Enemy::gotHit()
{
	hitTimes++;
	bCoolingDown = true;
	hit = Clock::now();
}

// Oppgave 12
void Enemy::getDestination(std::vector<Token*> tokens)
{
	// Code from here: https://stackoverflow.com/questions/2625021/game-enemy-move-towards-player

	if (myTokens >= tokens.size())
		return;

	glm::vec2 myPos{ getPosition2D().first,getPosition2D().second };
	glm::vec2 tokenPos;


	// Find token with the shortest distance to it
	glm::vec2 minPos{100.f,100.f};

	for (auto it = tokens.begin(); it != tokens.end(); it++)
	{
		if ((*it)->visible)
		{
			tokenPos = glm::vec2((*it)->getPosition2D().first, (*it)->getPosition2D().second);

			if (glm::length(tokenPos) < glm::length(minPos))
				minPos = tokenPos;
		}
	}
	tokenPos = minPos;

	glm::vec2 direction{ tokenPos.x - myPos.x, tokenPos.y - myPos.y };
	glm::vec2 normalizedDirection = glm::normalize(direction);

	move(normalizedDirection.x, normalizedDirection.y, 0.f);
}

void Enemy::setHeightmap(HeightMap* map)
{
	mHeightmap = map;
}

void Enemy::gatherToken()
{
	myTokens++;
	std::cout << "Token found!" << std::endl;
	std::cout << "Tokens gathered: " << myTokens << std::endl;
}
