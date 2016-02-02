#ifndef UI_BASIC_VIEW
#define UI_BASIC_VIEW

#include "ui_view.h"

namespace efl
{
	class ui_basic_view : public ui_view
	{
	private:
		Evas_Object *layout; //Base layout for view

		bool init_layout();

	protected:
		void load();

	public:
		ui_basic_view(ui_controller *controller);
		~ui_basic_view();

		Evas_Object *get_parent() { LOGI("CALLED layout = %p", this->layout); return this->layout; }
		Evas_Object *set_content(Evas_Object *content);
	};
}

#endif /* UI_BASIC_VIEW */
