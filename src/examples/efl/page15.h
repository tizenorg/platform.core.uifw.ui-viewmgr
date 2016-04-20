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

/** This example create a simple view which is inheritance ui_view.
 *  Then push in viewmgr.
 */
class page15: public ui_view
{
protected:
	void on_load()
	{
		ui_view::on_load();

		//Create a main content.
		Evas_Object *content = create_scrolling_content(this->get_base());

		this->set_content(content, "Page15 Scroller In Viewmgr");

		//Title Right button
		Elm_Button *right_btn = elm_button_add(this->get_base());
		elm_object_text_set(right_btn, "Next");
		evas_object_smart_callback_add(right_btn, "clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					create_page16();
				},
				this);
		this->set_title_right_btn(right_btn);
	}
};

void create_page15()
{
	//Push this view in viewmgr.
	UI_VIEWMGR->push_view(new page15());
}
