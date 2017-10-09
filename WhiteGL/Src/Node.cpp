#include "Node.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

/**
*@desc	s—ñ•ÏŠ·
*/
void CNode::transform()
{
	glPushMatrix();

	//x‚É50.0fˆÚ“®
	glTranslated(this->m_position.x, this->m_position.y, this->m_position.z);

	//Yaw( xŽ²‰ñ“] )
	glRotated(this->m_rotate.x, 1.0f, 0.0f, 0.0f);
	//Pich( yŽ²‰ñ“] )
	glRotated(this->m_rotate.y, 0.0f, 1.0f, 0.0f);
	//Roll( zŽ²‰ñ“] )
	glRotated(this->m_rotate.z, 0.0f, 0.0f, 1.0f);

	//x‚ð2”{‚ÉŠg‘å
	glScaled(this->m_scale.x, this->m_scale.y, this->m_scale.z);

	//ƒXƒvƒ‰ƒCƒg‚Ì•`‰æ
	this->draw();

	glPopMatrix();

	//ˆÊ’u‚Ì•ÏX
	glTranslated(this->m_position.x,this->m_position.y,this->m_position.z);
}