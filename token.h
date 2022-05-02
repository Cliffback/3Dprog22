#ifndef TOKEN_H
#define TOKEN_H

#include "visualobject.h"
#include "trianglesurface.h"
#include "interactiveobject.h"

class Token : public VisualObject
{
public:
    Token(Scene& scene, Shader* shaderProgram);
    Token(Scene& scene, Shader* shaderProgram, VisualObject* object);
    void move(float x, float y, float z) override;
    void construct(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

    void collision(VisualObject* player) override;
    void activate() override;

    void init() override;
    void draw();

    VisualObject* mObject{ nullptr };
    InteractiveObject* mPlayer{ nullptr };
    void hide();
    //QVector3D mPosition;

    float mx, my, mz;

private:

    bool visible{true};

};

#endif // TOKEN_H
