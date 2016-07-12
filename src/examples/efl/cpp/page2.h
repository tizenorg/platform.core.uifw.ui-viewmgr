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

/** This example create a simple view which is inheritance UiStandardView.
 *  And add two buttons in view title area. then push in viewmgr.
 */
class page2: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();

		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Title Buttons",
		//Prev Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
			        UI_VIEWMGR->popView();
		        },
		        //Next Button Callback
		        [](void *data, Evas_Object *obj, void *event_info) -> void
		        {
		      	  UI_VIEWMGR->pushView(new page3());
		        });

		//Title left button
		Elm_Button *leftTitleBtn = elm_button_add(this->getBase());
		elm_object_text_set(leftTitleBtn, "Cancel");

		//Title right button
		Elm_Button *rightTitleBtn = elm_button_add(this->getBase());
		elm_object_text_set(rightTitleBtn, "Done");

		//Set available rotation only "0, 90" of this view
		const int rots[2] = { 0, 90 };
		this->setAvailableRotations(rots, 2);

		//Arguments: content, title, subtitle, title left button, title right button
		this->setContent(content, "Page2", NULL, leftTitleBtn, rightTitleBtn);
	}

public:
	page2() : UiStandardView("page2") {}
	~page2() {}
};
