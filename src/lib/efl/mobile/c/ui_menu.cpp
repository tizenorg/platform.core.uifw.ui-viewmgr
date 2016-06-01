#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_menu.h"

using namespace efl_viewmanager;

extern "C" {
	bool ui_menu_content_set(ui_menu *menu, Elm_Ctxpopup *ctxpopup)
	{
		if (!menu)
		{
			LOGE("Invalid Menu");
			return false;
		}

		return menu->set_content(ctxpopup);
	}

	Elm_Ctxpopup *ui_menu_content_unset(ui_menu *menu)
	{
		//TODO
		return NULL;
	}

	bool ui_menu_activate(ui_menu *menu)
	{
		//TODO
		return 1;
	}

	bool ui_menu_deactivate(ui_menu *menu)
	{
		//TODO
		return 1;
	}

	bool ui_menu_activate_get(ui_menu *menu)
	{
		//TODO
		return 1;
	}

	Evas_Object *ui_menu_base_get(ui_menu *menu)
	{
		//TODO
		return NULL;
	}

	int ui_menu_degree_get(ui_menu *menu)
	{
		//TODO
		return 0;
	}

	Elm_Ctxpopup ui_menu_content_get(ui_menu *menu)
	{
		//TODO
		return NULL;
	}

	ui_view *ui_menu_view_get(ui_menu *menu)
	{
		//TODO
		return NULL;
	}
}

