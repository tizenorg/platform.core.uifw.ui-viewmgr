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

static void popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	//FIXME: remove dismissed callback because this callback is called twice.
	//It seems this is an efl or popup error, not this ui_popup nor example.
	evas_object_smart_callback_del(obj, "dismissed", popup_dismissed_cb);
	ui_base_popup *overlay = static_cast<ui_base_popup *>(data);
	delete (overlay);
}

class page12: public ui_view
{
protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Popup",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					create_page13();
				});

		this->set_content(content, "Page12");

		//Title Right button
		Elm_Button *right_btn = elm_button_add(this->get_base());
		elm_object_text_set(right_btn, "popup");
		evas_object_smart_callback_add(right_btn, "clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					page12 *view = static_cast<page12 *>(data);
					view->create_popup();
				},
				this);
		this->set_title_right_btn(right_btn);
	}

public:
	page12() : ui_view("page12") {}
	~page12() {}

	void create_popup()
	{
		//FIXME: is overlay a proper name?
		ui_base_popup *overlay = new ui_base_popup(this);

		Elm_Popup *popup = elm_popup_add(overlay->get_base());
		elm_object_text_set(popup, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
		elm_popup_timeout_set(popup, 3.0);
		evas_object_smart_callback_add(popup, "dismissed", popup_dismissed_cb, overlay);
		evas_object_smart_callback_add(popup, "block,clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					elm_popup_dismiss(obj);
				},
				NULL);
		evas_object_smart_callback_add(popup, "timeout",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					elm_popup_dismiss(obj);
				},
				NULL);
		overlay->set_content(popup);
		overlay->activate();
	}
};

void create_page12()
{
	//Push this view in viewmgr.
	UI_VIEWMGR->push_view(new page12());
}
