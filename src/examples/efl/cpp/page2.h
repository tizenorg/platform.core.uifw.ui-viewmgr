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

/** This example create a simple view which is inheritance ui_standard_view.
 *  And add two buttons in view title area. then push in viewmgr.
 */
class page2: public ui_standard_view
{
protected:
	void on_load()
	{
		ui_standard_view::on_load();

		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Title Buttons",
		//Prev Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        UI_VIEWMGR->pop_view();
		        },
		        //Next Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
		        	UI_VIEWMGR->push_view(new page3());
		        });

		//Title left button
		Elm_Button *left_title_btn = elm_button_add(this->get_base());
		elm_object_text_set(left_title_btn, "Cancel");

		//Title right button
		Elm_Button *right_title_btn = elm_button_add(this->get_base());
		elm_object_text_set(right_title_btn, "Done");

		//Arguments: content, title, subtitle, title left button, title right button
		this->set_content(content, "Page2", NULL, left_title_btn, right_title_btn);
	}

public:
	page2() : ui_standard_view("page2") {}
	~page2() {}
};
