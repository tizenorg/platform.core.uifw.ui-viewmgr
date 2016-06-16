#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_view.h"
#include "../../../../include/efl/mobile/c/ui_private.h"

using namespace efl_viewmanager;

class ui_standard_view_capi: public ui_standard_view, public ui_view_event_attr
{
public:
	void on_load()
	{
		if (this->lifecycle_callback.load)
		{
			if (!this->lifecycle_callback.load(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_load();
	}

	void on_unload()
	{
		if (this->lifecycle_callback.unload)
		{
			if (!this->lifecycle_callback.unload(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_unload();
	}

	void on_pause()
	{
		if (this->lifecycle_callback.pause)
		{
			if (!this->lifecycle_callback.pause(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_pause();
	}

	void on_resume()
	{
		if (this->lifecycle_callback.resume)
		{
			if (!this->lifecycle_callback.resume(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_resume();
	}

	void on_activate()
	{
		if (this->lifecycle_callback.activate)
		{
			if (!this->lifecycle_callback.activate(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_activate();
	}

	void on_deactivate()
	{
		if (this->lifecycle_callback.deactivate)
		{
			if (!this->lifecycle_callback.deactivate(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_deactivate();
	}

	void on_destroy()
	{
		if (this->lifecycle_callback.destroy)
		{
			if (!this->lifecycle_callback.destroy(this, this->lifecycle_data)) return;
		}
		ui_standard_view::on_destroy();
	}

	void on_portrait()
	{
		if (this->event_callback.portrait)
		{
			if (!this->event_callback.portrait(this, this->event_data)) return;
		}
		ui_standard_view::on_portrait();
	}

	void on_landscape()
	{
		if (this->event_callback.landscape)
		{
			if (!this->event_callback.landscape(this, this->event_data)) return;
		}
		ui_standard_view::on_landscape();
	}

	void on_rotate(int degree)
	{
		if (this->event_callback.rotate)
		{
			if (!this->event_callback.rotate(this, degree, this->event_data)) return;
		}
		ui_standard_view::on_rotate(degree);
	}

	void on_back()
	{
		if (this->event_callback.back)
		{
			if (!this->event_callback.back(this, this->event_data)) return;
		}
		ui_standard_view::on_back();
	}

	void on_menu(ui_menu *menu)
	{
		if (this->event_callback.menu)
		{
			if (!this->event_callback.menu(menu, this->event_data)) return;
		}
		ui_standard_view::on_menu(menu);
	}

	ui_standard_view_capi(const char *name)
			: ui_standard_view(name), ui_view_event_attr()
	{
	}

	~ui_standard_view_capi()
	{
	}
};

ui_view* ui_standard_view_create(const char *name)
{
	return new ui_standard_view_capi(name);
}

bool ui_standard_view_content_set(ui_view *view, Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn,
        Evas_Object *title_right_btn)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_content(content, title, subtitle, title_left_btn, title_right_btn);
}

bool ui_standard_view_title_set(ui_view *view, const char *text)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_title(text);
}

bool ui_standard_view_sub_title_set(ui_view *view, const char *text)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_subtitle(text);
}

bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_title_badge(badge_text);
}

bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_title_right_btn(title_right_btn);
}

Elm_Button *ui_standard_view_title_right_btn_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->get_title_right_btn();
}

Elm_Button *ui_standard_view_title_right_btn_unset(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->unset_title_right_btn();
}

bool ui_standard_view_title_left_btn_set(ui_view *view, Evas_Object *title_left_btn)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_title_left_btn(title_left_btn);
}

Elm_Button *ui_standard_view_title_left_btn_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->get_title_left_btn();
}

Elm_Button *ui_standard_view_title_left_btn_unset(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->unset_title_right_btn();
}

bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_toolbar(toolbar);
}

Elm_Toolbar *ui_standard_view_toolbar_get(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->get_toolbar();
}

Elm_Toolbar *ui_standard_view_toolbar_unset(ui_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->unset_toolbar();
}

bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim)
{
	if (!view)
	{
		LOGE("Invalid ui_view");
		return false;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);

	return capi_view->set_title_visible(visible, anim);
}
