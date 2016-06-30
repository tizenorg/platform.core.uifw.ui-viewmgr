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
 *  This create a content that has same size of screen.
 *  When this view has rotated viewmgr's internal scroller will be enabled automatically.
 */
class page15: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();

		//Create a main content.
		Evas_Object *content = createScrollingContent(this->getBase());

		this->setContent(content, "Page15 Scroller In Viewmgr");

		//Title Right button
		Elm_Button *rightBtn = elm_button_add(this->getBase());
		elm_object_text_set(rightBtn, "Next");
		evas_object_smart_callback_add(rightBtn, "clicked",
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page16());
				},
				this);

		this->setTitleRightBtn(rightBtn);
	}

public:
	page15() : UiStandardView("page15") {}
	~page15(){}
};
