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

/** A example for view class extension.
 *  This example will be created content in view load time.
 */
class page1: public ui_view
{
private:
	appdata_s *ad;

protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 1",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					//Deactivate viewmgr, when prev button clicked.
					ad->viewmgr->deactivate();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					create_page2(ad);
				},
				this->ad);

		this->set_content(content, "Title");
	}

public:
	page1(appdata_s *ad) : ui_view("page1"), ad(ad)
	{
		//Push this view in viewmgr.
		ad->viewmgr->push_view(this);
	}

	~page1()
	{
	}
};

void create_page1(appdata_s *ad)
{
	new page1(ad);
}
