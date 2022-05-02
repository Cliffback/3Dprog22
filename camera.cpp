#include "camera.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"


Camera::Camera(Scene* scene) : mScene(scene), mEye{0,0,0}
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees,aspect,nearplane,farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{

	if (!bFreeCamera)
	{
        mPosition = eye;
        mVmatrix.lookAt(eye, at, up);

	}
	else
	{
		keyInput(mKey, 0.01f);
        mVmatrix.lookAt(mPosition, mPosition + mForward, mUp);
	}
    update();
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData()); // Om vi bruker vår egen matrise må vi bruke GL_TRUE
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::translate(float dx, float dy, float dz)
{
    mVmatrix.translate(dx,dy,dz);
}

void Camera::keyInput(bool key[5], float speed)
{
	std::cout << "helloo world" << std::endl;


	if (key[6])
		speed = speed * 2;

	float moveX{ 0.0f }, moveY{ 0.0f }, moveZ{0.0f};

	if (key[0]) // W
		mPosition += speed * mForward;

	if (key[1]) // A
		mPosition += -speed * QVector3D::crossProduct(mForward,mUp);

	if (key[2]) // S
		mPosition += -speed * mForward;

	if (key[3]) // D
		mPosition += speed * QVector3D::crossProduct(mForward, mUp);

	if (key[4]) // Q
		mPosition += -speed * mUp;

	if (key[5]) // E
		mPosition += speed * mUp;

	//mPosition += QVector3D(moveX, moveY, 0.f);


}

void Camera::keyPressEvent(QKeyEvent* event)
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
	case Qt::Key_Q:
		mKey[4] = true;
		std::cout << "Q pressed" << std::endl;
		break;
	case Qt::Key_E:
		mKey[5] = true;
		std::cout << "E pressed" << std::endl;
		break;
	case Qt::Key_Shift:
		mKey[6] = true;
		//std::cout << "Shift pressed" << std::endl;
		break;
	default:
		break;
	}
}

void Camera::mouseMoveEvent(QMouseEvent* event)
{
	float newMouseX(event->y());
	float newMouseY(event->x());

	float deltaX = mouseX - newMouseX;
	float deltaY = mouseY - newMouseY;

	mouseX = newMouseX;
	mouseY = newMouseY;

	float rotateX(deltaX * 0.5f);
	float rotateY(deltaY * 0.5f);

	glm::vec3 newForward
		= glm::rotate(
			glm::vec3(mForward.x(), mForward.y(), mForward.z()),
			glm::radians(rotateX),
			glm::normalize(
				glm::cross(
					glm::vec3(mForward.x(), mForward.y(), mForward.z()),
					glm::vec3(mUp.x(), mUp.y(), mUp.z()))));

	newForward = glm::rotate(newForward, glm::radians(rotateY), glm::vec3(mUp.x(), mUp.y(), mUp.z()));

	mForward = QVector3D(newForward.x, newForward.y, newForward.z);

}

void Camera::keyReleaseEvent(QKeyEvent* event)
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

	case Qt::Key_Q:
		mKey[4] = false;
		std::cout << "Q released" << std::endl;
		break;

	case Qt::Key_E:
		mKey[5] = false;
		std::cout << "E released" << std::endl;
		break;

	case Qt::Key_Shift:
		mKey[6] = false;
		break;
	default:
		break;
	}
}

QVector3D Camera::getPosition()
{
    return mPosition;
}

glm::vec3 Camera::getRight()
{
	return glm::vec3(mRight.x(), mRight.y(), mRight.z());
}

glm::vec3 Camera::getForward()
{
	return glm::vec3(mForward.x(), mForward.y(), mForward.z());
}

glm::vec3 Camera::getUp()
{
	return glm::vec3(mUp.x(), mUp.y(), mUp.z());
}



