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
#ifndef _UI_STANDARD_VIEW_H_
#define _UI_STANDARD_VIEW_H_

namespace efl_viewmanager
{

class ui_standard_view: public ui_view
{
private:
	Elm_Layout *layout;                //Base layout for view
	Elm_Toolbar *toolbar;              //Toolbar
	Elm_Button *title_left_btn;        //Title left button
	Elm_Button *title_right_btn;       //Title right button

	bool create_layout();
	bool destroy_layout();

protected:
	virtual void on_load();
	virtual void on_unload();
	virtual void set_event_block(bool block);

public:
	ui_standard_view(const char *name = NULL);
	virtual ~ui_standard_view();

	bool set_content(Evas_Object *content, const char *title = NULL);
	bool set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_title_left_btn(Elm_Button *title_left_btn);
	bool set_title_right_btn(Elm_Button *title_right_btn);
	bool set_title(const char *text);
	bool set_toolbar(Elm_Toolbar *toolbar);
	bool set_title_visible(bool visible, bool anim);
	Evas_Object *unset_content();
	Elm_Button *unset_title_left_btn();
	Elm_Button *unset_title_right_btn();
	Elm_Toolbar *unset_toolbar();

	virtual Evas_Object *get_base();

	Elm_Button *get_title_left_btn()
	{
		return this->title_left_btn;
	}

	Elm_Button *get_title_right_btn()
	{
		return this->title_right_btn;
	}

	Elm_Toolbar *get_toolbar()
	{
		return this->toolbar;
	}
};

}

#endif /* _UI_STANDARD_VIEW_H_ */
