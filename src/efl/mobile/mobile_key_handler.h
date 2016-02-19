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
#ifndef MOBILE_KEY_HANDLER
#define MOBILE_KEY_HANDLER

#include <Elementary.h>
#include "../ui_key_handler.h"

namespace efl
{
class ui_viewmgr;

class mobile_key_handler : public ui_key_handler
{
public:
	mobile_key_handler(ui_viewmgr *viewmgr);

	bool init();
	bool term();

	ui_viewmgr *get_viewmgr() { return this->viewmgr; }
};

}

#endif /* MOBILE_KEY_HANDLER */
