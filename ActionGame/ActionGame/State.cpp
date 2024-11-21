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
	//ステートを変更するフラグを立てる
	isChangeState = true;
	//保存したステートから移行するステートを取得する
	nextState = allState.at(stateName);
}

void State::ChangeState()
{
	//Updateで呼ぶためフラグを確認する
	if (isChangeState)
	{
		//変更したらフラグを戻す
		isChangeState = false;
		//ステートを変更
		nowState = nextState;
	}
}

void State::SetAllStateMember(std::string stateName)
{
	//配列に登録
	allState[stateName] = stateValue;
	//配列の番号を増やす
	stateValue++;

}
