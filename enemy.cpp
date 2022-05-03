#include "enemy.h"

Enemy::Enemy(Scene& scene, Shader* shaderProgram) : VisualObject(scene, shaderProgram)
{
}

void Enemy::draw()
{
	VisualObject::draw();
}

void Enemy::move(float x, float y, float z)
{
	VisualObject::move(x, y, z);
}

void Enemy::getDestination()
{
}
