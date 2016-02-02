#include "ui_controller.h"

class app_controller : public efl::ui_controller
{
 public:

    virtual void load(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void unload(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void active(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void inactive(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void pause(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void resume(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }

    virtual void destroy(ui_view_base<Evas_Object *> *view)
    {
       LOGI("%p CALLED", view);
    }
};

