class page3_controller: public ui_controller
{
private:
	appdata_s *ad;

public:
	page3_controller(appdata_s *ad)
			: ad(ad)
	{
		ad->viewmgr->push_view(new ui_basic_view(this, "page3"));
	}

	~page3_controller()
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
			        page4_controller *controller = new page4_controller(ad);
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
