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
#ifndef _UI_BASE_VIEW_H_
#define _UI_BASE_VIEW_H_

namespace efl_viewmanager
{

/**
 *  @class UiBaseView
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a base class of EFL view. Typically, this view extends UiIfaceView and implements basic behaviors for EFL view in all profiles.
 *         A view must have one Evas_Object content instance which represents a view for a current screen.
 */
class UiBaseView: public ui_viewmanager::UiIfaceView
{
public:
	/**
	 *  @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 */
	explicit UiBaseView(const char *name = NULL);

	///Destructor.
	virtual ~UiBaseView();

	/**
	 *  @brief This is for replacing or setting a content of the view.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	virtual bool setContent(Evas_Object *content) override;

	/**
	 *  @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	virtual Evas_Object *unsetContent() override;

	/**
	 *  @brief Get a base object of ui_view.
	 *
	 *  @note Normally, this base object can be used for a parent of a view content.
	 *
	 *  @return The base object of ui_view.
	 */
	virtual Evas_Object *getBase();

	/**
	 *  @brief Set the indicator mode.
	 *
	 *  @param indicator The mode to set, one of #UiViewIndicator.
	 */
	virtual void setIndicator(UiViewIndicator indicator) override;

	/**
	 *  @brief Get current view's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int getDegree() override;

protected:
	/**
	 *  @brief Get a parent object of view.
	 *
	 *  @note This is calling viewmgr get_base() method internally.
	 *
	 *  @return The base layout object of viewmgr.
	 */
	Evas_Object *getParent();

	/**
	 *  @brief Toggle event block.
	 *
	 *  @note It makes view content event freeze during effect showing.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 */
	virtual void setEventBlock(bool block) override;

	/**
	 *  @brief View rotate changed.
	 *
	 *  @note This state will be called when view rotation changed.
	 *
	 *  @param degree The current degree of view.
	 *
	 *  @see onPortrait()
	 *  @see onLandscpae()
	 */
	virtual void onRotate(int degree) override;

	/**
	 *  @brief View portrait state.
	 *
	 *  @note This state will be called when view rotation changed to portrait.
	 *
	 *  @see onLandscpae()
	 *  @see onRotate()
	 */
	virtual void onPortrait() override;

	/**
	 *  @brief View landscape state.
	 *
	 *  @note This state will be called when view rotation changed to landscape.
	 *
	 *  @see onPortrait()
	 *  @see onRotate()
	 */
	virtual void onLandscape() override;

private:
	_UI_DECLARE_PRIVATE_IMPL(UiBaseView);
	_UI_DISABLE_COPY_AND_ASSIGN(UiBaseView);
	_UI_DECLARE_FRIENDS(UiBaseViewmgr);

	//Don't generate by compiler.
	UiBaseView() = delete;
};

}

#endif /* _UI_BASE_VIEW_H_ */
