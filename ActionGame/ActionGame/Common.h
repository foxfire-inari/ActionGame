#pragma once
#include<Dxlib.h>	//Dxlib
#include<assert.h>	//既定の値が入っているかの確認
#include<vector>	//CSVファイルから読み取った文字を保存する
#include<list>		//主にクラスをまとめる配列
#include<array>		//要素数が固定されている配列に使う
#include<string>	//文字列を扱う
#include<float.h>	//フロート型の比較などで使えるマクロ
#include<cmath>		//std::atanなどの計算
#include<math.h>	//sinなどの数学的な計算
#include<xkeycheck.h>

//ブロック1つのサイズ
static const int BLOCK_SIZE = 42;

//ウィンドウサイズ横
static const int WINDOW_X = BLOCK_SIZE * 16;
//ウィンドウサイズ縦
static const int WINDOW_Y = BLOCK_SIZE * 13;

//ウィンドウの中心
static const int WINDOW_MID_X = WINDOW_X/2;
static const int WINDOW_MID_Y = WINDOW_Y/2;

//フレームレート
static const float FPS = 60.f;

//円周率
static const float PI = 3.141592f;

//エラー時の返り値
static const int DX_ERROR = -1;

//テンプレート構造体
template <class Type>
struct Vector2//Vector2型を作成
{
	using value_type = Type;

	value_type x;
	value_type y;

	//座標比較用
	bool operator ==(Vector2 vec)
	{
		//float,double,long型は誤差が生じるため専用の計算を行う
		if (typeid(this.x) != typeid(float) &&
			typeid(this.x) != typeid(double) &&
			typeid(this.x) != typeid(long))
		{
			if (this->x == vec.x &&
				this->y == vec.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//float用
		else if(typeid(this.x) == typeid(float))
		{
			//fabsfで絶対値を取得、FLT_EPSILONより小さければ等しい
			if (fabsf(this->x - vec.x) <= FLT_EPSILON &&
				fabsf(this->y - vec.y) <= FLT_EPSILON)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//double用
		else if (typeid(this.x) == typeid(double))
		{
			if (fabs(this->x - vec.x) <= DBL_EPSILON &&
				fabs(this->y - vec.y) <= DBL_EPSILON)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//long用
		else if (typeid(this.x) == typeid(long))
		{
			if (fabsl(this->x - vec.x) <= LDBL_EPSILON &&
				fabsl(this->y - vec.y) <= LDBL_EPSILON)
			{
				return true;
			}
			else
			{
				return false;
			}

		}
	}

	//加算(Vector)
	Vector2 operator +(Vector2 _vec)
	{
		Vector2 vec;
		vec.x = this->x + _vec.x;
		vec.y = this->y + _vec.y;
		return vec;
	}

	//加算(Vector)
	void operator +=(Vector2 _vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
	}

	//減算(Vector)
	Vector2 operator -(Vector2 _vec)
	{
		Vector2 vec;
		vec.x = this->x - _vec.x;
		vec.y = this->y - _vec.y;
		return vec;
	}

	//減算(Vector)
	void operator -=(Vector2 _vec)
	{
		this->x -= _vec.x;
		this->y -= _vec.y;
	}

	//乗算(float)
	Vector2 operator *(float _scale)
	{
		Vector2 vec;
		vec.x = this->x * _scale;
		vec.y = this->y * _scale;
		return vec;
	}

	//乗算(float)
	void operator *=(float _scale)
	{
		this->x *= _scale;
		this->y *= _scale;
	}
};

//intのVector2
using I_Vec2 = Vector2<int>;
//floatのVector2
using F_Vec2 = Vector2<float>;
//doubleのVector2
using D_Vec2 = Vector2<double>;

/// <summary>
/// ベクトルのサイズをfloat型で返す
/// F_Vec2型以外入れられない
/// </summary>
/// <param name="_vec">ベクトル</param>
/// <returns>ベクトルの大きさ</returns>
static float VSize(F_Vec2 _vec)
{
	//各軸の2乗を出す
	float abs_val = std::pow(_vec.x, 2) + std::pow(_vec.y, 2);
	//返り値は平方根
	return sqrt(abs_val);
}