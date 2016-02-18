class page2_controller: public ui_controller
{
private:
	appdata_s *ad;

public:
	page2_controller(appdata_s *ad)
			: ad(ad)
	{
		ad->viewmgr->push_view(new ui_basic_view(this, "page2"));
	}
	~page2_controller()
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
			        page3_controller *controller = new page3_controller(ad);
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
