#include "ui_controller.h"

class app_controller : public efl::ui_controller
{
	public:

		virtual void load(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller load\n");
		}

		virtual void unload(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller unload\n");
		}

		virtual void active(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller active\n");
		}

		virtual void inactive(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller inactive\n");
		}


		virtual void pause(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller pause\n");
		}


		virtual void resume(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller resume\n");
		}


		virtual void destroy(ui_view_base<Evas_Object *> *view)
		{
			printf(" app_controller destroy\n");
		}
};

