#pragma once
#include"Common.h"

template<typename T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	/// <summary>
	/// ƒ|ƒCƒ“ƒ^‚ğ•Ô‚·
	/// </summary>
	/// <returns></returns>
	static T* GetInstance() {
		return instance;
	};

	/// <summary>
	/// ¶¬
	/// </summary>
	static void Create()
	{
		if (instance == nullptr)instance = new T;
	}

	/// <summary>
	/// íœ
	/// </summary>
	static void Destroy()
	{
		if (instance != nullptr)delete instance;
		instance = nullptr;
	}
};