#pragma once
/**
*animation.h
*
*	2017/10/11	Mat
*		�e�N�X�`���̃A�j���[�V����
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Constants.h"

typedef CVec4 CChip;

class CAnimation
{
protected:
	float m_Interval = 0;
	std::vector<CChip*> m_Rect;
	int i = 0;
	int m_Nowrect = 0;
	//�A�j���[�V��������
	int m_number = 0;
	bool m_isLoop = true;
	//���݂̃t���[����
	int m_currentFrame = 0;

public:
	CAnimation(float interval,int number ,bool isLoop):
		m_Interval(interval),m_number(number),m_isLoop(isLoop){}

	virtual CChip* animUpdate()
	{
		i++;
		if (i >= m_Interval)
		{
			i = 0;
			m_Nowrect++;
			if (m_Nowrect <= m_number)
			{
				return m_Rect[m_Nowrect];
			}
			//�Ō�̃A�j���[�V����&���[�v��true�Ȃ�
			else if (m_isLoop)
			{
				m_Nowrect = 0;
				return m_Rect[m_Nowrect];
			}
			//���[�v��false�Ȃ�
			else
			{
				m_Nowrect = m_number;
				return m_Rect[m_Nowrect];
			}
		}
	}

	virtual void addChipData(CChip* pChip){}

	/**
	*	@desc���݃t���[���̃`�b�v���擾����
	*	@return ���݃t���[���̃`�b�v
	*/
	virtual CChip getCurrentChip() = 0;
};

class CListAnimation : public CAnimation
{
protected:
	std::vector<CChip*> m_chipList;

public:
	CListAnimation(int interval, bool isLoop = false) :
		CAnimation(interval,0, isLoop) {}
	~CListAnimation()
	{
		//�`�b�v�̉��
		std::vector<CChip*>::iterator itr = this->m_chipList.begin();
		while (itr != this->m_chipList.end())
		{
			SAFE_DELETE((*itr));
			itr++;
		}
	}
	/**
	*	@desc�`�b�v�f�[�^�̒ǉ�
	*	@param	�`�b�v�f�[�^
	*/
	void addChipData(CChip* pChip)override
	{
		//�؂���͈͂�ǉ�����
		this->m_chipList.push_back(pChip);

		//�؂���͈͂�ǉ�������A�j���[�V�����̍ő吔���X�V����
		this->m_number = this->m_chipList.size();
	}

	/**
	*	@desc���݂̃t���[���̃`�b�v���擾
	*	@return ���݂̃t���[���̃`�b�v
	*/
	virtual CChip getCurrentChip() override
	{
		//�Y�������Z�q�Ŏ擾�����f�[�^���̂�CChip*�@�Ȃ̂ł��̒��g��Ԃ�
		return *(this->m_chipList[this->m_currentFrame]);
	}
};

class CNotAnimation : public CListAnimation
{
private:
	//�Q�Ƃ���`�b�v�f�[�^
	CChip* m_pChip = NULL;
public:
	CNotAnimation() :CListAnimation(0, false) {}
	~CNotAnimation() {}

	/**
	*	@desc�X�V�����͍s�킸�Ԃ��l�͕K��1�ɂȂ�
	*/
	CChip* animUpdate() override { return 0; }
	
	void addChipData(CChip* pChip)override
	{
		this->m_pChip = pChip;
	}
	/**
	*	@desc���݃t���[���̃`�b�v���擾����
	*	@return ���݃t���[���̃`�b�v
	*/
	CChip getCurrentChip() override
	{
		return (*this->m_pChip);
	}
};
