#ifndef UI_VIEWMGR
#define UI_VIEWMGR

#include <Elementary.h>
#include "ui_viewmgr_base.h"

namespace efl
{

   class ui_view;


   class ui_viewmgr : public ui_viewmgr_base
   {
    private:
       Ecore_Job *animation_job;
       bool animation_ongoing;
       //CHECK is it really needed?
       bool to_show;
       Evas_Object *win;
       Evas_Object *conform;
	   Evas_Object *base_layout;

       Evas_Object * create_conformant(Evas_Object *win);
       Evas_Object * create_base_layout(Evas_Object *conform);

/*
       static void
       _appear_finished_cb(void *data, Evas_Object *obj, const char *emision, const char *source)
       {
		  LOGI("CALLED");
          ui_viewmgr *viewmgr = (ui_viewmgr *)data;

          viewmgr->_push_view_finished(viewmgr->anim.view_this);

		  //TODO: Appear finish callback call?

		  elm_object_part_content_set(viewmgr->base_layout, "swallow.back", obj);

		  //TODO: Thaw event?

		  viewmgr->anim.view_this = NULL;
		  viewmgr->anim.view_other = NULL;
          viewmgr->animation_ongoing = false;
          viewmgr->to_show = false;
       }

       static void
       _appear_effect(ui_viewmgr *viewmgr)
       {
		  LOGI("CALLED");
          Evas_Object *layout;

		  //TODO: send a style intead of NULL value below.
          layout = _create_layout(viewmgr->base_layout, NULL);
          elm_object_part_content_set(viewmgr->base_layout, "swallow.front", layout);
          evas_object_show(layout);

		  if (!viewmgr->anim.view_this->get_content())
		  {
			  //TODO: Content load here?
		  }

		  if (viewmgr->anim.view_this->get_content())
		  {
			  //TODO: Freeze event?
              elm_object_part_content_set(layout,"swallow.view.this", 
					                      viewmgr->anim.view_this->get_content());
			  //View appear start.
		  }

		  if (viewmgr->anim.view_other)
		  {
			  if (viewmgr->anim.view_other->get_content())
			  {
				  //TODO: Freeze event?
				  elm_object_part_content_set(layout,"swallow.view.other",
				                              viewmgr->anim.view_other->get_content());
				  //View disappear start.
			  }
		  }
          //ui_view_base<Evas_Object *> *appear_view = viewmgr->view_list.back();

          // delete old layout if any
          _delete_layout(elm_object_part_content_get(viewmgr->base_layout, "swallow.back"));

          // start the animation
          elm_object_signal_emit(layout, "appear,effect", "elm");
          elm_object_signal_callback_add(layout, "appear,effect,finished", "*", _appear_finished_cb, viewmgr);
       }

       static void
       _disappear_finished_cb(void *data, Evas_Object *obj, const char *emision, const char *source)
       {
		  LOGI("CALLED");
          ui_viewmgr *viewmgr = (ui_viewmgr *)data;

          ui_view_base<Evas_Object *> *appear_view = viewmgr->view_list.back();
          //appear_view->active();

          //viewmgr->_pop_view_finished(appear_view);

          elm_object_part_content_set(viewmgr->base_layout, "swallow.back", obj);
          //evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.this"), EINA_FALSE);
          //evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.other"), EINA_FALSE);

          //destroy the view
          // remove it from the view stack
          //viewmgr->view_list.pop_back();
          elm_object_part_content_unset(obj,"swallow.view.this");
          viewmgr-> _pop_view_finished(viewmgr->anim.view_this);
          //delete(viewmgr->anim.view_this);
          //Do it in unload method?
          evas_object_del(viewmgr->anim.view_this->get_content());

          viewmgr->anim.view_this = NULL;
          viewmgr->anim.view_other = NULL;
          viewmgr->animation_ongoing = false;
       }

	   static void
	   _disappear_effect(ui_viewmgr* viewmgr)
	   {
		  LOGI("CALLED");
	      Evas_Object *layout;

		  //TODO: send a style intead of NULL value below.
          layout = _create_layout(viewmgr->base_layout, NULL);
          elm_object_part_content_set(viewmgr->base_layout, "swallow.front", layout);
          evas_object_show(layout);

          //TODO: check the content is?
          //TODO: event freeze?

          elm_object_part_content_set(layout,"swallow.view.this",
                                      viewmgr->anim.view_this->get_content());
          elm_object_part_content_set(layout,"swallow.view.other",
                                      viewmgr->anim.view_other->get_content());

		  //TODO: check is it right?
          //ui_view_base<Evas_Object *> *appear_view = viewmgr->view_list.back();

		  //view appear start
          //elm_object_part_content_set(layout,"swallow.view.this", appear_view->get_content());

		  //evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_this), EINA_TRUE);
		  //evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_other), EINA_TRUE);

          // delete old layout if any
          _delete_layout(elm_object_part_content_get(viewmgr->base_layout, "swallow.back"));

          elm_object_signal_emit(layout, "disappear,effect", "elm");
          elm_object_signal_callback_add(layout, "disappear,effect,finished", "*", _disappear_finished_cb, viewmgr);
	   }

       static void _animation_cb(void *data)
       {
          ui_viewmgr *viewmgr = (ui_viewmgr *)data;
          viewmgr->animation_job = NULL;

          if (viewmgr->animation_ongoing) {
            viewmgr->animation_job = ecore_job_add(_animation_cb, viewmgr);
            return;
          } else {
            viewmgr->animation_ongoing = true;
          }

          viewmgr->anim.view_this = viewmgr->view_list.back();

          //TODO: fix below hard coding :(

          //if (viewmgr->anim.view_this->get_state() == 3)
          if (viewmgr->to_show)
          {
             std::list<ui_view_base<Evas_Object *>*>::iterator li;

             for (li = viewmgr->view_list.begin(); li!= viewmgr->view_list.end(); li++)
             {
                ui_view *view = (ui_view *)*li;
                if (view->get_state() == 2)
                {
                   printf("Find active view %p\n", view);
                   viewmgr->anim.view_other = view;
                   break;
                }
             }

              _appear_effect(viewmgr);
           }
           else
           {
              std::list<ui_view_base<Evas_Object *>*>::reverse_iterator li;

              int i = 0;
              for (li = viewmgr->view_list.rbegin(); li!= viewmgr->view_list.rend(); li++)
              {
                 i++;
                 ui_view *view = (ui_view *)*li;
                 //if (view->get_state() == 2)
                 if (i == 2)
                 {
                    printf("Find view %p\n", view);
                    viewmgr->anim.view_other = view;
                    break;
                 }
              }

              if (viewmgr->anim.view_other)
                 _disappear_effect(viewmgr);
           }
       }
*/
    public:
       ui_viewmgr(const char *pkg);
	   ~ui_viewmgr();
       bool activate();
       bool deactivate();
	   Evas_Object *get_window() { return this->win; }
       ui_view *push_view(ui_view *view);
	   bool pop_view();

	   //TODO: Make this private
	   Evas_Object *get_base_layout() { return this->base_layout; }
   };
}

#endif /* UI_VIEWMGR */
