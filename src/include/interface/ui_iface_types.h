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
#ifndef _UI_IFACE_TYPES_H_
#define _UI_IFACE_TYPES_H_

/**
 * Possible values for indicator state.
 */
enum ui_view_indicator
{
	UI_VIEW_INDICATOR_UNKNOWN = 0, ///< Unknown state (Exceptional case)
	UI_VIEW_INDICATOR_DEFAULT,     ///< Opaque indicator
	UI_VIEW_INDICATOR_OPTIMAL,     ///< Transparent indicator
	UI_VIEW_INDICATOR_OVERLAP,     ///< Overlap indicator
	UI_VIEW_INDICATOR_HIDE,        ///< Indicator hide
	UI_VIEW_INDICATOR_SHOW,        ///< Indicator show
	UI_VIEW_INDICATOR_LAST
};

/**
 * Possible values for view state.
 */
enum ui_view_state
{
	UI_VIEW_STATE_UNKNOWN = 0,     ///< Unknown state (Exceptional case)
	UI_VIEW_STATE_LOAD,            ///< Load state
	UI_VIEW_STATE_UNLOAD,          ///< Unload state
	UI_VIEW_STATE_ACTIVATE,        ///< Activate state
	UI_VIEW_STATE_DEACTIVATE,      ///< Deactivate state
	UI_VIEW_STATE_PAUSE,           ///< Pause state
	UI_VIEW_STATE_LAST
};

#endif
