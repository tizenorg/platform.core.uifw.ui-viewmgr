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
class page9: public ui_basic_view
{
private:
	appdata_s *ad;

public:
	page9(ui_controller *controller, const char *name, appdata_s *ad)
		: ui_basic_view(controller, name), ad(ad)
	{
		this->set_viewmgr(ad->viewmgr);

		//Create a main content.
		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Page 9<br>(View inheritance)",
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

		//Don't delete view's content when this view poped.
		this->set_removable_content(false);
		this->set_content(content, "Title");
		ad->viewmgr->push_view(this);
	}

	~page9()
	{
	}
};

void create_page9(appdata_s *ad)
{
	/* This page is case for inherit view instead of controller in application.
	   You can add controller for view create, otherwise create content in view
	   constructor.*/
	new page9(NULL, "page8", ad);
}
