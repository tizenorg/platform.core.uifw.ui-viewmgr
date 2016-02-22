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
#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <Elementary.h>
#include "../interface/ui_viewmanager_interface.h"

#define CONVERT_TO_EO(T) static_cast<Evas_Object *>((T))
#define CONVERT_TO_T(EO) static_cast<T>((EO))

namespace efl_viewmgr
{
class ui_controller;

class ui_view: public viewmgr::ui_view_interface
{
	friend class ui_viewmgr;

public:
	ui_view(ui_controller *controller, const char *name = NULL, const char *style = NULL);
	virtual ~ui_view();

	virtual Evas_Object *set_content(Evas_Object *content);
	virtual Evas_Object *get_base();

	void set_indicator(ui_view_indicator indicator);

protected:
	virtual void unload_content();
	Evas_Object *get_parent();
};

}

#endif /* UI_VIEW_H */
