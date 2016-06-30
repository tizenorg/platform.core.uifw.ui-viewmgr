#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_menu.h"

using namespace efl_viewmanager;

struct ui_menu_s
{
	ui_menu *p;
};

static bool validate_menu(ui_menu *menu)
{
	if (!menu)
	{
		LOGE("Invalid ui_menu = NULL");
		return false;
	}
	return true;
}

EAPI bool ui_menu_set_content(ui_menu *menu, Elm_Ctxpopup *ctxpopup)
{
	if (!validate_menu(menu)) return false;
	return menu->setContent(ctxpopup);
}

EAPI Elm_Ctxpopup *ui_menu_get_content(ui_menu *menu)
{
	if (!validate_menu(menu)) return NULL;
	return menu->getContent();
}

EAPI Elm_Ctxpopup *ui_menu_unset_content(ui_menu *menu)
{
	if (!validate_menu(menu)) return NULL;
	return menu->unsetContent();
}

EAPI bool ui_menu_activate(ui_menu *menu)
{
	if (!validate_menu(menu)) return false;
	return menu->activate();
}

EAPI bool ui_menu_deactivate(ui_menu *menu)
{
	if (!validate_menu(menu)) return false;
	return menu->deactivate();
}

EAPI bool ui_menu_get_activated(ui_menu *menu)
{
	if (!validate_menu(menu)) return false;
	return menu->isActivated();
}

EAPI Evas_Object *ui_menu_get_base(ui_menu *menu)
{
	if (!validate_menu(menu)) return NULL;
	return menu->getBase();
}

EAPI int ui_menu_get_degree(ui_menu *menu)
{
	if (!validate_menu(menu)) return -1;
	return menu->getDegree();
}

EAPI ui_view *ui_menu_get_view(ui_menu *menu)
{
	if (!validate_menu(menu)) return NULL;
	return dynamic_cast<ui_view *>(menu->getView());
}
