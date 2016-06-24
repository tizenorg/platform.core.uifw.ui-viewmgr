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
#ifndef _UI_COMMON_VIEW_CAPI_H_
#define _UI_COMMON_VIEW_CAPI_H_

namespace efl_viewmanager
{

class ui_common_view_capi
{
public:
	ui_view_lifecycle_callback_s lifecycle_callback;
	ui_view_event_callback_s event_callback;
	void *lifecycle_data;
	void *event_data;
	const char *type;

	ui_common_view_capi(const char *type) : lifecycle_data(NULL), event_data(NULL), type(type)
	{
		this->lifecycle_callback = {0, };
		this->event_callback = {0, };
	}

	~ui_common_view_capi()
	{
	}
};

}

#endif /* _UI_COMMON_VIEW_CAPI_H_ */
