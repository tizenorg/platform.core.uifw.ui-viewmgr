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

/** This page inherit UiStandardView.
 *  And implement on_portait(), on_landscape() method to create portrait, landscape content.
 *  This page will be created suitable content in on_portrait(), on_landscape() method.
 */
class page9: public UiStandardView
{
protected:
	void onLoad()
	{
		UiStandardView::onLoad();

		if (this->getOrientationMode() == UI_VIEW_ORIENTATION_MODE_PORTRAIT)
			this->onPortrait();
		else
			this->onLandscape();
	}

	void onPortrait()
	{
		UiStandardView::onPortrait();

		Evas_Object *content = createContent(this->getBase(), "ViewMgr Demo<br>Portrait/Landscape",
			//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page10());
		        });

		//Set title text, content, indicator property
		this->setTitle("Page9");
		this->setContent(content);
		this->setIndicator(UI_VIEW_INDICATOR_DEFAULT);
	}

	void onLandscape()
	{
		UiStandardView::onLandscape();

		Evas_Object *content = createLandscapeContent(this->getBase(), "ViewMgr Demo<br>Portrait/Landscape",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->popView();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pushView(new page10());
				});

		//Set title text, content, indicator property
		this->setTitle("Page9");
		this->setContent(content);
		this->setIndicator(UI_VIEW_INDICATOR_OPTIMAL);
	}

public:
	page9() : UiStandardView("page9") {}
	~page9() {}
};
