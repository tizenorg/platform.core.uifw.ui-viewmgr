#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_view.h"

using namespace efl_viewmanager;

extern "C" {
	ui_view* ui_standard_view_create(const char *name)
	{
		//TODO
		return NULL;
	}

	bool ui_view_lifecycle_callbacks_set(ui_view *view,
										 ui_view_lifecycle_callback_s *lifecycle_callback, void *data)
	{
		//TODO
		return 1;
	}
	Evas_Object* ui_view_base_get(ui_view *view)
	{
		//TODO
		return NULL;
	}

	bool ui_view_content_set(ui_view *view, Evas_Object *content)
	{
		//TODO
		return 1;
	}

	bool ui_standard_view_content_set(ui_view *view, Evas_Object *content,
									  const char *title, const char *subtitle,
									  Evas_Object *title_left_btn, Evas_Object *title_right_btn)
	{
		//TODO
		return 1;
	}

	bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text)
	{
		//TODO
		return 1;
	}

	bool ui_view_indicator_set(ui_view *view, ui_view_indicator indicator)
	{
		//TODO
		return 1;
	}

	bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar)
	{
		//TODO
		return 1;
	}

	void ui_view_removable_content(ui_view *view, bool remove)
	{
		//TODO
	}

	bool ui_view_event_callbacks_set(ui_view *view,
		                             ui_view_event_callback_s *event_callback, void *data)
	{
		//TODO
		return 1;
	}

	bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn)
	{
		//TODO
		return 1;
	}

	bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim)
	{
		//TODO
		return 1;
	}
}
