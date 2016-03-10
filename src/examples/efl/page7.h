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
class page7: public ui_basic_controller
{
private:
	appdata_s *ad;

public:
	page7(appdata_s *ad)
		: ad(ad)
	{
		/* ui_basic_view(controller, identity name, style name of view).
		   Later, you could get the identity name using view->get_name();
		   you could get the style name of view as well */
		ui_basic_view *view = new ui_basic_view(this, "page7");

		//FIXME: It will be deleted or change to other way :(
		//       We don't have any way to support it now.
		view->set_viewmgr(ad->viewmgr);

		//Create a main content.
		Evas_Object *content = create_content(view->get_base(), "ViewMgr Demo<br>Page 7<br>With Toolbar<br>(Navigationbar style)",
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

		view->set_content(content, "Title with toolbar");
		Evas_Object *toolbar = create_toolbar(view->get_base(), "navigationbar");
		view->set_toolbar(toolbar);
		ad->viewmgr->push_view(view);
	}

	~page7()
	{
	}
};

void create_page7(appdata_s *ad)
{
	new page7(ad);
}
