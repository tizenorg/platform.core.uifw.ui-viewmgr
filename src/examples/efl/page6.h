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
class page6: public ui_basic_controller
{
private:
	appdata_s *ad;

public:
	page6(appdata_s *ad)
		: ad(ad)
	{
		/* ui_basic_view(controller, identity name).
		   Later, you could get the identity name using view->get_name(); */
		ad->viewmgr->push_view(new ui_basic_view(this, "page6"));
	}

	~page6()
	{
	}

	void load()
	{

		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(this->get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 6<br>With Toolbar<br>(tabbar style)",
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
					create_page7(ad);
				},
				this->ad);

		//Arguments: content, title
		view->set_content(content, "Title with toolbar");
		Evas_Object *toolbar = create_toolbar(view->get_base(), "toolbar_with_title");
		view->set_toolbar(toolbar);
	}
};

void create_page6(appdata_s *ad)
{
	new page6(ad);
}
