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
#ifndef _UI_BASE_OVERLAY_H_
#define _UI_BASE_OVERLAY_H_

namespace efl_viewmanager
{

class UiBaseView;

/**
 *  @class UiBaseOverlay
 *
 *  @internal
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a base class to support EFL overlay view which could be active on other UiBaseView. An overlay is designed to be one subordinate of one
 *         UiBaseView. UiBaseOverlay is nothing more than UiIfaceOverlay in behavior perspective. It just comes out with renaming class for adapting with
 *         other EFL base classes.
 */
class UiBaseOverlay: public ui_viewmanager::UiIfaceOverlay
{
protected:
	/**
	 *  @brief This is a constructor for initializing overlay.
	 *
	 *  @param view The instance of UiBaseView.
	 */
	UiBaseOverlay(UiBaseView *view);

	///Destructor.
	virtual ~UiBaseOverlay();
};

}

#endif /* _UI_BASE_OVERLAY_H_ */
