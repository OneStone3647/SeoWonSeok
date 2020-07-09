#pragma once

template<typename T>
class Singleton
{
private:
	static T* m_This;

protected:
	Singleton()
	{

	}

	virtual ~Singleton()
	{

	}

public:
	static T* GetInstance()
	{
		if (m_This == nullptr)
		{
			m_This = new T;
		}

		return m_This;
	};

	static void DestroyInstance()
	{
		if (m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	};
};

template<typename T> T* Singleton<T>::m_This = 0;