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
}

