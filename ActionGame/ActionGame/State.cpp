#include "State.h"

State::State()
	:nowState{ 0 },
	nextState{ 0 },
	isChangeState{ 0 },
	stateValue{ 0 } 
{
}

State::~State()
{
	allState.clear();
}

void State::SetNextState(std::string stateName)
{
	//�X�e�[�g��ύX����t���O�𗧂Ă�
	isChangeState = true;
	//�ۑ������X�e�[�g����ڍs����X�e�[�g���擾����
	nextState = allState.at(stateName);
}

void State::ChangeState()
{
	//Update�ŌĂԂ��߃t���O���m�F����
	if (isChangeState)
	{
		//�ύX������t���O��߂�
		isChangeState = false;
		//�X�e�[�g��ύX
		nowState = nextState;
	}
}

void State::SetAllStateMember(std::string stateName)
{
	//�z��ɓo�^
	allState[stateName] = stateValue;
	//�z��̔ԍ��𑝂₷
	stateValue++;

}
