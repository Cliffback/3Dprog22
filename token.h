#ifndef TOKEN_H
#define TOKEN_H

#include "visualobject.h"
#include "trianglesurface.h"
#include "interactiveobject.h"

class NPC;
class Token : public VisualObject
{
public:
    Token(Scene& scene, Shader* shaderProgram);
    Token(Scene& scene, Shader* shaderProgram, VisualObject* object);
    void move(float x, float y, float z) override;
    void construct(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    void collision(VisualObject* object) override { ; };
    void activate() override;

    void init() override;
    void draw();

    VisualObject* mObject{ nullptr };
    InteractiveObject* mPlayer{ nullptr };
    void hide();
    //QVector3D mPosition;

    float mx, my, mz;

    bool visible{true};
private:


};

class PlayerToken : public Token
{
public:
    PlayerToken(Scene& scene, Shader* shaderProgram, VisualObject* object);
	void collision(VisualObject* object) override;

};

class NPCToken : public Token
{
public:
    NPCToken(Scene& scene, Shader* shaderProgram, VisualObject* object);
    void collision(VisualObject* object) override;

};

#endif // TOKEN_H
