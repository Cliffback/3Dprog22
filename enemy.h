#pragma once
#include "visualobject.h"

class Token;
class HeightMap;
class Enemy :
    public VisualObject
{
public:
    Enemy(Scene& scene, Shader* shaderProgram);
    Enemy(Scene& scene, Shader* shaderProgram, VisualObject* model);

    void init() override;
    void draw() override;
    void move(float x, float y, float z) override;

    void getDestination(std::vector<Token*> tokens);
    void setHeightmap(HeightMap* map);
    HeightMap* mHeightmap{ nullptr };

    void gatherToken();

    int myTokens{ 0 };

    VisualObject* mModel{ nullptr };

private:
    float mx, my, mz; // posisjon
    float mSpeed{ 0.2f };

    typedef std::chrono::system_clock Clock;
    Clock::time_point hit;
    Clock::time_point current;
    Clock::duration cooldown;
};

