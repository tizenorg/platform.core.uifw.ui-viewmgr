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
 *  And make a button on right top side of title area to activate popup.
 *  The created popup has view and it will be managed by viewmgr.
 */

static void _popupDismissedCb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_smart_callback_del(obj, "dismissed", _popupDismissedCb);
	UiPopup *popup = static_cast<UiPopup *>(data);
	delete (popup);
}

class page12: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();

		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Popup",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page13());
				});

		//Title Right button
		Elm_Button *rightBtn = elm_button_add(this->getBase());
		elm_object_text_set(rightBtn, "popup");
		evas_object_smart_callback_add(rightBtn, "clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					page12 *view = static_cast<page12 *>(data);
					view->createPopup();
				},
				this);

		//Set title text, right button, content
		this->setTitle("Page12");
		this->setContent(content);
		this->setTitleRightBtn(rightBtn);
	}

public:

	page12() : UiStandardView("page12") {}
	~page12() {}

	void createPopup()
	{
		UiPopup *popup = new UiPopup(this);
		if (!popup) return;

		Elm_Popup *obj = elm_popup_add(popup->getBase());
		elm_object_text_set(obj, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
		elm_popup_timeout_set(obj, 3.0);
		evas_object_smart_callback_add(obj, "dismissed", _popupDismissedCb, popup);
		evas_object_smart_callback_add(obj, "block,clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					elm_popup_dismiss(obj);
				},
				NULL);
		evas_object_smart_callback_add(obj, "timeout",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					elm_popup_dismiss(obj);
				},
				NULL);

		popup->setContent(obj);
		popup->activate();
	}
};
