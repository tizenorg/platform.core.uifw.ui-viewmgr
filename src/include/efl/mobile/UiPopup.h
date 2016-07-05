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
#ifndef _UI_POPUP_H_
#define _UI_POPUP_H_

namespace efl_viewmanager
{

class UiView;

/**
 *  @class UiPopup
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief UiPopup is to support EFL popup UI which could be active on one UiView. A popup is used for traditional popping context information to give
 *         an option or information in its view context. Elm_Popup widget could be set as this UiPopup content for mobile profile. UiPopup will set up all
 *         Elm_Popup decorating options instead of users for their convenient. A UiPopup is designed to be one subordinate of one UiView in order to share
 *         events and contexts each other to work nicely. One of differ points of UiPopup with UiMenu is, multiple popup could be active at the same time.
 *         That means, a new UiPopup will be overlaid on the previous UiPopup on the demands. It's up to user's scenario.
 *
 *  @warning UiPopup and its content, Elm_Popup will be deleted by its owned UiView on the proper time. So you can just leave its instance to it.
 */
class UiPopup : public efl_viewmanager::UiBaseOverlay
{
public:
	/**
	 *  @brief This is a constructor for initializing this popup.
	 *
	 *  @param The instance of UiView.
	 */
	UiPopup(UiView *view);

	///Destructor.
	virtual ~UiPopup();

	/**
	 *  @brief popup activate.
	 *
	 *  @note It makes popup state as show.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see deactivate()
	 */
	virtual bool activate();

	/**
	 *  @brief popup deactivate.
	 *
	 *  @note It makes popup state as hide.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see activate()
	 */
	virtual bool deactivate();

	/**
	 *  @brief This is for replacing or setting a content of the popup.
	 *
	 *  @param popup popup object. It allows @c NULL for canceling the previous content.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	virtual bool setContent(Elm_Popup* popup);

	/**
	 *  @brief This is for unsetting a content of the popup.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual Elm_Popup *unsetContent();

	/**
	 *  @brief Return the active status of popup.
	 *
	 *  @return @c true if overlay is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	virtual bool isActivated();

	/**
	 *  @brief Get a base object of an UiPopup.
	 *
	 * @note Normally, A base object can be used for a parent of UiPopup content.
	 *
	 *  @return base object of UiPopup.
	 */
	virtual Evas_Object *getBase();

	/**
	 *  @brief Get current popup's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int getDegree();

protected:
	/**
	 *  @brief Get a base window of viewmgr.
	 *
	 *  @return viewmgr's window object.
	 */
	virtual Elm_Win *getWindow();

private:
	_UI_DECLARE_PRIVATE_IMPL(UiPopup);
	_UI_DISABLE_COPY_AND_ASSIGN(UiPopup);

	//Don't generate by compiler.
	UiPopup() = delete;
};

}

#endif /* _UI_POPUP_H_ */
