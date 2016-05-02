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

/** This page inherit ui_standard_view.
 *  And implement on_portait(), on_landscape() method to create portarit, landscape content.
 *  This page will be created suitable content in on_portrait(), on_landscape() method.
 */
class page9: public ui_standard_view
{
protected:
	void on_load()
	{
		ui_standard_view::on_load();

		//FIXME: Change below code to more convenient and clear way.
		if (this->get_degree() == 90 || this->get_degree() == 270)
			this->on_landscape();
		else
			this->on_portrait();
	}

	void on_portrait()
	{
		ui_standard_view::on_portrait();

		Evas_Object *content = create_content(this->get_base(), "ViewMgr Demo<br>Portrait/Landscape",
			//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->push_view(new page10());
		        });
		this->set_content(content, "Page 9");
		this->set_indicator(UI_VIEW_INDICATOR_DEFAULT);
	}

	void on_landscape()
	{
		ui_standard_view::on_landscape();

		Evas_Object *content = create_landscape_content(this->get_base(), "ViewMgr Demo<br>Portrait/Landscape",
				//Prev Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->pop_view();
				},
				//Next Button Callback
				[](void *data, Evas_Object *obj, void *event_info) -> void
				{
					UI_VIEWMGR->push_view(new page10());
				});
		this->set_content(content, "Page 9");
		this->set_indicator(UI_VIEW_INDICATOR_OPTIMAL);
	}

public:
	page9() : ui_standard_view("page9") {}
	~page9() {}
};
