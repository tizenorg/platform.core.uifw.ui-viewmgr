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
#ifndef UI_IFACE_VIEW_H_
#define UI_IFACE_VIEW_H_

#include <string>

using namespace std;

namespace viewmgr {


template<typename T, typename T2>
class ui_iface_viewmgr;

/**
 *  @class ui_iface_view
 *
 *  @internal
 *  @ingroup viewmgr
 *
 *  @brief UI View Base Class. This is the base class of view. A view must have one content instance which represents a view for a current screen.
 *         UI View may have it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands.
 *         It's not mandatory but view should describe the transitions in this class.
 *
 *  @warning When the transitions are finished, the view must to call ui_iface_viewmgr :: _push_finished(), ui_iface_viewmgr :: _pop_finished() in order that
 *           The ui_iface_viewmgr keeps the view states exactly.
 */
template<typename T, typename T2>
class ui_iface_view : public ui_iface_rotatable
{
	friend class ui_iface_viewmgr<T, T2>;

private:
	T content;                              ///< A content instance for a screen as a view.
	string name;                            ///< View name.
	string transition_style;                ///< View transition style name.
	ui_iface_viewmgr<T, T2> *viewmgr;           ///< Viewmgr which this view belongs to.
	ui_view_state state;                    ///< View state.
	ui_view_indicator indicator;            ///< View indicator mode.
	bool event_block;                       ///< State of event block.
	bool removable_content;                 ///< When this value is true, view removes it's content internally on unload state.

protected:

	/** @brief toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_iface_viewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 */
	virtual void set_event_block(bool block);

	/** @brief view load state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_load();

	/** @brief view unload state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_unload();

	/** @brief view activate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_activate();

	/** @brief view deactivate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_deactivate();

	/** @brief view pause state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_pause();

	/** @brief view resume state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_resume();

	/** @brief view destroy state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_destroy();

	/** @brief Return the state of event block.
	 *
	 *  @see set_event_block()
	 */
	bool get_event_block();

	/** @brief Return a viewmgr which this view is belonging to.
	 */
	//FIXME: Is it necessary?
	ui_iface_viewmgr<T, T2> *get_viewmgr();

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return true if it succeed, false otherwise.
	 */
	virtual bool set_content(T content);

	/** @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual T unset_content();

public:
	/** @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 */
	ui_iface_view(const char *name = NULL);

	///Destructor for terminating view.
	virtual ~ui_iface_view();

	/** @brief set transition style of a view.
	 *
	 *  @note @p style is reserved for supporting various kinds of view transition effects.
	 *        The actual behaviors with this transition style is up to your frameworks. Default value of the style is NULL.
	 *        and "none" represents none transition. If you don't like give any transition effects to this view, you can pass "none" as @p style.
	 *
	 *  @param style a transition style name.
	 *
	 *  @return true if the given @c style is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should implement the logic to check the given style name is available or not.
	 *           If your framework doesn't support any styles then just allow a @c NULL argument and return true. Otherwise return false.
	 */
	bool set_transition_style(const char *style);

	/** @brief set name of the view.
	 *
	 *  @note A view can gets a specific name. default value of the name is NULL.
	 *
	 *  @param name a new name of view.
	 *
	 *  @return true if the given @c name is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should check the name duplicate with other view or not.
	 */
	bool set_name(const char *name);

	/** @brief set content removable.
	 *
	 *  @param removable if @p removable is @c true, content of this view will be removed on unload state. @c false otherwise.
 	 *
	 *  @warning You should not remove a view content manually on unload status if removable content is set.
	 */
	void set_removable_content(bool removable);

	/** @brief set the indicator of the view with mode.
	 *
	 *  @param indicator The mode to set, one of #ui_view_indicator.
	 */
	void set_indicator(ui_view_indicator indicator);

	/** @brief Return a style name of this view.
	 *
	 *  @return style name of view.
	 */
	const char *get_transition_style();

	/** @brief Return a name of this view.
	 *
	 *  @return name of view.
	 */
	const char *get_name();

	/** @brief Return a content instance of this view.
	 *
	 *  @return content of view.
	 */
	T get_content();

	/** @brief Return a state of this view.
	 *
	 *  #return current state of view.
	 */
	ui_view_state get_state();

	/** @brief Return a state of removable content.
	 *
	 *  @return true if the view's content is removable, otherwise false.
	 */
	bool get_removable_content();

	/** @brief Return the indicator mode of this view.
	 *
	 *  @return indicator state of view.
	 */
	ui_view_indicator get_indicator();

	void on_back();
};


template<typename T, typename T2>
bool ui_iface_view<T, T2>::get_event_block()
{
	return this->event_block;
}

template<typename T, typename T2>
ui_iface_viewmgr<T, T2> *ui_iface_view<T, T2>::get_viewmgr()
{
	return this->viewmgr;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::set_event_block(bool block)
{
	this->event_block = block;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_load()
{
	this->state = UI_VIEW_STATE_LOAD;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->set_content(NULL);
		return;
	}
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_activate()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_deactivate()
{
	this->state = UI_VIEW_STATE_DEACTIVATE;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_resume()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_destroy()
{
}

template<typename T, typename T2>
ui_iface_view<T, T2>::ui_iface_view(const char *name)
		: content(NULL), name(string(name ? name : "")), transition_style(string("default")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

template<typename T, typename T2>
ui_iface_view<T, T2>::~ui_iface_view()
{
	this->viewmgr->remove_view(this);
}

template<typename T, typename T2>
bool ui_iface_view<T, T2>::set_content(T content)
{
	this->content = content;
	return true;
}

template<typename T, typename T2>
T ui_iface_view<T, T2>::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

template<typename T, typename T2>
bool ui_iface_view<T, T2>::set_transition_style(const char *style)
{
	this->transition_style.assign(style);
	return true;
}

template<typename T, typename T2>
bool ui_iface_view<T, T2>::set_name(const char *name)
{
	this->name.assign(name);
	return true;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::set_removable_content(bool removable)
{
	this->removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::set_indicator(ui_view_indicator indicator)
{
	this->indicator = indicator;
}

template<typename T, typename T2>
const char *ui_iface_view<T, T2>::get_transition_style()
{
	return this->transition_style.c_str();
}

template<typename T, typename T2>
const char *ui_iface_view<T, T2>::get_name()
{
	return this->name.c_str();
}

template<typename T, typename T2>
T ui_iface_view<T, T2>::get_content()
{
	return this->content;
}

template<typename T, typename T2>
ui_view_state ui_iface_view<T, T2>::get_state()
{
	return this->state;
}

template<typename T, typename T2>
bool ui_iface_view<T, T2>::get_removable_content()
{
	return this->removable_content;
}

template<typename T, typename T2>
ui_view_indicator ui_iface_view<T, T2>::get_indicator()
{
	return this->indicator;
}

template<typename T, typename T2>
void ui_iface_view<T, T2>::on_back()
{
	ui_iface_viewmgr<T, T2> *viewmgr = this->get_viewmgr();
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr, view =%p", this);
		return;
	}
	viewmgr->pop_view();
}

}

#endif /* UI_IFACE_VIEW_H_ */
