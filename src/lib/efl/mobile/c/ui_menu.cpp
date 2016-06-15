#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_menu.h"

using namespace efl_viewmanager;

bool ui_menu_content_set(ui_menu *menu, Elm_Ctxpopup *ctxpopup)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return false;
	}

	return menu->set_content(ctxpopup);
}

Elm_Ctxpopup *ui_menu_content_get(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return NULL;
	}

	return menu->get_content();
}

Elm_Ctxpopup *ui_menu_content_unset(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return NULL;
	}

	return menu->unset_content();
}

bool ui_menu_activate(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return false;
	}

	return menu->activate();
}

bool ui_menu_deactivate(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return false;
	}

	return menu->deactivate();
}

bool ui_menu_activated_get(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return false;
	}

	return menu->is_activated();
}

Evas_Object *ui_menu_base_get(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return NULL;
	}

	return menu->get_base();
}

int ui_menu_degree_get(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return -1;
	}

	return menu->get_degree();
}

ui_view *ui_menu_view_get(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu");
		return NULL;
	}

	return dynamic_cast<ui_view *>(menu->get_view());
}
