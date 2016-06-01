#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_popup.h"

using namespace efl_viewmanager;

extern "C" {
	ui_popup *ui_popup_create(ui_view *view)
	{
		return new ui_popup(view);
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

	bool ui_popup_activate(ui_popup *popup)
	{
		if (!popup)
		{
			LOGE("Invalid popup");
			return false;
		}

		return popup->activate();
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
}
