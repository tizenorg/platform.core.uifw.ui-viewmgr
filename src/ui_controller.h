#ifndef UI_CONTROLLER
#define UI_CONTROLLER

#include <Elementary.h>
#include <dlog.h>
#include "ui_controller_base.h"
#include "ui_view.h"

namespace efl
{
class ui_controller: public ui_controller_base
{
public:
	virtual ~ui_controller()
	{
	}

	virtual void load()
	{
	}

	virtual void unload()
	{
	}

	virtual void active()
	{
	}

	virtual void inactive()
	{
	}

	virtual void pause()
	{
	}

	virtual void resume()
	{
	}

	virtual void destroy()
	{
	}

	ui_view *get_view();
};
}

#endif /* UI_CONTROLLER_H */
