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

/** This page shows how to create a view content in advance.
 */
class page8: public UiStandardView
{
public:
	page8() : UiStandardView("page8")
	{
		//Create a main content.
		Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Content Preloading",
			//Prev Button Callback
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UI_VIEWMGR->popView();
			},
			//Next Button Callback
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UI_VIEWMGR->pushView(new page9());
			});

		//Set title text, content
		this->setTitle("Page8");
		this->setContent(content);

		//Don't delete view's content when this view popped.
		//This is a show case for saving this content for reuse later.
		this->setRemovableContent(false);
	}
	~page8() {}
};
