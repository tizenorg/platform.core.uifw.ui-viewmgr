#ifndef UI_BASIC_VIEW
#define UI_BASIC_VIEW

#include "../efl_viewmgr.h"

//FIXME: is it correct to define here?
#define EDJ_PATH "/opt/usr/apps/org.tizen.ui-viewmgr/res/ui-viewmgr.edj"
#define GROUP "elm/layout/tizen_view/default"

namespace efl
{

class ui_basic_view: public ui_view
{
private:
	Evas_Object *layout; //Base layout for view
	bool create_layout();
	bool destroy_layout();

protected:
	virtual void load();
	virtual void unload();
	virtual void unload_content();

public:
	ui_basic_view(ui_controller *controller, const char *name = NULL);
	virtual ~ui_basic_view();

	Evas_Object *get_base()
	{
		return this->layout;
	}

	Evas_Object *set_content(Evas_Object *content, const char *title = NULL);
	Evas_Object *set_content(Evas_Object *content, const char *title, const char *subtitle, Evas_Object *icon, Evas_Object *title_left_btn, Evas_Object *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_icon(Evas_Object *icon);
	bool set_title_left_btn(Evas_Object *title_left_btn);
	bool set_title_right_btn(Evas_Object *title_right_btn);
	bool set_title(const char *text);
};

}

#endif /* UI_BASIC_VIEW */
