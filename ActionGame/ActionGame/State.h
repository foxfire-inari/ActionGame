#pragma once
//配列に名前を付けられるためunordered_mapを使う
#include<unordered_map>
#include<string>

/// <summary>
/// ステートパターンで使う状態
/// </summary>
class State
{
public:
	State();
	~State();

	/// <summary>
	/// 次に移行するステートをセット
	/// </summary>
	/// <param name="stateName">セットするステートの名前</param>
	void SetNextState(std::string stateName);

	/// <summary>
	/// ステートを変える
	/// </summary>
	void ChangeState();

	/// <summary>
	/// 今のステートを返す
	/// </summary>
	/// <returns></returns>
	int GetNowState()const { return nowState; }

	/// <summary>
	/// 次のステートを返す
	/// </summary>
	/// <returns></returns>
	int GetNextState()const { return nextState; }

	/// <summary>
	/// 新しいステートの追加
	/// </summary>
	/// <param name="stateName">追加するステートの名前</param>
	void SetAllStateMember(std::string stateName);

private:

	/// <summary>
	/// 現在のステート
	/// </summary>
	int nowState;

	/// <summary>
	/// 次のステート
	/// </summary>
	int nextState;

	/// <summary>
	/// ステートを変更できるか
	/// </summary>
	bool isChangeState;

	/// <summary>
	/// ステートの連想配列
	/// </summary>
	std::unordered_map<std::string, int> allState;

	/// <summary>
	/// 配列に登録する番号
	/// </summary>
	int stateValue;

};

