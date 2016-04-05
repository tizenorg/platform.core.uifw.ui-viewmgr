#ifndef UI_IFACE_SINGLETON_H
#define UI_IFACE_SINGLETON_H

#include <cassert>

using namespace std;

namespace viewmgr
{

template<typename T>
class singleton
{
private:
	static T* inst;

public:
	singleton();
	virtual ~singleton();
	inline static T* get_instance();
};

template<typename T> T* singleton<T>::inst = NULL;

template<typename T>
singleton<T>::singleton()
{
	assert(!singleton::inst);

	T* pT = reinterpret_cast<T*>(1);

	//Derived Class - Singleton class
	int offset = reinterpret_cast<int>(pT) - reinterpret_cast<int>(reinterpret_cast<singleton<T>*>(pT));
	singleton::inst = reinterpret_cast<T*>((reinterpret_cast<int>(this) + offset));
}

template<typename T>
singleton<T>::~singleton()
{
	assert(singleton::inst);
	singleton::inst = NULL;
}

template<typename T>
T* singleton<T>::get_instance()
{
	assert(singleton::inst);
	return singleton::inst;
}

}

#endif /* UI_IFACE_SINGLETON_H_ */
