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

	Evas_Object *create_page10_content(ui_view *view, bool is_portrait)
	{
		Evas_Object *content;

		if (is_portrait)
		{
			//Create portrait content.
			content = create_content(view->get_base(),
					"ViewMgr Demo<br>Page 10 With<br>on_portrait(), on_landscape()",
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
		}
		else
		{
			//Create landscape content.
			content = create_landscape_content(view->get_base(),
					"ViewMgr Demo<br>Page 10 With<br>on_portrait(), on_landscape()",
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
		}

		return content;
	}

	void on_load()
	{
		Evas_Object *content;

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
		Evas_Object *content;

		ui_view *view = dynamic_cast<ui_view *>(this->get_view());

		content = this->create_page10_content(view, true);
		view->set_content(content, "Title Portrait");
	}

	void on_landscape()
	{
		Evas_Object *content;

		ui_view *view = dynamic_cast<ui_view *>(this->get_view());

		content = this->create_page10_content(view, false);
		view->set_content(content, "Title Landscape");
	}

};

void create_page10(appdata_s *ad)
{
	new page10(ad);
}
