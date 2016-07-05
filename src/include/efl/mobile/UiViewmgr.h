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

class UiView;
class UiApp;

/**
 *  @class UiViewmgr
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a mobile EFL view manager class. Typically, this view manager extends UiBaseViewmgr and implements mobile specific behaviors for
 *         EFL view manager in mobile profile. UiViewmgr is nothing more than UiBaseViewmgr in behavior perspective. It just comes out with renaming class
 *         for adapting with other EFL mobile classes.
 */
class UiViewmgr: public efl_viewmanager::UiBaseViewmgr
{
protected:
	//Don't allow to create UiViewmgr instance
	/**
	 *  @brief This is a constructor for initializing viewmgr.
	 *
	 *  @param pkg The name of package.
	 */
	UiViewmgr(const char *pkg);

	///Destructor.
	virtual ~UiViewmgr();

private:
	_UI_DISABLE_COPY_AND_ASSIGN(UiViewmgr);
	_UI_DECLARE_FRIENDS(UiView);
	_UI_DECLARE_FRIENDS(UiApp);

	//Don't generate by compiler.
	UiViewmgr() = delete;
};
}

#endif /* _UI_VIEWMGR_H_ */
