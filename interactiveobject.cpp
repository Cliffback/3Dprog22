#include "interactiveobject.h"
#include "heightmap.h"
#include "renderwindow.h"
#include "scene.h"
#include "boundingshape.h"

InteractiveObject::InteractiveObject(Scene& scene, Shader* shaderProgram) : VisualObject(scene, shaderProgram), mx{0.0f}, my{0.0f}, mz{0.0f}
{
    createObject();

}

InteractiveObject::InteractiveObject(Scene& scene, Shader* shaderProgram, VisualObject* model) : VisualObject(scene, shaderProgram), mModel(model), mx{ 0.0f }, my{ 0.0f }, mz{ 0.0f }
{
    bShape = new AABB();
}

InteractiveObject::InteractiveObject(Scene& scene, Shader* shaderProgram, TriangleSurface* surface) : VisualObject(scene, shaderProgram), mx{0.0f}, my{0.0f}, mz{0.0f}, mySurface{surface}
{
    createObject();
}

void InteractiveObject::createObject()
{
    float unit{ 2.f };
    float xmin{ unit * -1 }, xmax{ xmin * -1 }, xmid{ 0 }, ymin{ xmin }, ymid{ xmid }, ymax{ ymax }, zmin{ 0 }, zmax{ unit }, zmid{ unit / 2 };

    mVertices.push_back(Vertex{ xmin, ymax, zmin, 0,1,0 }); // Bottom Left
    mVertices.push_back(Vertex{ xmax, ymax, zmin, 1,0,0 }); // Bottom right
    mVertices.push_back(Vertex{ xmid, ymin, zmin, 0,0,0 }); // Bottom mid

    mVertices.push_back(Vertex{ xmid, ymin, zmin, 0,1,0 }); // Bottom mid
    mVertices.push_back(Vertex{ xmax, ymax, zmin, 1,0,1 }); // Bottom right
    mVertices.push_back(Vertex{ xmid, ymid, zmax , 0,0,1 }); // Top

    mVertices.push_back(Vertex{ xmin, ymax, zmin, 1,0,1 }); // Bottom left
    mVertices.push_back(Vertex{ xmid, ymin, zmin, 0,1,0 }); // Bottom mid
    mVertices.push_back(Vertex{ xmid, ymid, zmax , 0,0,1 }); // Top

    mVertices.push_back(Vertex{ xmin, ymax, zmin, 0,1,0 }); // Bottom Left
    mVertices.push_back(Vertex{ xmid, ymid, zmax , 0,0,1 }); // Top
    mVertices.push_back(Vertex{ xmax, ymax, zmin, 1,0,1 }); // Bottom right

    mMatrix.setToIdentity();

    bShape = new AABB();
}

InteractiveObject::~InteractiveObject()
{

}

void InteractiveObject::init()
{
	if (mModel)
        mModel->init();

    else
		VisualObject::init();
}

void InteractiveObject::draw()
{
    drawCollision();

    if (mModel)
    {
        mModel->draw();
    }

    else
    {
        if (mTexture)
        {
            glActiveTexture(mShaderProgram->getShaderSlot());
            glBindTexture(GL_TEXTURE_2D, mTexture->id());
        }

        mShaderProgram->loadShader();

        VisualObject::draw();
    }



    keyInput(mKey, 0.2f);

}


