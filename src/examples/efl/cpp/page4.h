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
 *  And set long text to title, set badge text in view title area.
 *  Then push in viewmgr.
 */
class page4: public UiStandardView
{
protected:
	void on_load()
	{
		UiStandardView::on_load();

		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr++ Demo<br>Title Badge",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->push_view(new page5());
				});

		//Arguments: content, title
		this->set_content(content, "Page4. We put a long title here intentionally");
		this->set_title_badge("999+");
	}

public:
	page4() : UiStandardView("page4") {}
	~page4() {}
};
