#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <QWindow>
#include <QKeyEvent>
#include "visualobject.h"
#include "trianglesurface.h"
#include "tquadtre.h"

class HeightMap;
class InteractiveObject : public VisualObject
{
public:
    InteractiveObject(Scene& scene, Shader* shaderProgram);
	InteractiveObject(Scene& scene, Shader* shaderProgram, VisualObject* model);
    InteractiveObject(Scene& scene, Shader* shaderProgram, TriangleSurface* mySurface);

	void createObject();

    ~InteractiveObject() override;
	void init() override;
    void draw() override;
	void move(float x, float y, float z) override;
	void keyInput(bool key[5], float speed);
	float mathFunction(float dx, float dy);
	float getXYZ(char xyz) override;
	void gatherToken();
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	int getTokens();
	void setHeightmap(HeightMap* map);

	HeightMap* mHeightmap{ nullptr };

	VisualObject* mModel{ nullptr };
   private:
	float mx, my, mz; // posisjon
	TriangleSurface* mySurface{ nullptr };
	int myTokens{0};
	float mSpeed{ 1.f };
	bool mKey[5]{ false };
	gsml::QuadTre<std::string, VisualObject*> mQuadTre;

	float rotate{ 0.f };









};

#endif // INTERACTIVEOBJECT_H
