#ifndef _UI_IFACE_SINGLETON_H_
#define _UI_IFACE_SINGLETON_H_

namespace ui_viewmanager
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
	T* pT = reinterpret_cast<T*>(1);

	//Derived Class - Singleton class
	int offset = reinterpret_cast<int>(pT) - reinterpret_cast<int>(reinterpret_cast<singleton<T>*>(pT));
	singleton::inst = reinterpret_cast<T*>((reinterpret_cast<int>(this) + offset));
}

template<typename T>
singleton<T>::~singleton()
{
	singleton::inst = NULL;
}

template<typename T>
T* singleton<T>::get_instance()
{
	return singleton::inst;
}

}

#endif /* _UI_IFACE_SINGLETON_H_ */
