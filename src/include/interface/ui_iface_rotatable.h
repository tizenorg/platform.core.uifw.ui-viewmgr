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
#ifndef UI_ROTATABLE_INTERFACE_H_
#define UI_ROTATABLE_INTERFACE_H_

namespace viewmgr
{
class ui_iface_rotatable
{
protected:
	/** @brief This is for calling controller's portrait method.
	 */
	virtual void on_portrait() {}

	/** @brief This is for calling controller's landscape method.
	 */
	virtual void on_landscape() {}

	/** @brief This is for calling controller's rotate method.
	 */
	virtual void on_rotate(int degree) {}

public:
	/** @brief Get current view's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int get_degree() { return 0; }
};

}

#endif /* UI_ROTATABLE_INTERFACE_H_ */