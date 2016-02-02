#ifndef UI_BASIC_VIEW
#define UI_BASIC_VIEW

#include "ui_view.h"

namespace efl
{

class ui_basic_view: public ui_view
{
private:
	Evas_Object *layout; //Base layout for view
	bool create_layout();
	bool destroy_layout();

protected:
	void load();
	void unload();

public:
	ui_basic_view(ui_controller *controller);
	virtual ~ui_basic_view();

	Evas_Object *get_base()
	{
		return this->layout;
	}

	Evas_Object *set_content(Evas_Object *content);
	Evas_Object *set_content(Evas_Object *content, const char *title, const char *subtitle = NULL, Evas_Object *title_left_btn = NULL, Evas_Object *title_right_btn = NULL);
};

}

#endif /* UI_BASIC_VIEW */
