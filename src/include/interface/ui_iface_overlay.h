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
#ifndef UI_IFACE_OVERLAY_H
#define UI_IFACE_OVERLAY_H

namespace viewmgr
{

class ui_iface_view;

template<typename T>
class ui_iface_overlay: public ui_iface_rotatable
{
private:
	ui_iface_view *view;
	T content;

protected:
	ui_iface_overlay(ui_iface_view *view);
	virtual ~ui_iface_overlay();
	virtual bool set_content(T content);
	virtual T unset_content();

public:
	ui_iface_view *get_view();
	virtual T get_content();
	virtual bool activate() = 0;
	virtual bool deactivate() = 0;
	virtual bool is_activated() = 0;
};


template<typename T>
ui_iface_overlay<T>::ui_iface_overlay(ui_iface_view *view)
		: view(view), content(NULL)
{
}

template<typename T>
ui_iface_overlay<T>::~ui_iface_overlay()
{
}

template<typename T>
bool ui_iface_overlay<T>::set_content(T content)
{
	T prev = this->content;
	this->content = content;
	return true;
}

template<typename T>
T ui_iface_overlay<T>::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

template<typename T>
T ui_iface_overlay<T>::get_content()
{
	return this->content;
}

template<typename T>
ui_iface_view *ui_iface_overlay<T>::get_view()
{
	return this->view;
}

}

#endif /* UI_IFACE_OVERLAY_H */
