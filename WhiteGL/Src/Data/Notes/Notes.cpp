#include "Notes.h"
#include "../../Character/Character.h"
#include "../../NotesUI/NotesUI.h"

CNotesAnimation::CNotesAnimation()
{

}

CNotesAnimation::~CNotesAnimation()
{

}

void CNotesAnimation::half(CCharacter* pChara)
{
	pChara->m_state = 0;
	(*pChara->m_pAnimations)[pChara->m_state]->start();
}

void CNotesAnimation::quarter(CCharacter* pChara)
{
	pChara->m_state = 0;
	(*pChara->m_pAnimations)[pChara->m_state]->start();
}

void CNotesAnimation::eighth(CCharacter* pChara)
{
	pChara->m_state = 0;
	(*pChara->m_pAnimations)[pChara->m_state]->start();
}

CNotesAnimation2::CNotesAnimation2()
{

}

CNotesAnimation2::~CNotesAnimation2()
{

}

void CNotesAnimation2::half(CNotesUI* pChara)
{
	//(*pChara->m_pAnimations)[pChara->m_state]->start();
}

void CNotesAnimation2::quarter(CNotesUI* pChara)
{
	(*pChara->m_pAnimations)[pChara->m_state]->start();
}

void CNotesAnimation2::eighth(CNotesUI* pChara)
{
	//(*pChara->m_pAnimations)[pChara->m_state]->start();
}