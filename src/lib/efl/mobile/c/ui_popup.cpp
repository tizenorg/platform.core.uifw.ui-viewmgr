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

EAPI bool ui_popup_content_set(ui_popup *popup, Elm_Popup *content)
{
	if (!validate_popup(popup)) return false;
	return popup->set_content(content);
}

EAPI Elm_Popup *ui_popup_content_get(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->get_content();
}

EAPI Elm_Popup *ui_popup_content_unset(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->unset_content();
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

EAPI bool ui_popup_activate_get(ui_popup *popup)
{
	if (!validate_popup(popup)) return false;
	return popup->is_activated();
}

EAPI Evas_Object *ui_popup_base_get(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return popup->get_base();
}

EAPI int ui_popup_degree_get(ui_popup *popup)
{
	if (!validate_popup(popup)) return -1;
	return popup->get_degree();
}

EAPI ui_view *ui_popup_view_get(ui_popup *popup)
{
	if (!validate_popup(popup)) return NULL;
	return dynamic_cast<ui_view *>(popup->get_view());
}
