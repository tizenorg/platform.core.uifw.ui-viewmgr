#ifndef UI_VIEW
#define UI_VIEW

#include <Elementary.h>
#include "ui_view_base.h"

#define CONVERT_TO_EO(T) static_cast<Evas_Object *>((T))
#define CONVERT_TO_T(EO) static_cast<T>((EO))

namespace efl
{
class ui_controller;

class ui_view: public ui_view_base
{
public:
	ui_view(ui_controller *controller, const char *name = NULL);
	virtual ~ui_view();

	virtual Evas_Object *set_content(Evas_Object *content);
	virtual Evas_Object *get_base();

protected:
	virtual void load();
};

}

#endif /* UI_VIEW */
