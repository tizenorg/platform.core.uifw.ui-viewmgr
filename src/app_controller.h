#include "ui_controller.h"

class app_controller : public efl::ui_controller
{
 public:

    virtual void load(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void unload(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void active(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void inactive(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void pause(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void resume(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }

    virtual void destroy(ui_view_base<Evas_Object *> *view)
    {
       LOGI("CALLED");
    }
};

