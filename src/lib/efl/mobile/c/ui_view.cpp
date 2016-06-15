#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_view.h"
#include "../../../../include/efl/mobile/c/ui_capi_private.h"

using namespace efl_viewmanager;

class ui_view_capi: public ui_view, public ui_view_event_attr
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
			: ui_view(name), ui_view_event_attr()
	{
	}

	~ui_view_capi()
	{
	}
};

bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_view_event_attr *event_attr = dynamic_cast<ui_view_event_attr *>(view);
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

bool ui_view_event_callbacks_set(ui_view *view, ui_view_event_callback_s *event_callback, void *data)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_view_event_attr *event_attr = dynamic_cast<ui_view_event_attr *>(view);
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

Evas_Object* ui_view_base_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}
	return view->get_base();
}

Evas_Object *ui_view_content_unset(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	return view->unset_content();
}

void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return;
	}

	return view->set_indicator(indicator);
}

ui_view_indicator ui_view_indicator_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return UI_VIEW_INDICATOR_LAST;
	}

	return view->get_indicator();
}

void ui_view_removable_content_set(ui_view *view, bool remove)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return;
	}

	view->set_removable_content(remove);
}

bool ui_view_removable_content_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	return view->get_removable_content();
}

int ui_view_degree_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return -1;
	}

	return view->get_degree();
}

bool ui_view_transition_style_set(ui_view *view, const char *style)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	return view->set_transition_style(style);
}

const char *ui_view_transition_style_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	return view->get_transition_style();
}

const ui_menu *ui_view_menu_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	return view->get_menu();
}

bool ui_view_name_set(ui_view *view, const char *name)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	return view->set_name(name);

}

const char *ui_view_name_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	return view->get_name();

}

ui_view_state ui_view_state_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return UI_VIEW_STATE_UNKNOWN;
	}

	return view->get_state();
}

Evas_Object *ui_view_content_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	return view->get_content();
}

bool ui_view_destroy(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}
	delete (view);
	return true;
}

ui_view* ui_view_create(const char *name)
{
	return new ui_view_capi(name);
}

bool ui_view_content_set(ui_view *view, Evas_Object *content)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}
	return view->set_content(content);
}
