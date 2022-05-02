#ifndef NPC_H
#define NPC_H

#include "visualobject.h"
#include "route.h"
#include "trianglesurface.h"

class NPC : public VisualObject
{
public:
    NPC(Scene& scene, Shader* shaderProgram);
    NPC(Scene& scene, Shader* shaderProgram, TriangleSurface* surface, float speed, float radius, bool visiblePath, bool visibleObject);
    NPC(Scene& scene, Shader* shaderProgram, TriangleSurface* surface, Route* route, float speed, float radius, bool visiblePath, bool visibleObject);
    ~NPC() override;
    void construct(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    void move(float dt) override;
    void changeRoute(float speed, Route* route, bool visiblePath, bool visibleObject);
    void init() override;
    void draw() override;
    float getXYZ(char xyz);

private:
    float mx, my, mz; // posisjon
    float mSpeed;
    TriangleSurface* mySurface{ nullptr };
    Route* myRoute{ nullptr };
    bool forward{true};
    bool showPath{false};
    Route* zeroRoute{ nullptr };
    bool showObject{ false };

};

#endif // NPC_H
