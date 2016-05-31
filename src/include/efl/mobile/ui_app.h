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
#ifndef _UI_APP_H_
#define _UI_APP_H_

namespace efl_viewmanager
{

class ui_viewmgr;

class ui_app : public ui_iface_app
{
public:
	/**
	 *  @brief This is a constructor for initializing ui_app.
	 *
	 *  @param pkg The name of package.
	 *  @param loale_dir The path of locale directory.
	 */
	ui_app(const char *pkg, const char *locale_dir);

	///Destructor.
	virtual ~ui_app();

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return ui_viewmgr instance.
	 */
	ui_viewmgr *get_viewmgr();

	/**
	 *  @brief Return ui_app instance.
	 *
	 *  @return The instance of ui_app.
	 */
	static ui_app *get_instance();

private:
	_UI_DISABLE_COPY_AND_ASSIGN(ui_app);
};

}

#endif /* _UI_APP_H_ */
