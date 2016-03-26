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
 *  And set subtitle in title area.
 */
class page3: public ui_view
{
private:
	appdata_s *ad;

protected:
	void on_load()
	{
		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 3",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					ad->viewmgr->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					appdata_s *ad = static_cast<appdata_s *>(data);
					create_page4(ad);
				},
				this->ad);

		//Arguments: content, title, subtitle, title left button, title right button
		this->set_content(content, "Title", "Subtitle", NULL, NULL);
	}

public:
	page3(const char *name, appdata_s *ad)
		: ui_view(name), ad(ad)
	{
		//Push this view in viewmgr.
		ad->viewmgr->push_view(this);
	}

	~page3()
	{
	}
};

void create_page3(appdata_s *ad)
{
	new page3("page3", ad);
}
