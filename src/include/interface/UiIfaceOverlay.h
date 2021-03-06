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
#ifndef _UI_IFACE_OVERLAY_H_
#define _UI_IFACE_OVERLAY_H_

namespace ui_viewmanager
{

class UiIfaceView;

/**
 *  @class UiIfaceOverlay
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief This is a base class to support overlay view which could be active on other UiIfaceView. An overlay is designed to be one subordinate of one
 *         UiIfaceView. The specific behaviors of this class are totally depended on the derived class but it must be communicated with UiIfaceView to work
 *         successfully. Fundamentally, overlay view provides simpler interfaces than UiIfaceView since most of the overlay views will be active temporarily.
 *         This class is inherited to UiIfaceRotatable class to handle view's rotation state.
 */
class UiIfaceOverlay: public UiIfaceRotatable
{
public:
	/**
	 *  @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	virtual bool setContent(T content);

	/**
	 *  @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	virtual T unsetContent();

	/**
	 *  @brief The H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void onBack();

	/**
	 *  @brief Overlay activate.
	 *
	 *  @note It makes overlay state as show.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see deactivate()
	 */
	virtual bool activate();

	/**
	 *  @brief Overlay deactivate.
	 *
	 *  @note It makes overlay state as hide.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see activate()
	 */
	virtual bool deactivate();

	/**
	 *  @brief Return the active status of overlay.
	 *
	 *  @return @c true if overlay is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	virtual bool isActivated();

	/**
	 *  @brief Return a view which is matched with the overlay.
	 *
	 *  @return The view which is matched with overlay.
	 */
	UiIfaceView *getView();

	/**
	 *  @brief Return a content instance of this overlay.
	 *
	 *  @return content of overlay.
	 */
	virtual T getContent();

protected:
	/**
	 *  @brief This is a constructor for initializing overlay.
	 *
	 *  @param view The instance of UiIfaceView.
	 */
	explicit UiIfaceOverlay(UiIfaceView *view);

	///Destructor.
	virtual ~UiIfaceOverlay();

private:
	_UI_DECLARE_PRIVATE_IMPL(UiIfaceOverlay);
	_UI_DISABLE_COPY_AND_ASSIGN(UiIfaceOverlay);
};

}

#endif /* _UI_IFACE_OVERLAY_H_ */
