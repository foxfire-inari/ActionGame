#pragma once
#include<Dxlib.h>
#include<assert.h>
#include<vector>
#include<list>
#include<array>
#include<string>
#include<float.h>
#include <cmath>
#include<math.h>
#include <typeinfo>

//ウィンドウサイズ横
static const int Window_X = 800;
//ウィンドウサイズ縦
static const int Window_Y = 600;

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

	/// <summary>
	/// ベクトルのサイズをfloat型で返す
	/// float型以外で使ったら止まる
	/// </summary>
	/// <param name="_vec">ベクトル</param>
	/// <returns>ベクトルの大きさ</returns>
	static float VSize(Vector2 _vec)
	{
		assert(typeid(_vec.x) == typeid(float));
		float abs_val = std::pow(_vec.x, 2) + std::pow(_vec.y, 2);

		return sqrt(abs_val);
	}
};

//intのVector2
using I_Vec2 = Vector2<int>;
//floatのVector2
using F_Vec2 = Vector2<float>;
//doubleのVector2
using D_Vec2 = Vector2<double>;
