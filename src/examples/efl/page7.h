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
 *  And this page make a content in page constructor time.
 */
class page7: public ui_view
{
protected:
	void on_load()
	{
		ui_view::on_load();

		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Navigationbar",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					create_page8();
				});

		//FIXME: Don't delete view's content when this view poped.
		this->set_removable_content(false);
		this->set_content(content, "Page7");
		Elm_Toolbar *toolbar = create_toolbar(this->get_base(), "navigationbar");
		this->set_toolbar(toolbar);
	}
public:
	page7() : ui_view("page7") {}
	~page7() {}
};

void create_page7()
{
	//Push this view in viewmgr.
	UI_VIEWMGR->push_view(new page7());
}
