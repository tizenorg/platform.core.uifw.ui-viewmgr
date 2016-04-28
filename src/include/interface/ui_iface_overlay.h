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
#ifndef _UI_IFACE_OVERLAY_H_
#define _UI_IFACE_OVERLAY_H_

namespace ui_viewmanager
{

template<typename T, typename T2>
class ui_iface_view;

template<typename T, typename T2>
class ui_iface_overlay: public ui_iface_rotatable
{
private:
	ui_iface_view<T, T2> *view;
	T content;

protected:
	ui_iface_overlay(ui_iface_view<T, T2> *view);
	virtual ~ui_iface_overlay();

public:
	virtual bool set_content(T content);
	virtual T unset_content();
	ui_iface_view<T, T2> *get_view();
	virtual T get_content();
	virtual void on_back();
	virtual bool activate() = 0;
	virtual bool deactivate() = 0;
	virtual bool is_activated() = 0;
};


template<typename T, typename T2>
ui_iface_overlay<T, T2>::ui_iface_overlay(ui_iface_view<T, T2> *view)
		: view(view), content(NULL)
{
}

template<typename T, typename T2>
ui_iface_overlay<T, T2>::~ui_iface_overlay()
{
}

template<typename T, typename T2>
bool ui_iface_overlay<T, T2>::set_content(T content)
{
	this->content = content;
	return true;
}

template<typename T, typename T2>
T ui_iface_overlay<T, T2>::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

template<typename T, typename T2>
T ui_iface_overlay<T, T2>::get_content()
{
	return this->content;
}

template<typename T, typename T2>
ui_iface_view<T, T2> *ui_iface_overlay<T, T2>::get_view()
{
	return this->view;
}

template<typename T, typename T2>
void ui_iface_overlay<T, T2>::on_back()
{
	this->deactivate();
}

}

#endif /* _UI_IFACE_OVERLAY_H_ */
