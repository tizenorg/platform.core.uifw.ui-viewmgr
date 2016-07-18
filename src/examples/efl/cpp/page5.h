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

/** This page inherit UiView to show how to create full view.
 *  And set indicator state as hide.
 */
class page5: public UiView
{
protected:
	void onLoad()
	{
		UiView::onLoad();

		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Full View",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page6());
				});

		//Set content, indicator property
		this->setContent(content);
		this->setIndicator(UI_VIEW_INDICATOR_HIDE);
	}

public:
	page5() : UiView("page5") {}
	~page5() {}
};
