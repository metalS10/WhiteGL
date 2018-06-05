#include "NotesUI.h"

CNotesUI::CNotesUI()
{
	this->init();
}

CNotesUI::~CNotesUI()
{

}

bool CNotesUI::init()
{
	std::vector<CAnimation*>* anim = new std::vector<CAnimation*>();

	//�e�N�X�`���̐ݒ�
	this->texPas= IMAGE_WORP;

	//�����A�j���[�V�����̐ݒ�
	anim->push_back(new CChipListAnimation(3, false));
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*anim)[0]->addChipData(new CChip(0, 0, 54, 54));
	(*anim)[0]->addChipData(new CChip(54, 0, 54, 54));
	(*anim)[0]->addChipData(new CChip(54*2, 0, 54, 54));
	(*anim)[0]->addChipData(new CChip(54*3, 0, 54, 54));

	this->m_pAnimations = anim;

	m_pNotes = new CNotesAnimation2();

	return true;
}

void CNotesUI::update()
{
	(*this->m_pAnimations)[m_state]->update();
}


void CNotesUI::half()
{
	m_pNotes->half(this);
}

void CNotesUI::quarter()
{
	m_pNotes->quarter(this);
}

void CNotesUI::eighth()
{
	m_pNotes->eighth(this);
}