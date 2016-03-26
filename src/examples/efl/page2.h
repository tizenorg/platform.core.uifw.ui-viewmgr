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

/** A example for view class extension.
 *  This example will be created content in view load time.
 *  And add two buttons in left, right side of title area.
 */
class page2: public ui_view
{
private:
	appdata_s *ad;

protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 2",
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
					create_page3(ad);
				},
				this->ad);

		//Title left button
		Elm_Button *left_title_btn = elm_button_add(this->get_base());
		elm_object_text_set(left_title_btn, "Cancel");

		//Title right button
		Elm_Button *right_title_btn = elm_button_add(this->get_base());
		elm_object_text_set(right_title_btn, "Done");

		//Arguments: content, title, subtitle, title left button, title right button
		this->set_content(content, "Title Buttons", NULL, left_title_btn, right_title_btn);
	}

public:
	page2(appdata_s *ad) : ui_view("page2"), ad(ad)
	{
		//Push this view in viewmgr.
		ad->viewmgr->push_view(this);
	}

	~page2()
	{
	}
};

void create_page2(appdata_s *ad)
{
	new page2(ad);
}
