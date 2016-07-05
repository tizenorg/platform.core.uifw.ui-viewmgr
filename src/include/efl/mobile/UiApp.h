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

class UiViewmgr;

/*
 *  @class UiIfaceApp
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief UiIfaceApp is designed for wrapping the application instance. This class hides unnecessary application settings but expose only basic functions
 *         such as initialization and run. Basically, it works on the application life-cycle. It has application life-cycle event interfaces such as create(),
 *         pause(), resume(), terminate(), etc so that users can handle those events for the their application concept. Also, It provides system event
 *         interfaces such as low_baterry(), low_meomory(), lang_changed(), region_changed() and so on. UiIfaceApp create an unique UiViewmgr instance
 *         internally, and manage its life.
*/
class UiApp : public ui_viewmanager::UiIfaceApp
{
public:
	/**
	 *  @brief This is a constructor for initializing UiPopup.
	 *
	 *  @param pkg The name of package.
	 *  @param loale_dir The path of locale directory.
	 */
	UiApp(const char *pkg, const char *locale_dir);

	///Destructor.
	virtual ~UiApp();

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return UiViewmgr instance.
	 */
	UiViewmgr *getViewmgr();

	/**
	 *  @brief Return UiApp instance.
	 *
	 *  @return The instance of UiApp.
	 */
	static UiApp *getInstance();

private:
	_UI_DISABLE_COPY_AND_ASSIGN(UiApp);

	//Don't generate by compiler.
	UiApp() = delete;
};

}

#endif /* _UI_APP_H_ */
