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

/** This page inherit ui_view to show title with toolbar sample.
 */
class page6: public ui_view
{
private:
	appdata_s *ad;

protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 6",
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
		this->set_content(content, "Title with toolbar");
		Elm_Toolbar *toolbar = create_toolbar(this->get_base(), "toolbar_with_title");
		this->set_toolbar(toolbar);
	}

public:
	page6(appdata_s *ad) : ui_view("page6"), ad(ad)
	{
		ad->viewmgr->push_view(this);
	}

	~page6()
	{
	}
};

void create_page6(appdata_s *ad)
{
	/* A example for view class extension instead of using controller class. */
	new page6(ad);
}
