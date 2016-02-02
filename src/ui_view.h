#ifndef UI_VIEW
#define UI_VIEW

#include <Elementary.h>
#include "ui_view_base.h"

#define CONVERT_TO_EO(T) static_cast<Evas_Object *>((T))
#define CONVERT_TO_T(EO) static_cast<T>((EO))

namespace efl
{
   class ui_controller;

   class ui_view : public ui_view_base
   {
    public:
	   ui_view(ui_controller *controller);
	   ~ui_view();

      virtual Evas_Object *set_content(Evas_Object *content);
	  virtual Evas_Object *get_parent();

	protected:
	  virtual void load();

/*    protected:

       virtual void set_event_block(bool block)
       {
         //TO DO: Implement below to proper way.
         //if (block)
         //   evas_object_freeze_events_set(elm_object_part_content_get(this->content, "swallow.view.this"), EINA_FALSE);
         //else
         //	  evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_this), EINA_TRUE);
       } */
   };
}

#endif /* UI_VIEW */
