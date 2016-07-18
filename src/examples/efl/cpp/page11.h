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
static void _ctxpopupItemSelectCb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = static_cast<Elm_Object_Item *>(event_info);
	LOGE("Item (%s) is selected", elm_object_item_text_get(it));
	elm_ctxpopup_dismiss(obj);
}

class page11: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();

		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Menu Popup",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page12());
				});

		//Set title text, content
		this->setTitle("Page11");
		this->setContent(content);
	}

	void onMenu(UiMenu *menu)
	{
		UiStandardView::onMenu(menu);

		Elm_Ctxpopup *ctxpopup = elm_ctxpopup_add(menu->getBase());
		elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Search", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Search", NULL, _ctxpopupItemSelectCb, this);
		elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, _ctxpopupItemSelectCb, this);

		menu->setContent(ctxpopup);
	}

public:
	page11() : UiStandardView("page11") {}
	~page11() {}
};
