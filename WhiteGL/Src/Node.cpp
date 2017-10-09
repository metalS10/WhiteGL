#include "Node.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

/**
*@desc	�s��ϊ�
*/
void CNode::transform()
{
	glPushMatrix();

	//x��50.0f�ړ�
	glTranslated(this->m_position.x, this->m_position.y, this->m_position.z);

	//Yaw( x����] )
	glRotated(this->m_rotate.x, 1.0f, 0.0f, 0.0f);
	//Pich( y����] )
	glRotated(this->m_rotate.y, 0.0f, 1.0f, 0.0f);
	//Roll( z����] )
	glRotated(this->m_rotate.z, 0.0f, 0.0f, 1.0f);

	//x��2�{�Ɋg��
	glScaled(this->m_scale.x, this->m_scale.y, this->m_scale.z);

	//�X�v���C�g�̕`��
	this->draw();

	glPopMatrix();

	//�ʒu�̕ύX
	glTranslated(this->m_position.x,this->m_position.y,this->m_position.z);
}