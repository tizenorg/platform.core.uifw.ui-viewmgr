#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_view.h"
#include "../../../../include/efl/mobile/c/_ui_common_view_capi.h"

static const char *_this_type = "ui_view";

class ui_view_capi: public ui_view, public ui_common_view_capi
{
public:
	void onLoad()
	{
		if (this->lifecycle_callback.load)
		{
			if (!this->lifecycle_callback.load(this, this->lifecycle_data)) return;
		}
		ui_view::onLoad();
	}

	void onUnload()
	{
		if (this->lifecycle_callback.unload)
		{
			if (!this->lifecycle_callback.unload(this, this->lifecycle_data)) return;
		}
		ui_view::onUnload();
	}

	void onPause()
	{
		if (this->lifecycle_callback.pause)
		{
			if (!this->lifecycle_callback.pause(this, this->lifecycle_data)) return;
		}
		ui_view::onPause();
	}

	void onResume()
	{
		if (this->lifecycle_callback.resume)
		{
			if (!this->lifecycle_callback.resume(this, this->lifecycle_data)) return;
		}
		ui_view::onResume();
	}

	void onActivate()
	{
		if (this->lifecycle_callback.activate)
		{
			if (!this->lifecycle_callback.activate(this, this->lifecycle_data)) return;
		}
		ui_view::onActivate();
	}

	void onDeactivate()
	{
		if (this->lifecycle_callback.deactivate)
		{
			if (!this->lifecycle_callback.deactivate(this, this->lifecycle_data)) return;
		}
		ui_view::onDeactivate();
	}

	void onDestroy()
	{
		if (this->lifecycle_callback.destroy)
		{
			if (!this->lifecycle_callback.destroy(this, this->lifecycle_data)) return;
		}
		ui_view::onDestroy();
	}

	void onPortrait()
	{
		if (this->event_callback.portrait)
		{
			if (!this->event_callback.portrait(this, this->event_data)) return;
		}
		ui_view::onPortrait();
	}

	void onLandscape()
	{
		if (this->event_callback.landscape)
		{
			if (!this->event_callback.landscape(this, this->event_data)) return;
		}
		ui_view::onLandscape();
	}

	void onRotate(int degree)
	{
		if (this->event_callback.rotate)
		{
			if (!this->event_callback.rotate(this, degree, this->event_data)) return;
		}
		ui_view::onRotate(degree);
	}

	void onBack()
	{
		if (this->event_callback.back)
		{
			if (!this->event_callback.back(this, this->event_data)) return;
		}
		ui_view::onBack();
	}

	void onMenu(ui_menu *menu)
	{
		if (this->event_callback.menu)
		{
			if (!this->event_callback.menu(menu, this->event_data)) return;
		}
		ui_view::onMenu(menu);
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

EAPI bool ui_view_set_lifecycle_callbacks(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data)
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

EAPI bool ui_view_set_event_callbacks(ui_view *view, ui_view_event_callback_s *event_callback, void *data)
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

EAPI Evas_Object* ui_view_get_base(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->getBase();
}

EAPI Evas_Object *ui_view_unset_content(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->unsetContent();
}

EAPI void ui_view_set_indicator(ui_view *view, ui_view_indicator indicator)
{
	if (!validate_view(view)) return;
	view->setIndicator(indicator);
}

EAPI ui_view_indicator ui_view_get_indicator(ui_view *view)
{
	if (!validate_view(view)) return UI_VIEW_INDICATOR_UNKNOWN;
	return view->getIndicator();
}

EAPI void ui_view_set_removable_content(ui_view *view, bool remove)
{
	if (!validate_view(view)) return;
	view->setRemovableContent(remove);
}

EAPI bool ui_view_get_removable_content(ui_view *view)
{
	if (!validate_view(view)) return false;
	return view->getRemovableContent();
}

EAPI int ui_view_get_degree(ui_view *view)
{
	if (!validate_view(view)) return -1;
	return view->getDegree();
}

EAPI ui_view_orientation_mode ui_view_get_orientation_mode(ui_view *view)
{
	if (!validate_view(view)) return UI_VIEW_ORIENTATION_MODE_UNKOWN;
	return view->getOrientationMode();
}

EAPI bool ui_view_set_available_rotations(ui_view *view, const int *rotations, unsigned int count)
{
	if (!validate_view(view)) return false;
	return view->setAvailableRotations(rotations, count);
}

EAPI const int *ui_view_get_available_rotations(ui_view *view, unsigned int *count)
{
	if (!validate_view(view)) return false;
	return view->getAvailableRotations(count);
}

EAPI bool ui_view_set_transition_style(ui_view *view, const char *style)
{
	if (!validate_view(view)) return false;
	return view->setTransitionStyle(style);
}

EAPI const char *ui_view_get_transition_style(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->getTransitionStyle();
}

EAPI const ui_menu *ui_view_get_menu(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->getMenu();
}

EAPI const char *ui_view_get_name(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->getName();
}

EAPI ui_view_state ui_view_get_state(ui_view *view)
{
	if (!validate_view(view)) return UI_VIEW_STATE_UNKNOWN;
	return view->getState();
}

EAPI Evas_Object *ui_view_get_content(ui_view *view)
{
	if (!validate_view(view)) return NULL;
	return view->getContent();
}

EAPI bool ui_view_destroy(ui_view *view)
{
	if (!validate_view(view)) return false;
	delete (view);
	return true;
}

EAPI bool ui_view_set_content(ui_view *view, Evas_Object *content)
{
	if (!validate_view(view)) return false;
	return view->setContent(content);
}

EAPI const char *ui_view_get_type(ui_view *view)
{
	if (!validate_view(view)) return false;
	return dynamic_cast<ui_common_view_capi *>(view)->type;
}
