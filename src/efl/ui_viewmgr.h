#ifndef UI_VIEWMGR
#define UI_VIEWMGR

#include <Elementary.h>
#include "../interface/ui_viewmgr.h"

namespace efl
{

class ui_view;

class ui_viewmgr: public ui_viewmgr_base
{
private:
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *base_layout;

	Evas_Object *create_conformant(Evas_Object *win);
	Evas_Object *create_base_layout(Evas_Object *conform);

public:
	ui_viewmgr(const char *pkg);
	~ui_viewmgr();

	bool activate();
	bool deactivate();
	ui_view *push_view(ui_view *view);
	bool pop_view();

	//FIXME: Make this private
	Evas_Object *get_base_layout()
	{
		return this->base_layout;
	}

	Evas_Object *get_window()
	{
		return this->win;
	}
};
}

#endif /* UI_VIEWMGR */
