#ifndef _UI_IFACE_SINGLETON_H_
#define _UI_IFACE_SINGLETON_H_

namespace ui_viewmanager
{

template<typename XX>
class singleton
{
private:
	static XX* inst;

public:
	singleton();
	virtual ~singleton();
	inline static XX* get_instance();
};

template<typename XX> XX* singleton<XX>::inst = NULL;

template<typename XX>
singleton<XX>::singleton()
{
	XX* pT = reinterpret_cast<XX*>(1);

	//Derived Class - Singleton class
	int offset = reinterpret_cast<int>(pT) - reinterpret_cast<int>(reinterpret_cast<singleton<XX>*>(pT));
	singleton::inst = reinterpret_cast<XX*>((reinterpret_cast<int>(this) + offset));
}

template<typename XX>
singleton<XX>::~singleton()
{
	singleton::inst = NULL;
}

template<typename XX>
XX* singleton<XX>::get_instance()
{
	return singleton::inst;
}

}

#endif /* _UI_IFACE_SINGLETON_H_ */
