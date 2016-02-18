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

public:
	app_controller4(appdata_s *ad)
			: ad(ad)
	{
	}

	~app_controller4()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(this->get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 4",
				//Prev Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->pop_view();
		        },
		        //Next Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->deactivate();
		        }, this->ad);

		//Arguments: content, title
		view->set_content(content, "TitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitle");
		view->set_title_badge("999+");
	}

	void unload()
	{
		//You could destroy the content here for save memory.
		ui_view *view = this->get_view();
		Evas_Object *content = view->set_content(NULL);
		evas_object_del(content);
	}

};


class app_controller3: public ui_controller
{
private:
	appdata_s *ad;

public:
	app_controller3(appdata_s *ad)
			: ad(ad)
	{
	}

	~app_controller3()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(this->get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 3",
				//Prev Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->pop_view();
		        },
		        //Next Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        app_controller4 *controller = new app_controller4(ad);
			        ad->viewmgr->push_view(new ui_basic_view(controller));
		        }, this->ad);

		//Arguments: content, title, subtitle, icon, title left button, title right button
		view->set_content(content, "Title", "Subtitle", NULL, NULL, NULL);
	}

	void unload()
	{
		//You could destroy the content here for save memory.
		ui_view *view = this->get_view();
		Evas_Object *content = view->set_content(NULL);
		evas_object_del(content);
	}
};


class app_controller2: public ui_controller
{
private:
	appdata_s *ad;

public:
	app_controller2(appdata_s *ad)
			: ad(ad)
	{
	}
	~app_controller2()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(ui_controller::get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 2",
				//Prev Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->pop_view();
		        },
		        //Next Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        app_controller3 *controller = new app_controller3(ad);
			        ad->viewmgr->push_view(new ui_basic_view(controller));
		        }, this->ad);

		//Title left button
		Evas_Object *left_title_btn = elm_button_add(view->get_base());
		elm_object_text_set(left_title_btn, "Cancel");

		//Title right button
		Evas_Object *right_title_btn = elm_button_add(view->get_base());
		elm_object_text_set(right_title_btn, "Done");

		//Arguments: content, title, subtitle, icon, title left button, title right button
		view->set_content(content, "Title Buttons", NULL, NULL, left_title_btn, right_title_btn);
	}

	void unload()
	{
		//You could destroy the content here for save memory.
		ui_view *view = this->get_view();
		Evas_Object *content = view->set_content(NULL);
		evas_object_del(content);
	}
};

class app_controller1: public ui_controller
{
private:
	appdata_s *ad;

public:
	app_controller1(appdata_s *ad)
			: ad(ad)
	{
	}
	~app_controller1()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(ui_controller::get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 1",
				//Prev Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->deactivate();
		        },
		        //Next Button
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        app_controller2 *controller = new app_controller2(ad);
			        ui_basic_view *view = new ui_basic_view(controller, "page2");
			        ad->viewmgr->push_view(view);
		        }, this->ad);

		view->set_content(content, "Title");
	}

	void unload()
	{
		//You could destroy the content here for save memory.
		ui_view *view = this->get_view();
		Evas_Object *content = view->set_content(NULL);
		evas_object_del(content);
	}
};
