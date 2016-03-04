#include "ui_viewmanager_private.h"

using namespace efl_viewmgr;

class ui_capi_controller: public ui_controller
{
private:
	bool _ui_view_event_callback_call(ui_view *view, const char *event, void *event_info)
	{
		const char *strshare;

		if (!event) return EINA_FALSE;

		strshare = eina_stringshare_add(event);
		for (typename std::list<ui_view_event_callback *>::iterator it = callback_list.begin(); it != callback_list.end(); it++)
		{
			if (!(*it)->delete_me) {
				if (((*it)->view == view) &&((*it)->event == strshare))
				{
					eina_stringshare_del(strshare);
					return (*it)->func((*it)->func_data, view, event_info);
				}
			}
	    }

		eina_stringshare_del(strshare);
		return EINA_FALSE;
	}
public:
	void load()
	{
		ui_basic_view *view = dynamic_cast<ui_basic_view *>(this->get_view());
		_ui_view_event_callback_call(view, "load", NULL);
	}
};
