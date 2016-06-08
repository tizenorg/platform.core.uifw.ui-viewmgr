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


/** This page implement on_menu() method to create ctxpopup when menu HW key clicked.
 *  This page will be created menu(ctxpopup)items in on_menu() method.
 */
static void ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = static_cast<Elm_Object_Item *>(event_info);
	elm_ctxpopup_dismiss(obj);
	LOGE("Item (%s) is selected", elm_object_item_text_get(it));
}

class page11: public ui_standard_view
{
protected:
	void on_load()
	{
		ui_standard_view::on_load();

		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Menu Popup",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->push_view(new page12());
				});

		this->set_content(content, "Page11");
	}

	void on_menu(ui_menu *menu)
	{
		//FIXME: Is it needed?
		ui_standard_view::on_menu(menu);

		Elm_Ctxpopup *ctxpopup = elm_ctxpopup_add(menu->get_base());
		elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, this);
		elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, this);

		menu->set_content(ctxpopup);
	}

public:
	page11() {}
	~page11() {}
};
