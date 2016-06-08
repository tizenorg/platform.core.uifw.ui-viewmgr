#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_view.h"

using namespace efl_viewmanager;

///////////////////////////////////////////////////////////////////////////
////////////////////////// ui_standard_view_capi //////////////////////////
///////////////////////////////////////////////////////////////////////////

class ui_standard_view_capi : public ui_standard_view
{
private:
	ui_view_lifecycle_callback_s lifecycle_callback;
	ui_view_event_callback_s event_callback;
	void *lifecycle_data;
	void *event_data;

protected:
	void on_load()
	{
		ui_standard_view::on_load();

		if (this->lifecycle_callback.load) {
			this->lifecycle_callback.load(this, this->lifecycle_data);
		}
	}

	void on_portrait()
	{
		if (this->event_callback.portrait) {
			this->event_callback.portrait(this, this->event_data);
		}
	}

	void on_landscape()
	{
		if (this->event_callback.landscape) {
			this->event_callback.landscape(this, this->event_data);
		}
	}

	void on_rotate(int degree)
	{
		if (this->event_callback.rotate) {
			this->event_callback.rotate(this, degree,this->event_data);
		}
	}

	void on_menu(ui_menu *menu)
	{
		if (this->event_callback.menu) {
			this->event_callback.menu(menu, this->event_data);
		}
	}

public:
	ui_standard_view_capi(const char *name)
		: ui_standard_view(name)
	{
		this->lifecycle_callback = {0,};
		this->event_callback = {0,};
		this->lifecycle_data = NULL;
		this->event_data = NULL;
	}

	~ui_standard_view_capi()
	{
	}

	void set_lifecycle_callback(ui_view_lifecycle_callback_s *callback)
	{
		this->lifecycle_callback = *callback;
	}

	void set_lifecycle_data(void *data)
	{
		this->lifecycle_data = data;
	}

	void set_event_callback(ui_view_event_callback_s *callback)
	{
		this->event_callback = *callback;
	}

	void set_event_data(void *data)
	{
		this->event_data = data;
	}
};

///////////////////////////////////////////////////////////////////////////
//////////////////////////// ui_viwe_capi /////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class ui_view_capi : public ui_view
{
private:
	ui_view_lifecycle_callback_s lifecycle_callback;
	ui_view_event_callback_s event_callback;
	void *lifecycle_data;
	void *event_data;


protected:
	void on_load()
	{
		ui_view::on_load();

		if (this->lifecycle_callback.load) {
			this->lifecycle_callback.load(this, this->lifecycle_data);
		}
	}

	void on_portrait()
	{
		if (this->event_callback.portrait) {
			this->event_callback.portrait(this, this->event_data);
		}
	}

	void on_landscape()
	{
		if (this->event_callback.landscape) {
			this->event_callback.landscape(this, this->event_data);
		}
	}

	void on_rotate(int degree)
	{
		if (this->event_callback.rotate) {
			this->event_callback.rotate(this, degree,this->event_data);
		}
	}

	void on_menu(ui_menu *menu)
	{
		ui_view::on_menu(menu);

		if (this->event_callback.menu) {
			this->event_callback.menu(menu, this->event_data);
		}
	}

public:
	ui_view_capi(const char *name)
		: ui_view(name)
	{
		this->lifecycle_callback = {0,};
		this->event_callback = {0,};
		this->lifecycle_data = NULL;
		this->event_data = NULL;
	}

	~ui_view_capi()
	{
	}

	void set_lifecycle_callback(ui_view_lifecycle_callback_s *callback)
	{
		this->lifecycle_callback = *callback;
	}

	void set_lifecycle_data(void *data)
	{
		this->lifecycle_data = data;
	}

	void set_event_callback(ui_view_event_callback_s *callback)
	{
		this->event_callback = *callback;
	}

	void set_event_data(void *data)
	{
		this->event_data = data;
	}
};

