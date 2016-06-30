#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_popup.h"

using namespace efl_viewmanager;

struct ui_popup_s
{
	ui_popup *p;
};

static bool validate_popup(ui_popup *popup)
{
	if (!popup)
	{
		LOGE("Invalid ui_popup = NULL");
		return false;
	}
	return true;
}

EAPI ui_popup *ui_popup_create(ui_view *view)
{
	return new ui_popup(view);
}

EAPI void ui_popup_destroy(ui_popup *popup)
{
	if (!validate_popup(popup)) return;
	delete(popup);
}

EAPI bool ui_popup_set_content(ui_popup *popup, Elm_Popup *content)
{
	if (!validate_popup(popup)) return false;
	return popup->setContent(content);
}

EAPI Elm_Popup *ui_popup_get_content(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->getContent();
}

EAPI Elm_Popup *ui_popup_unset_content(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->unsetContent();
}

EAPI bool ui_popup_activate(ui_popup *popup)
{
	if (!validate_popup(popup)) return false;
	return popup->activate();
}

EAPI bool ui_popup_deactivate(ui_popup *popup)
{
	if (!validate_popup(popup)) return false;
	return popup->deactivate();
}

EAPI bool ui_popup_get_activate(ui_popup *popup)
{
	if (!validate_popup(popup)) return false;
	return popup->isActivated();
}

EAPI Evas_Object *ui_popup_get_base(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->getBase();
}

EAPI int ui_popup_get_degree(ui_popup *popup)
{
	if (!validate_popup(popup)) return -1;
	return popup->getDegree();
}

EAPI ui_view *ui_popup_get_view(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return dynamic_cast<ui_view *>(popup->getView());
}
