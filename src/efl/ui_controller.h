#ifndef UI_CONTROLLER
#define UI_CONTROLLER

#include <Elementary.h>
#include "../interface/ui_viewmgr.h"

namespace efl
{
class ui_controller: public ui_controller_base
{
public:
	virtual ~ui_controller()
	{
	}
	ui_view *get_view();

	virtual void load() {}
	virtual void unload() {}
	virtual void active() {}
	virtual void inactive() {}
	virtual void pause() {}
	virtual void resume() {}
	virtual void destroy() {}
};
}

#endif /* UI_CONTROLLER_H */
