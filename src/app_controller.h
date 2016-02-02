#include "ui_controller.h"

class app_controller1 : public ui_controller
{
 public:
	 app_controller1()
	 {
          LOGI("CALLED");
	 }

	 ~app_controller1()
	 {
          LOGI("CALLED");
	 }
    void load()
    {
		  ui_view *view = ui_controller :: get_view();
		  Evas_Object *btn = elm_button_add(view->get_parent());
		  elm_object_text_set(btn, "TEST");
		  view->set_content(btn);
          LOGI("CALLED btn = %p view = %p", btn, view);
    }

    void unload()
    {
          LOGI("CALLED");
    }

    void active()
    {
          LOGI("CALLED");
    }

    void inactive()
    {
          LOGI("CALLED");
    }

    void pause()
    {
          LOGI("CALLED");
    }

    void resume()
    {
          LOGI("CALLED");
    }

    void destroy()
    {
          LOGI("CALLED");
    }
};
