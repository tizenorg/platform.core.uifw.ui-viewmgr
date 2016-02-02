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
}
