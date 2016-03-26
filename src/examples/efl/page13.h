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

/** This page inherit ui_ui_view
 *  And make a button on right top side of title area to activate popup.
 *  The created popup has view and it will be managed by viewmgr.
 */
class page13: public ui_view
{
private:
	appdata_s *ad;

protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 13<br>(Popup)",
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
					create_page14(ad);
				},
				this->ad);
		this->set_content(content, "Title");

		//Title Right button
		Elm_Button *right_btn = elm_button_add(this->get_base());
		elm_object_text_set(right_btn, "popup");
		evas_object_smart_callback_add(right_btn, "clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					page13 *view = static_cast<page13 *>(data);
					view->create_popup();
				},
				this);
		this->set_title_right_btn(right_btn);
	}

public:
	page13(const char *name, appdata_s *ad)
			: ui_view(name), ad(ad)
	{
		ad->viewmgr->push_view(this);
	}

	~page13()
	{
	}

	void create_popup()
	{
		ui_popup *view = new ui_popup(this);

		Evas_Object *popup = elm_popup_add(view->get_base());

		elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
		elm_object_text_set(popup, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
		elm_popup_timeout_set(popup, 3.0);
		evas_object_smart_callback_add(popup, "block,clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					evas_object_del(obj);
				},
				NULL);
		evas_object_smart_callback_add(popup, "timeout",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					evas_object_del(obj);
				},
				NULL);
		evas_object_show(popup);

		view->set_content(popup);
		view->activate();
	}
};

void create_page13(appdata_s *ad)
{
	/* A example for view class extension instead of using controller class. */
	new page13("page13", ad);
}
