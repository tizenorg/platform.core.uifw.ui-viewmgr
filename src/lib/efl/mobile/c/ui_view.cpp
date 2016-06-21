#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_view.h"
#include "../../../../include/efl/mobile/c/_ui_common_view_capi.h"

using namespace efl_viewmanager;

static const char *_this_type = "ui_view";

class ui_view_capi: public ui_view, public ui_common_view_capi
{
public:
	void on_load()
	{
		if (this->lifecycle_callback.load)
		{
			if (!this->lifecycle_callback.load(this, this->lifecycle_data)) return;
		}
		ui_view::on_load();
	}

	void on_unload()
	{
		if (this->lifecycle_callback.unload)
		{
			if (!this->lifecycle_callback.unload(this, this->lifecycle_data)) return;
		}
		ui_view::on_unload();
	}

	void on_pause()
	{
		if (this->lifecycle_callback.pause)
		{
			if (!this->lifecycle_callback.pause(this, this->lifecycle_data)) return;
		}
		ui_view::on_pause();
	}

	void on_resume()
	{
		if (this->lifecycle_callback.resume)
		{
			if (!this->lifecycle_callback.resume(this, this->lifecycle_data)) return;
		}
		ui_view::on_resume();
	}

	void on_activate()
	{
		if (this->lifecycle_callback.activate)
		{
			if (!this->lifecycle_callback.activate(this, this->lifecycle_data)) return;
		}
		ui_view::on_activate();
	}

	void on_deactivate()
	{
		if (this->lifecycle_callback.deactivate)
		{
			if (!this->lifecycle_callback.deactivate(this, this->lifecycle_data)) return;
		}
		ui_view::on_deactivate();
	}

	void on_destroy()
	{
		if (this->lifecycle_callback.destroy)
		{
			if (!this->lifecycle_callback.destroy(this, this->lifecycle_data)) return;
		}
		ui_view::on_destroy();
	}

	void on_portrait()
	{
		if (this->event_callback.portrait)
		{
			if (!this->event_callback.portrait(this, this->event_data)) return;
		}
		ui_view::on_portrait();
	}

	void on_landscape()
	{
		if (this->event_callback.landscape)
		{
			if (!this->event_callback.landscape(this, this->event_data)) return;
		}
		ui_view::on_landscape();
	}

	void on_rotate(int degree)
	{
		if (this->event_callback.rotate)
		{
			if (!this->event_callback.rotate(this, degree, this->event_data)) return;
		}
		ui_view::on_rotate(degree);
	}

	void on_back()
	{
		if (this->event_callback.back)
		{
			if (!this->event_callback.back(this, this->event_data)) return;
		}
		ui_view::on_back();
	}

	void on_menu(ui_menu *menu)
	{
		if (this->event_callback.menu)
		{
			if (!this->event_callback.menu(menu, this->event_data)) return;
		}
		ui_view::on_menu(menu);
	}

	ui_view_capi(const char *name)
			: ui_view(name), ui_common_view_capi(_this_type)
	{
	}

	~ui_view_capi()
	{
	}
};

struct ui_view_s
{
	ui_view_capi *p;
};

static bool validate_view(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view = NULL");
		return false;
	}
	return true;
}

EAPI ui_view* ui_view_create(const char *name)
{
	return new ui_view_capi(name);
}

EAPI bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data)
{
	if (!validate_view(view)) return false;

	ui_common_view_capi *event_attr = dynamic_cast<ui_common_view_capi *>(view);
	if (!event_attr)
	{
		LOGE("This view(%p) doesn't allow lifecycle callback?!");
		return false;
	}

	if (lifecycle_callback)
	{
		event_attr->lifecycle_callback = *lifecycle_callback;
	}
	event_attr->lifecycle_data = data;

	return true;
}

EAPI bool ui_view_event_callbacks_set(ui_view *view, ui_view_event_callback_s *event_callback, void *data)
{
	if (!validate_view(view)) return false;

	ui_common_view_capi *event_attr = dynamic_cast<ui_common_view_capi *>(view);
	if (!event_attr)
	{
		LOGE("This view(%p) doesn't allow event callback?!");
		return false;
	}

	if (event_callback)
	{
		event_attr->event_callback = *event_callback;
	}
	event_attr->event_data = data;

	return true;
}

EAPI Evas_Object* ui_view_base_get(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->get_base();
}

EAPI Evas_Object *ui_view_content_unset(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->unset_content();
}

EAPI void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator)
{
	if (!validate_view(view)) return;
	view->set_indicator(indicator);
}

EAPI ui_view_indicator ui_view_indicator_get(ui_view *view)
{
	if (!validate_view(view)) return UI_VIEW_INDICATOR_UNKNOWN;
	return view->get_indicator();
}

EAPI void ui_view_removable_content_set(ui_view *view, bool remove)
{
	if (!validate_view(view)) return;
	view->set_removable_content(remove);
}

EAPI bool ui_view_removable_content_get(ui_view *view)
{
	if (!validate_view(view)) return false;
	return view->get_removable_content();
}

EAPI int ui_view_degree_get(ui_view *view)
{
	if (!validate_view(view)) return -1;
	return view->get_degree();
}

EAPI bool ui_view_transition_style_set(ui_view *view, const char *style)
{
	if (!validate_view(view)) return false;
	return view->set_transition_style(style);
}

EAPI const char *ui_view_transition_style_get(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->get_transition_style();
}

EAPI const ui_menu *ui_view_menu_get(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->get_menu();
}

EAPI const char *ui_view_name_get(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->get_name();
}

EAPI ui_view_state ui_view_state_get(ui_view *view)
{
	if (!validate_view(view)) return UI_VIEW_STATE_UNKNOWN;
	return view->get_state();
}

EAPI Evas_Object *ui_view_content_get(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->get_content();
}

EAPI bool ui_view_destroy(ui_view *view)
{
	if (!validate_view(view)) return false;
	delete (view);
	return true;
}

EAPI bool ui_view_content_set(ui_view *view, Evas_Object *content)
{
	if (!validate_view(view)) return false;
	return view->set_content(content);
}

EAPI const char *ui_view_type_get(ui_view *view)
{
	if (!validate_view(view)) return false;
	return dynamic_cast<ui_common_view_capi *>(view)->type;
}
