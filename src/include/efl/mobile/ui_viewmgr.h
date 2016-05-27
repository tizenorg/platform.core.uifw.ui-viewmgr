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
#ifndef _UI_VIEWMGR_H_
#define _UI_VIEWMGR_H_

namespace efl_viewmanager
{

class ui_view;
class ui_app;
class ui_app_capi;

/**
 *  @class ui_viewmgr
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a mobile EFL view manager class. Typically, this view manager extends ui_base_viewmgr and implements mobile specific behaviors for
 *         EFL view manager in mobile profile. ui_viewmgr is nothing more than ui_base_viewmgr in behavior perspective. It just comes out with renaming class
 *         for adapting with other EFL mobile classes.
 */
class ui_viewmgr: public ui_base_viewmgr
{
protected:
	//Don't allow to create ui_viewmgr instance
	/**
	 *  @brief This is a constructor for initializing viewmgr.
	 *
	 *  @param pkg The name of package.
	 */
	ui_viewmgr(const char *pkg);

	///Destructor.
	virtual ~ui_viewmgr();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_viewmgr);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_viewmgr);
	_UI_DECLARE_FRIENDS(ui_view);
	_UI_DECLARE_FRIENDS(ui_app);
	_UI_DECLARE_FRIENDS(ui_app_capi);
};
}

#endif /* _UI_VIEWMGR_H_ */
