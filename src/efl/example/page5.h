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
class page5: public ui_controller
{
private:
	appdata_s *ad;

public:
	page5(appdata_s *ad)
			: ad(ad)
	{
		//No basic form.
		/* ui_view(controller, identity name).
		   Later, you could get the identity name using view->get_name(); */
		ui_view *view = ad->viewmgr->push_view(new ui_view(this, "page5"));
	}

	~page5()
	{
	}

	void load()
	{
		//Initialize contents.

		ui_view *view = dynamic_cast<ui_view *>(this->get_view());

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 5<br>(Full View)",
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
					ad->viewmgr->deactivate();
				},
				this->ad);

		view->set_content(content);
		view->set_indicator(UI_VIEW_INDICATOR_HIDE);
	}
};

void create_page5(appdata_s *ad)
{
	new page5(ad);
}
