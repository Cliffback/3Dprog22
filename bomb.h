#pragma once
#include "visualobject.h"
#include <chrono>

class Bomb :
    public VisualObject
{
public:
    Bomb(Scene& scene, Shader* shaderProgram, QVector3D spawnAt);
	~Bomb();
    void construct();
    void draw() override;
	void fall();
    float mx, my, mz; // posisjon
    bool remove{ false };

    void collision(VisualObject* player) override;

private:
    typedef std::chrono::system_clock Clock;
    Clock::time_point born;
	Clock::time_point current;
    Clock::duration lifetime;



};

