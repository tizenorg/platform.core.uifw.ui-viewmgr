#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_popup.h"

using namespace efl_viewmanager;

extern "C" {
	ui_popup *ui_popup_create(ui_view *view)
	{
		return new ui_popup(view);
	}

	void ui_popup_del(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return;
		}

		delete(popup);
	}

	bool ui_popup_content_set(ui_popup *popup, Elm_Popup *elm_popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return false;
		}

		if (!elm_popup)
		{
			LOGE("Invalid elm_popup");
			return false;
		}

		return popup->set_content(elm_popup);
	}

	Elm_Popup ui_popup_content_get(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return NULL;
		}

		return popup->get_content();
	}

	Elm_Popup *ui_popup_content_unset(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return NULL;
		}

		return popup->unset_content();
	}

	bool ui_popup_activate(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return false;
		}

		return popup->activate();
	}

	bool ui_popup_deactivate(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return false;
		}

		return popup->deactivate();
	}

	bool ui_popup_activate_get(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return false;
		}

		return popup->is_activated();
	}

	Evas_Object *ui_popup_base_get(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return NULL;
		}

		return popup->get_base();
	}

	int ui_popup_degree_get(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return -1;
		}

		return popup->get_degree();
	}

	ui_view *ui_popup_view_get(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return NULL;
		}

		return popup->get_view();
	}
}
