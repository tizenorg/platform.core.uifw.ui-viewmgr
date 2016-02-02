#include <dlog.h>
#include "ui_view.h"
#include "ui_viewmgr.h"

using namespace efl;

void
win_delete_request_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_viewmgr *viewmgr = static_cast<ui_viewmgr*>(data);
   delete(viewmgr);
}

Evas_Object *
ui_viewmgr :: create_conformant(Evas_Object *win)
{
	Evas_Object *conform = elm_conformant_add(win);
	if (!conform) return NULL;

	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	elm_win_conformant_set(win, EINA_TRUE);
	evas_object_show(conform);

	return conform;
}

ui_viewmgr :: ui_viewmgr(const char *pkg) : ui_viewmgr_base()
{
	if (!pkg)
	{
		LOGE("Invalid package name");
		return;
	}
	//Window
	this->win = elm_win_util_standard_add(pkg, pkg);

	if (!this->win) {
		LOGE("Failed to create a window (%s)", pkg);
		return;
	}

	//Set window rotation
	if (elm_win_wm_rotation_supported_get(this->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(this->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(this->win, "delete,request", win_delete_request_cb, this);

	//Conformant: Make this configurable.
	this->conform = create_conformant(this->win);

	if (!this->conform) {
		LOGE("Failed to create a conformant (%s)", pkg);
		return;
	}

	//Set Indicator properties
	elm_win_indicator_mode_set(this->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(this->win, ELM_WIN_INDICATOR_TRANSPARENT);

	elm_win_autodel_set(this->win, EINA_TRUE);
}

ui_viewmgr :: ~ui_viewmgr()
{
}

bool
ui_viewmgr :: activate()
{
	evas_object_show(this->win);
	return true;
}

bool
ui_viewmgr :: deactivate()
{
    evas_object_lower(this->win);
	return true;
}

ui_view *
ui_viewmgr :: push_view(ui_view *view)
{
	ui_viewmgr_base :: push_view(view);
/*
	this->to_show = true;
	if (!this->animation_job)
		this->animation_job = ecore_job_add(_animation_cb, this);
*/
	return view;
}
