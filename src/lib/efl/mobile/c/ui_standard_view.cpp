#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_view.h"
#include "../../../../include/efl/mobile/c/ui_standard_view.h"
#include "../../../../include/efl/mobile/c/_ui_common_view_capi.h"

static const char *_this_type = "ui_standard_view";

class ui_standard_view_capi: public ui_standard_view, public ui_common_view_capi
{
public:
	void onLoad()
	{
		if (this->lifecycle_callback.load)
		{
			if (!this->lifecycle_callback.load(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onLoad();
	}

	void onUnload()
	{
		if (this->lifecycle_callback.unload)
		{
			if (!this->lifecycle_callback.unload(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onUnload();
	}

	void onPause()
	{
		if (this->lifecycle_callback.pause)
		{
			if (!this->lifecycle_callback.pause(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onPause();
	}

	void onResume()
	{
		if (this->lifecycle_callback.resume)
		{
			if (!this->lifecycle_callback.resume(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onResume();
	}

	void onActivate()
	{
		if (this->lifecycle_callback.activate)
		{
			if (!this->lifecycle_callback.activate(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onActivate();
	}

	void onDeactivate()
	{
		if (this->lifecycle_callback.deactivate)
		{
			if (!this->lifecycle_callback.deactivate(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onDeactivate();
	}

	void onDestroy()
	{
		if (this->lifecycle_callback.destroy)
		{
			if (!this->lifecycle_callback.destroy(this, this->lifecycle_data)) return;
		}
		ui_standard_view::onDestroy();
	}

	void onPortrait()
	{
		if (this->event_callback.portrait)
		{
			if (!this->event_callback.portrait(this, this->event_data)) return;
		}
		ui_standard_view::onPortrait();
	}

	void onLandscape()
	{
		if (this->event_callback.landscape)
		{
			if (!this->event_callback.landscape(this, this->event_data)) return;
		}
		ui_standard_view::onLandscape();
	}

	void onRotate(int degree)
	{
		if (this->event_callback.rotate)
		{
			if (!this->event_callback.rotate(this, degree, this->event_data)) return;
		}
		ui_standard_view::onRotate(degree);
	}

	void onBack()
	{
		if (this->event_callback.back)
		{
			if (!this->event_callback.back(this, this->event_data)) return;
		}
		ui_standard_view::onBack();
	}

	void onMenu(ui_menu *menu)
	{
		if (this->event_callback.menu)
		{
			if (!this->event_callback.menu(menu, this->event_data)) return;
		}
		ui_standard_view::onMenu(menu);
	}

	ui_standard_view_capi(const char *name)
			: ui_standard_view(name), ui_common_view_capi(_this_type)
	{
	}

	~ui_standard_view_capi()
	{
	}
};

struct ui_standard_view_s
{
	ui_standard_view_capi *p;
};

static ui_standard_view_capi *validate_view(ui_standard_view *view)
{
	if (!view)
	{
		LOGE("Invalid ui_standard_view = NULL");
		return NULL;
	}

	ui_standard_view_capi *capi_view = dynamic_cast<ui_standard_view_capi *>(view);
	if (!capi_view)
	{
		LOGE("Invalid ui_standard_view = %p. Probably, you passed ui_view, not ui_standard_view.", view);
		return NULL;
	}

	return capi_view;
}

EAPI ui_standard_view* ui_standard_view_create(const char *name)
{
	return new ui_standard_view_capi(name);
}

EAPI bool ui_standard_view_set_title(ui_standard_view *view, const char *text)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setTitle(text);
}

EAPI bool ui_standard_view_set_sub_title(ui_standard_view *view, const char *text)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setSubtitle(text);
}

EAPI bool ui_standard_view_set_title_badge(ui_standard_view *view, const char *badge_text)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setTitleBadge(badge_text);
}

EAPI bool ui_standard_view_set_title_right_btn(ui_standard_view *view, Evas_Object *title_right_btn)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setTitleRightBtn(title_right_btn);
}

EAPI Elm_Button *ui_standard_view_get_title_right_btn(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->getTitleRightBtn();
}

EAPI Elm_Button *ui_standard_view_unset_title_right_btn(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->unsetTitleRightBtn();
}

EAPI bool ui_standard_view_set_title_left_btn(ui_standard_view *view, Evas_Object *title_left_btn)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setTitleLeftBtn(title_left_btn);
}

EAPI Elm_Button *ui_standard_view_get_title_left_btn(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->getTitleLeftBtn();
}

EAPI Elm_Button *ui_standard_view_unset_title_left_btn(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->unsetTitleRightBtn();
}

EAPI bool ui_standard_view_set_toolbar(ui_standard_view *view, Elm_Toolbar *toolbar)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setToolbar(toolbar);
}

EAPI Elm_Toolbar *ui_standard_view_get_toolbar(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->getToolbar();
}

EAPI Elm_Toolbar *ui_standard_view_unset_toolbar(ui_standard_view *view)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return NULL;
	return capi_view->unsetToolbar();
}

EAPI bool ui_standard_view_set_title_visible(ui_standard_view *view, bool visible, bool anim)
{
	ui_standard_view_capi *capi_view;
	if (!(capi_view = validate_view(view))) return false;
	return capi_view->setTitleVisible(visible, anim);
}