extern "C" {
//================================== view common APIs ========================================

bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		//FIXME: Maybe... There is a more nice way for it...
		ui_standard_view_capi *capi_standard_view = dynamic_cast<ui_standard_view_capi *>(view);
		if (capi_standard_view)
		{
			if (lifecycle_callback) capi_standard_view->set_lifecycle_callback(lifecycle_callback);
			if (data) capi_standard_view->set_lifecycle_data(data);
		}
		else
		{
			ui_view_capi *capi_view = dynamic_cast<ui_view_capi *>(view);

			if (lifecycle_callback) capi_view->set_lifecycle_callback(lifecycle_callback);
			if (data) capi_view->set_lifecycle_data(data);
		}

		return true;
	}

	bool ui_view_event_callbacks_set(ui_view *view,
		                             ui_view_event_callback_s *event_callback, void *data)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		//FIXME: Maybe... There is a more nice way for it...
		ui_standard_view_capi *capi_standard_view = dynamic_cast<ui_standard_view_capi *>(view);
		if (capi_standard_view)
		{
			if (event_callback) capi_standard_view->set_event_callback(event_callback);
			if (data) capi_standard_view->set_event_data(data);
		}
		else
		{
			ui_view_capi *capi_view = dynamic_cast<ui_view_capi *>(view);

			if (event_callback) capi_view->set_event_callback(event_callback);
			if (data) capi_view->set_event_data(data);
		}

		return true;
	}

	Evas_Object* ui_view_base_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_standard_view = dynamic_cast<ui_standard_view_capi *>(view);
		if (capi_standard_view)
			return capi_standard_view->get_base();
		else
		{
			ui_view_capi *capi_view = dynamic_cast<ui_view_capi *>(view);

			return capi_view->get_base();
		}
	}

	Evas_Object *ui_view_content_unset(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_standard_view = dynamic_cast<ui_standard_view_capi *>(view);
		if (capi_standard_view)
			return capi_standard_view->unset_content();
		else
		{
			ui_view_capi *capi_view = dynamic_cast<ui_view_capi *>(view);

			return capi_view->unset_content();
		}
	}

	void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return;
		}

		return view->set_indicator(indicator);
	}

	ui_view_indicator ui_view_indicator_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return UI_VIEW_INDICATOR_LAST;
		}

		return view->get_indicator();
	}

	void ui_view_removable_content_set(ui_view *view, bool remove)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return;
		}

		view->set_removable_content(remove);
	}

	bool ui_view_removable_content_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		return view->get_removable_content();
	}

	int  ui_view_degree_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return -1;
		}

		return view->get_degree();
	}

	bool ui_view_transition_style_set(ui_view *view, const char *style)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		return view->set_transition_style(style);
	}

	const char *ui_view_transition_style_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		return view->get_transition_style();
	}

	const ui_menu *ui_view_menu_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		return view->get_menu();
	}

	bool ui_view_name_set(ui_view *view, const char *name)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		return view->set_name(name);

	}

	const char *ui_view_name_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		return view->get_name();

	}

	ui_view_state ui_view_state_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return UI_VIEW_STATE_LAST;
		}

		return view->get_state();
	}

	Evas_Object *ui_view_content_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		return view->get_content();

	}

//================================ ui_standard view APIs =====================================

	ui_view* ui_standard_view_create(const char *name)
	{
		return new ui_standard_view_capi(name);
	}

	bool ui_standard_view_content_set(ui_view *view, Evas_Object *content,
									  const char *title, const char *subtitle,
									  Evas_Object *title_left_btn, Evas_Object *title_right_btn)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_content(content, title, subtitle, title_left_btn, title_right_btn);
	}


	bool ui_standard_view_title_set(ui_view *view, const char *text)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_title(text);
	}

	bool ui_standard_view_sub_title_set(ui_view *view, const char *text)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_subtitle(text);
	}

	bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_title_badge(badge_text);
	}

	bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_title_right_btn(title_right_btn);
	}

	Elm_Button *ui_standard_view_title_right_btn_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->get_title_right_btn();
	}

	Elm_Button *ui_standard_view_title_right_btn_unset(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->unset_title_right_btn();
	}

	bool ui_standard_view_title_left_btn_set(ui_view *view, Evas_Object *title_left_btn)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_title_left_btn(title_left_btn);
	}

	Elm_Button *ui_standard_view_title_left_btn_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->get_title_left_btn();
	}

	Elm_Button *ui_standard_view_title_left_btn_unset(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->unset_title_right_btn();
	}


	bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_toolbar(toolbar);
	}

	Elm_Toolbar *ui_standard_view_toolbar_get(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->get_toolbar();
	}

	Elm_Toolbar *ui_standard_view_toolbar_unset(ui_view *view)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return NULL;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->unset_toolbar();
	}

	bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return -1;
		}

		ui_standard_view_capi *capi_view = static_cast<ui_standard_view_capi *>(view);

		return capi_view->set_title_visible(visible, anim);
	}

//==================================== ui_view APIs ==========================================

	ui_view* ui_view_create(const char *name)
	{
		return new ui_view_capi(name);
	}

	bool ui_view_content_set(ui_view *view, Evas_Object *content)
	{
		if (!view)
		{
			LOGE("Invalid View");
			return false;
		}

		ui_view_capi *capi_view = static_cast<ui_view_capi *>(view);

		return capi_view->set_content(content);
	}
}
