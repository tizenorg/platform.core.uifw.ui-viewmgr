#include "ui_view_base.h"

namespace efl
{
   class ui_view : public ui_view_base<Evas_Object *>
   {
    protected:

       virtual void set_event_block(bool block)
       {

         //TO DO: Implement below to proper way.
         //if (block)
         //   evas_object_freeze_events_set(elm_object_part_content_get(this->content, "swallow.view.this"), EINA_FALSE);
         //else
         //	  evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_this), EINA_TRUE);
       }
   };
}
