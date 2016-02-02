#include <dlog.h>
#include "ui_controller.h"
#include "ui_viewmgr.h"
#include "ui_view_base.h"

using namespace efl;


void
ui_view_base :: set_event_block(bool block)
{
	this->event_block = block;
}


void
ui_view_base :: load()
{
	this->state = UI_VIEW_STATE_LOAD;
	if (this->content) return;
	if (!this->controller) return;
	this->controller->load();
}


void
ui_view_base :: unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->unload();
}


void
ui_view_base :: active()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (!this->controller) return;
	this->controller->active();
}


void
ui_view_base :: inactive()
{
	this->state = UI_VIEW_STATE_INACTIVE;
	if (!this->controller) return;
	this->controller->inactive();
}


void
ui_view_base :: pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
	if (!this->content) return;
	if (state != UI_VIEW_STATE_ACTIVE) return;
	if (!this->controller) return;
	this->controller->pause();
}


void
ui_view_base :: resume()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (state != UI_VIEW_STATE_PAUSE) return;
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->resume();
}


void
ui_view_base :: destroy()
{
	if (!this->controller) return;
	this->controller->destroy();
}


ui_view_base :: ui_view_base(T content, ui_controller_base *controller) : content(content),
	                                                                      controller(controller),
																		  name(string()),
                                                                          style(string()),
                                                                          viewmgr(NULL),
                                                                          state(UI_VIEW_STATE_LOAD),
                                                                          event_block(false)
{
	if (!content) this->state = UI_VIEW_STATE_UNLOAD;
	else this->state = UI_VIEW_STATE_LOAD;
	controller->set_view(this);
}

ui_view_base ::ui_view_base(ui_controller_base *controller = NULL) : ui_view_base(NULL, controller)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

ui_view_base :: ~ui_view_base()
{
        LOGE("1");
	this->viewmgr->remove_view(this);
        LOGE("2");
	if (this->controller) delete(this->controller);
        LOGE("3");
}



ui_controller_base*
ui_view_base :: set_controller(ui_controller_base *controller)
{
	ui_controller_base *prev_controller = this->controller;
	this->controller = controller;
	controller->set_view(this);
	prev_controller->set_view(NULL);
	return prev_controller;
}



T
ui_view_base :: set_content(T content)
{
	T prev = this->content;
	this->content = content;
	return prev;
}


bool
ui_view_base :: set_style(const char *style)
{
	this->style.assign(style);
	return true;
}
