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

/** This page implements on_rotate() method to create portrait, landscape content.
 *  This page will be created suitable content in on_rotate() method.
 */
class page10: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();
		this->onRotate(this->getDegree());
	}

	void onRotate(int degree)
	{
		UiStandardView::onRotate(degree);

		if (this->getDegree() == 0 || this->getDegree() == 180)
		{
			//Portrait
			Evas_Object *content = createContent(this->getBase(), "ViewMgr++ Demo<br>Rotation",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->popView();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pushView(new page11());
					});

			this->setContent(content, "Page 10");
			this->setIndicator(UI_VIEW_INDICATOR_DEFAULT);
		} else {
			//Landscape
			Evas_Object *content = createLandscapeContent(this->getBase(), "ViewMgr++ Demo<br>Rotation",
					//Prev Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->popView();
					},
					//Next Button Callback
					[](void *data, Evas_Object *obj, void *event_info) -> void
					{
						UI_VIEWMGR->pushView(new page11());
					});

			this->setContent(content, "Page 10");
			this->setIndicator(UI_VIEW_INDICATOR_OPTIMAL);
		}
	}
public:
	page10() : UiStandardView("page10") {}
	~page10() {}
};
