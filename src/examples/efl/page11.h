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

/** This page inherit ui_controller
 *  And implement on_rotate() method to create portarit, landscape content.
 *  This page will be created suitable content in on_rotate() method.
 */
class page11: public ui_controller
{
protected:
	void on_load()
	{
		ui_view *view = dynamic_cast<ui_view *>(this->get_view());
		this->on_rotate(view->get_degree());
	}

	void on_rotate(int degree)
	{
		ui_view *view = dynamic_cast<ui_view *>(this->get_view());

		//Portrait
		if (view->get_degree() == 0 || view->get_degree() == 180)
		{
			Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 11<br>(Rotate)",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pop_view();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						create_page12();
					});
			view->set_content(content, "Title");
			view->set_indicator(UI_VIEW_INDICATOR_DEFAULT);
		}
		//Landscape
		else
		{
			Evas_Object *content = create_landscape_content(view->get_base(), "ViewMgr Demo<br>Page 11<br>(Rotate)",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pop_view();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						create_page12();
					});
			view->set_content(content, "Title");
			view->set_indicator(UI_VIEW_INDICATOR_OPTIMAL);
		}
	}
public:
	page11()
	{
		UI_VIEWMGR->push_view(new ui_view(this, "page11"));
	}
	~page11() {}
};

void create_page11()
{
	//page 11 controller
	page11 *controller = new page11();
}
