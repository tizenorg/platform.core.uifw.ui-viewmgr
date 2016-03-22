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
class page1: public ui_basic_controller
{
private:
	appdata_s *ad;

public:
	page1(appdata_s *ad)
			: ad(ad)
	{
		/* ui_basic_view(controller, identity name).
		   Later, you could get the identity name using view->get_name(); */
		ad->viewmgr->push_view(new ui_basic_view(this, "page1"));
	}
	~page1()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_basic_view *view = dynamic_cast<ui_basic_view *>(this->get_view());

		printf("view 1 load rot = %d\n", view->get_degree());
		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 1",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					ad->viewmgr->deactivate();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					create_page2(ad);
				},
				this->ad);

		view->set_content(content, "Title");
	}

	bool menu()
	{
		LOGE("Menu!");
		return true;
	}

	void rotated(int degree)
	{
		LOGE("Current view's degree is %d\n", degree);
	}

	void portrait()
	{
		LOGE("View is on portrait mode\n");
	}

	void landscape()
	{
		LOGE("View is on landscape mode\n");
	}
};

void create_page1(appdata_s *ad)
{
	new page1(ad);
}
