#include "ui_controller_base.h"


template <typename T>
class ui_view_base;

namespace efl
{

	using namespace std;
	class ui_controller : public ui_controller_base<Evas_Object *>
	{
		public:

			virtual void load(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller load\n");
			}

			virtual void unload(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller unload\n");
			}


			virtual void active(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller active\n");
			}


			virtual void inactive(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller inactive\n");
			}


			virtual void pause(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller pause\n");
			}


			virtual void resume(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller resume\n");
			}


			virtual void destroy(ui_view_base<Evas_Object *> *view)
			{
				printf(" efl_ui_controller destroy\n");
			}
	};
}
