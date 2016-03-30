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

/** This page implements on_rotate() method to create portarit, landscape content.
 *  This page will be created suitable content in on_rotate() method.
 */
class page10: public ui_view
{
protected:
	void on_load()
	{
		this->on_rotate(this->get_degree());
	}

	void on_rotate(int degree)
	{
		//Portrait
		if (this->get_degree() == 0 || this->get_degree() == 180)
		{
			Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Rotation",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pop_view();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						create_page11();
					});
			this->set_content(content, "Page 10");
			this->set_indicator(UI_VIEW_INDICATOR_DEFAULT);
		}
		//Landscape
		else
		{
			Evas_Object *content = create_landscape_content(this->get_base(), "ViewMgr Demo<br>Rotation",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pop_view();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						create_page11();
					});
			this->set_content(content, "Page 10");
			this->set_indicator(UI_VIEW_INDICATOR_OPTIMAL);
		}
	}
public:
	page10() : ui_view("page10") {}
	~page10() {}
};

void create_page10()
{
	//Push this view in viewmgr.
	UI_VIEWMGR->push_view(new page10());
}
