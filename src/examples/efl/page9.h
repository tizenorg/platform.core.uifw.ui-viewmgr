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

/** This page inherit ui_controller to show view create in controller side.
 *  And this page create content in controller constructor time.
 */
class page9: public ui_controller
{
public:
	page9()
	{
		ui_view *view = new ui_view(this, "page9");

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 9<br>(Controller Inheritance + Content Preloading)",
			//Prev Button Callback
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UI_VIEWMGR->pop_view();
			},
			//Next Button Callback
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				create_page10();
			});

		//Don't delete view's content when this view poped.
		view->set_removable_content(false);
		view->set_content(content, "Title");

		UI_VIEWMGR->push_view(view);
	}
	~page9() {}
};

void create_page9()
{
	page9 *controller = new page9();
}
