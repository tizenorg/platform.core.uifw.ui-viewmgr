/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
class page10: public ui_controller
{
private:
	appdata_s *ad;

public:
	page10(appdata_s *ad)
		: ad(ad)
	{
		/* ui_view(controller, identity name).
		   Later, you could get the identity name using view->get_name(); */
		ad->viewmgr->push_view(new ui_view(this, "page10"));
	}

	~page10()
	{
	}

	void on_load()
	{
		//Initialize contents.
		ui_view *view = dynamic_cast<ui_view *>(this->get_view());

		//FIXME: Change below code to more convenient and clear way.
		if (view->get_degree() == 90 || view->get_degree() == 270)
			this->on_landscape();
		else
			this->on_portrait();
	}

	void on_portrait()
	{
		ui_view *view = dynamic_cast<ui_view *>(this->get_view());
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 10<br>(Portrait + Landscape)",
								//Prev Button Callback
						        [](void *data, Evas_Object *obj, void *event_info) -> void
						        {
							        appdata_s *ad = static_cast<appdata_s *>(data);
							        ad->viewmgr->pop_view();
						        },
						        //Next Button Callback
						        [](void *data, Evas_Object *obj, void *event_info) -> void
						        {
							        appdata_s *ad = static_cast<appdata_s *>(data);
							        create_page11(ad);
						        },
						        this->ad);
		view->set_content(content, "Title");
		view->set_indicator(UI_VIEW_INDICATOR_DEFAULT);
	}

	void on_landscape()
	{
		ui_view *view = dynamic_cast<ui_view *>(this->get_view());
		Evas_Object *content = create_landscape_content(view->get_base(), "ViewMgr Demo<br>Page 10<br>(Portrait + Landscape)",
				//Prev Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        ad->viewmgr->pop_view();
		        },
		        //Next Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        appdata_s *ad = static_cast<appdata_s *>(data);
			        create_page11(ad);
		        },
		        this->ad);
		view->set_content(content, "Title");
		view->set_indicator(UI_VIEW_INDICATOR_OPTIMAL);
	}

};

void create_page10(appdata_s *ad)
{
	new page10(ad);
}