void InteractiveObject::move(float dx, float dy, float dz)
{
    mx += dx * mSpeed;
    my += dy * mSpeed;

    // The following code could probably be set up way better

	if (mModel)
	{
        if (mHeightmap)
        {
            mz = mHeightmap->getHeight(glm::vec3(mx, my, mz));

            mModel->move(mx, my, mz);
            
            QVector4D pos{ mx,my,mz,1.0f };
            mPosition.setColumn(3, pos);
            mMatrix = mPosition;
        }

        else
        {
            float temp = mathFunction(mx, my) - mz; // We get the z-difference since last frame from the surface

        	mModel->move(mx, my, temp);

        	QVector4D pos{ mx,my,temp,1.0f };
            mPosition.setColumn(3, pos);
            mMatrix = mPosition;
            mz = mathFunction(mx, my);
        }
	}

	else
	{
        if (mHeightmap)
        {
            mz = mHeightmap->getHeight(glm::vec3(mx, my, mz));

            QVector4D pos{ mx,my,mz,1.0f };
            mPosition.setColumn(3, pos);
            mMatrix = mPosition;
        }

        else
        {
            float temp = mathFunction(mx, my) - mz; // We get the z-difference since last frame from the surface
            QVector4D pos{ mx,my,temp,1.0f };
            mPosition.setColumn(3, pos);
            mMatrix = mPosition;
            mz = mathFunction(mx, my);

        }
	}

	bShape->position = glm::vec3(mx, my, mz);


    //mScene.initQuadTre();
    //mScene.drawQuads();
    //mScene.collisionCheck();
}

void InteractiveObject::keyInput(bool key[5], float speed)
{
    if (key[4])
        speed = speed * 2;

    float moveX{ 0.0f }, moveY{ 0.0f };

    if (key[0]) // W
        moveY = speed;

    if (key[1]) // A
        moveX = -speed;

    if (key[2]) // S
        moveY = -speed;

    if (key[3]) // D
        moveX = speed;

    move(moveX, moveY, 0.f);
    
}


float InteractiveObject::mathFunction(float dx, float dy)
{

    return mySurface->function(dx,dy);
    //return sin(dx)*dy;
}

float InteractiveObject::getXYZ(char xyz)
{
    switch (xyz)
    {
    case 'x':
        return mx;
        break;
    case 'y':
        return my;
        break;
    case 'z':
        return mz;
        break;
    default:
        return 0.f;
        break;
    }
}

void InteractiveObject::gatherToken()
{
myTokens++;
std::cout << "Token found!" << std::endl;
std::cout << "Tokens gathered: " << myTokens << std::endl;
}


void InteractiveObject::keyPressEvent(QKeyEvent* event)
{

    switch (event->key())
    {
	    case Qt::Key_W:
	        mKey[0] = true;
	        //std::cout << "W pressed" << std::endl;
	        break;
	    case Qt::Key_A:
	        mKey[1] = true;
	        //std::cout << "A pressed" << std::endl;
	        break;
	    case Qt::Key_S:
	        mKey[2] = true;
	        //std::cout << "S pressed" << std::endl;
	        break;
	    case Qt::Key_D:
	        mKey[3] = true;
	        //std::cout << "D pressed" << std::endl;
	        break;
	    case Qt::Key_Shift:
	        mKey[4] = true;
	        //std::cout << "Shift pressed" << std::endl;
	        break;
	    default:
	        break;
    }
}

void InteractiveObject::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key())
	    {
	    case Qt::Key_W:
	        mKey[0] = false;
	        //qDebug() << "released W";
	        //std::cout << "W released" << std::endl;
	        break;
	    case Qt::Key_A:
            mKey[1] = false;
	        //qDebug() << "released A";
	        //std::cout << "A released" << std::endl;
	        break;
	    case Qt::Key_S:
            mKey[2] = false;
            //qDebug() << "released S";
	        //std::cout << "S released" << std::endl;
	        break;
	    case Qt::Key_D:
            mKey[3] = false;
	        //qDebug() << "released D";
	        //std::cout << "D released" << std::endl;
	        break;
        case Qt::Key_Shift:
            mKey[4] = false;
            //qDebug() << "released Shift";
            //std::cout << "Shift released" << std::endl;
            break;
        default:
            break;
	    }
}

int InteractiveObject::getTokens()
{
    return myTokens;
}

void InteractiveObject::setHeightmap(HeightMap* map)
{
    mHeightmap = map;
}
