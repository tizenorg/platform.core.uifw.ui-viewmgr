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
#ifndef _UI_APP_CAPI_H_
#define _UI_APP_CAPI_H_

namespace efl_viewmanager
{

class ui_viewmgr;

class ui_app_capi
{
public:
	ui_app_capi(const char *pkg, const char *locale_dir);
	virtual ~ui_app_capi();

	ui_viewmgr *get_viewmgr();
	static ui_app_capi *get_instance();

	virtual int run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data);

protected:

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_app_capi);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_app_capi);
};

}

#endif /* _UI_APP_CAPI_H_ */
