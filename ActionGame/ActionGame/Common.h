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

//�u���b�N1�̃T�C�Y
static const int BLOCK_SIZE = 42;

//�E�B���h�E�T�C�Y��
static const int WINDOW_X = BLOCK_SIZE * 16;
//�E�B���h�E�T�C�Y�c
static const int WINDOW_Y = BLOCK_SIZE * 13;
//�t���[�����[�g
static const float FPS = 60.f;

//�~����
static const float PI = 3.141592f;


template <class Type>
struct Vector2//Vector2�^���쐬
{
	using value_type = Type;

	value_type x;
	value_type y;

	//���W��r�p
	bool operator ==(Vector2 vec)
	{
		//float,double,long�^�͌덷�������邽�ߐ�p�̌v�Z���s��
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
		//float�p
		else if(typeid(this.x) == typeid(float))
		{
			//fabsf�Ő�Βl���擾�AFLT_EPSILON��菬������Γ�����
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
		//double�p
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
		//long�p
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

	//���Z(Vector)
	Vector2 operator +(Vector2 _vec)
	{
		Vector2 vec;
		vec.x = this->x + _vec.x;
		vec.y = this->y + _vec.y;
		return vec;
	}

	//���Z(Vector)
	void operator +=(Vector2 _vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
	}

	//���Z(Vector)
	Vector2 operator -(Vector2 _vec)
	{
		Vector2 vec;
		vec.x = this->x - _vec.x;
		vec.y = this->y - _vec.y;
		return vec;
	}

	//���Z(Vector)
	void operator -=(Vector2 _vec)
	{
		this->x -= _vec.x;
		this->y -= _vec.y;
	}

	//��Z(float)
	Vector2 operator *(float _scale)
	{
		Vector2 vec;
		vec.x = this->x * _scale;
		vec.y = this->y * _scale;
		return vec;
	}

	/// <summary>
	/// �x�N�g���̃T�C�Y��float�^�ŕԂ�
	/// float�^�ȊO�Ŏg������~�܂�
	/// </summary>
	/// <param name="_vec">�x�N�g��</param>
	/// <returns>�x�N�g���̑傫��</returns>
	static float VSize(Vector2 _vec)
	{
		assert(typeid(_vec.x) == typeid(float));
		float abs_val = std::pow(_vec.x, 2) + std::pow(_vec.y, 2);

		return sqrt(abs_val);
	}
};

//int��Vector2
using I_Vec2 = Vector2<int>;
//float��Vector2
using F_Vec2 = Vector2<float>;
//double��Vector2
using D_Vec2 = Vector2<double>;
