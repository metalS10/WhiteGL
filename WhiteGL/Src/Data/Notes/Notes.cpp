#include "Notes.h"

CNotesAnimation::CNotesAnimation()
{

}

CNotesAnimation::~CNotesAnimation()
{

}

void CNotesAnimation::start(CCharacter* pChara)
{
	pChara->m_state = 1;
}

void CNotesAnimation::update(CCharacter* pChara)
{
}

void CNotesAnimation::stop()
{

}