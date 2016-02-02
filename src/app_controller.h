#include "ui_controller.h"


static Evas_Object*
create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb, appdata_s *ad)
{
	Evas_Object *grid, *box, *layout, *scroller, *btn, *button_layout;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* Grid */
	grid = elm_grid_add(scroller);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", text);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Previous Page Button */
	btn = elm_button_add(grid);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_grid_pack(grid, btn, 10, 90, 30, 8);

	/* Next Page Button */
	btn = elm_button_add(grid);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_grid_pack(grid, btn, 60, 90, 30, 8);

	elm_object_content_set(scroller, grid);

	return scroller;
}





class app_controller4: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{

		appdata_s *ad = static_cast<appdata_s *>(data);

	}

public:
	app_controller4(appdata_s *ad) :
			ad(ad), content(NULL)
	{
	}

	~app_controller4()
	{
		LOGE("controller 4");
	}

	void load()
	{
		LOGE("view 4 button create");
		ui_view *view = this->get_view();
		Evas_Object *btn = elm_button_add(view->get_base());
		elm_object_text_set(btn, "Page 4");
		view->set_content(btn);

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);

		this->content = btn;
	}

	void unload()
	{
		LOGE("controller4");
		evas_object_del(this->content);
		ui_view *view = this->get_view();
		view->set_content(NULL);
	}

	void active()
	{
		LOGE("controller4");
	}

	void inactive()
	{
		LOGE("controller4");
	}

	void destroy()
	{
		LOGE("controller4");
	}
};

class app_controller3: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{

		appdata_s *ad = static_cast<appdata_s *>(data);

		//View 4

		app_controller4 *controller = new app_controller4(ad);
		ad->viewmgr->push_view(new ui_basic_view(controller));

	}

public:
	app_controller3(appdata_s *ad) :
			ad(ad), content(NULL)
	{
	}

	~app_controller3()
	{
		LOGE("controller 3");
	}

	void load()
	{
		ui_view *view = this->get_view();
		Evas_Object *btn = elm_button_add(view->get_base());
		elm_object_text_set(btn, "Page 3");
		view->set_content(btn);

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);

		this->content = btn;
	}

	void unload()
	{
		LOGE("controller3");
		evas_object_del(this->content);
		ui_view *view = this->get_view();
		view->set_content(NULL);
	}

	void active()
	{
		LOGE("controller3");
	}

	void inactive()
	{
		LOGE("controller3");
	}

	void destroy()
	{
		LOGE("controller3");
	}
};

class app_controller2: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void next_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		//View 2
		app_controller2 *controller = new app_controller2(ad);
		ad->viewmgr->push_view(new ui_basic_view(controller));
	}
	static void prev_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		ad->viewmgr->deactivate();
	}

public:
	app_controller2(appdata_s *ad) :
			ad(ad), content(NULL)
	{
	}

	~app_controller2()
	{
	}

	void load()
	{
		ui_basic_view *view = dynamic_cast<ui_basic_view *>(ui_controller::get_view());
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 2", prev_clicked_cb, next_clicked_cb, this->ad);

		Evas_Object *left_title_btn = elm_button_add(view->get_base());
		elm_object_text_set(left_title_btn, "Cancel");

		Evas_Object *right_title_btn = elm_button_add(view->get_base());
		elm_object_text_set(right_title_btn, "Done");

		view->set_content(content, "Title Buttons", NULL, left_title_btn, right_title_btn);
		this->content = content;
	}

	void unload()
	{
		evas_object_del(this->content);
		ui_view *view = this->get_view();
		view->set_content(NULL);
	}
};

class app_controller1: public ui_controller
{
private:
	appdata_s *ad;

	static void next_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		//View 2
		app_controller2 *controller = new app_controller2(ad);
		ad->viewmgr->push_view(new ui_basic_view(controller));
	}
	static void prev_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		ad->viewmgr->deactivate();
	}

public:
	app_controller1(appdata_s *ad) :
			ad(ad)
	{
	}

	~app_controller1()
	{
	}

	void load()
	{
		ui_basic_view *view = dynamic_cast<ui_basic_view *>(ui_controller::get_view());
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 1", prev_clicked_cb, next_clicked_cb, this->ad);
		view->set_content(content, "Title");
	}

	void unload()
	{
		ui_view *view = ui_controller::get_view();
		Evas_Object *btn = view->set_content(NULL);
		evas_object_del(btn);
	}
};
