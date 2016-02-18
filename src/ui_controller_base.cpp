#include <dlog.h>
#include "ui_view_base.h"
#include "ui_controller_base.h"

void ui_controller_base::set_view(ui_view_base *view)
{
	if (this->view)
	{
		//TODO: ?
	}
	this->view = view;
}
