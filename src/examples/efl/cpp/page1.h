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

/** This example create a simple view which is inheritance of an UiStandardView.
 *  Then push in viewmgr.
 */
class page1: public UiStandardView
{
protected:
	//on_load() will be called when this page1 is requested to be shown.
	void onLoad()
	{
		UiStandardView::onLoad();

		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Basic View",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page2());
				});

		//Set title text, content
		this->setTitle("Page1");
		this->setContent(content);
	}

public:
	page1() : UiStandardView("page1") {}
	~page1() {}
};
