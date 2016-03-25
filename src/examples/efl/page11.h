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

class page11: public ui_view
{
private:
	appdata_s *ad;

protected:
	virtual void on_load()
	{
		this->on_rotate(this->get_degree());
	}

	virtual void on_rotate(int degree)
	{
		if (this->get_degree() == 0 || this->get_degree() == 180)
		{
			Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 11 (View inheritance)<br>With on_rotate()",
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
						ad->viewmgr->deactivate();
			        },
			        this->ad);
			this->set_content(content, "Title Portrait");
		}
		else
		{
			Evas_Object *content = create_landscape_content(this->get_base(), "ViewMgr Demo<br>Page 11 (View inheritance)<br>With on_rotate()",
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
						ad->viewmgr->deactivate();
			        },
			        this->ad);
			this->set_content(content, "Title Landscape");
		}
	}

public:
	page11(const char *name, appdata_s *ad)
		: ui_view(name), ad(ad)
	{
		ad->viewmgr->push_view(this);
	}

	~page11()
	{
	}
};

void create_page11(appdata_s *ad)
{
	/* A example for view class extension instead of using controller class. */
	new page11("page11", ad);
}
