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

/** This page inherit UiStandardView
 *  This view create a lot of buttons to show how to handle title area visible state with animation or no effect.
 */
class page16: public UiStandardView
{
protected:
	void on_load()
	{
		UiStandardView::on_load();

		//Create a main content.
		Evas_Object *content = create_title_handle_content(this->get_base(),
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->deactivate();
				},
				//Title Show Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UiStandardView *view = static_cast<UiStandardView *>(data);
					view->set_title_visible(true, false);
				},
				//Title Hide Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UiStandardView *view = static_cast<UiStandardView *>(data);
					view->set_title_visible(false, false);
				},
				//Title Show Anim Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UiStandardView *view = static_cast<UiStandardView *>(data);
					view->set_title_visible(true, true);
				},
				//Title Hide Anim Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UiStandardView *view = static_cast<UiStandardView *>(data);
					view->set_title_visible(false, true);
				}, this);

		this->set_content(content, "Page16");
	}

public:
	page16() : UiStandardView("page16") {}
	~page16() {}
};
