#include <Elementary.h>
#include "ui_viewmgr_base.h"
#include "ui_view.h"

namespace efl
{
   class ui_viewmgr : public ui_viewmgr_base<Evas_Object *>
   {
    private:
       Ecore_Job *animation_job;
       bool animation_ongoing;
       Evas_Object *window;
       Evas_Object *conformant;
       Evas_Object *base_layout;

       static void
       _window_delete_cb(void *data, Evas* e EINA_UNUSED,
			             Evas_Object *obj EINA_UNUSED,
						 void *event_info EINA_UNUSED)
       {
          //Clean up resources
       }

       static Evas_Object *
       _create_conformant(Evas_Object *parent)
       {
          Evas_Object *conform;

          if (parent == NULL) return NULL;

          conform = elm_conformant_add(parent);
          evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
          elm_win_resize_object_add(parent, conform);
          evas_object_show(conform);

          return conform;
       }

       static Evas_Object *
       _create_layout(Evas_Object *parent, const char *style)
       {
          Evas_Object *layout;
          char group[100] = {0 };

          // create a layout using given style
          layout = elm_layout_add(parent);
          if (!style) style = "default";
          snprintf(group, sizeof(group), "layout/viewmgr/%s", style);
		  LOGI("Layout file set %s %s", ELM_DEMO_EDJ, group);
          elm_layout_file_set(layout, ELM_DEMO_EDJ, group);

          return layout;
       }

       static void
       _delete_layout(Evas_Object* layout)
       {
          Evas_Object *content;

		  if (layout)
		  {
             content = elm_object_part_content_unset(layout, "swallow.view.this");
             if (content)
                evas_object_hide(content);

			 content = elm_object_part_content_unset(layout, "swallow.view.other");

			 if (content)
                evas_object_hide(content);

			 evas_object_del(layout);
          }
       }

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
			  printf("content is NULL!\n");
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
              printf("anim.view_other = %p\n", viewmgr->anim.view_other);
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

          viewmgr->_push_view_finished(appear_view);

		  //evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.this"), EINA_FALSE);
		  //evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.other"), EINA_FALSE);

		  //destroy the view
		  // remove it from the view stack
		  //view_mgr->view_stack = eina_list_remove(view_mgr->view_stack, view_mgr->anim.view_this);
		  //elm_object_part_content_unset(obj,"swallow.view.this");
		  //ui_view_del(view_mgr->anim.view_this);

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

		  //TODO: check is it right?
          ui_view_base<Evas_Object *> *appear_view = viewmgr->view_list.back();

		  //view appear start
          elm_object_part_content_set(layout,"swallow.view.this", appear_view->get_content());

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
		  printf("view this = %p state = %d\n", viewmgr->anim.view_this, viewmgr->anim.view_this->get_state());

		  //TODO: fix below hard coding :(
		  printf("anim cb\n");

		  if (viewmgr->anim.view_this->get_state() == 1)
		  {
			  std::list<ui_view_base<Evas_Object *>*>::iterator li;

			 for (li = viewmgr->view_list.begin(); li!= viewmgr->view_list.end(); li++)
			 {
				 ui_view *view = (ui_view *)*li;
				if (view->get_state() == 2)
				{
				   printf("Find active view\n");
                   viewmgr->anim.view_other = view;
				   break;
				}
			 }

			 _appear_effect(viewmgr);
		  }

		  //_disappear_effect(viewmgr);

       }

    public:
       ui_viewmgr(Evas_Object *window) : animation_job(NULL), animation_ongoing(false)
       {
		  LOGI("CALLED");
          if (!window) {
            LOGE("window is NULL"); return;
          }

          if (!evas_object_smart_type_check(window, "elm_win")) {
            LOGE("param is not window"); return;
          }

		  if (evas_object_data_get(window, "viewmgr")) {
            LOGE("givin window has viewmgr already"); return;
		  }

          this->window = window;
          evas_object_event_callback_add(this->window, EVAS_CALLBACK_DEL, _window_delete_cb, NULL);

          //Create conformant
          this->conformant = _create_conformant(this->window);
          //NEED TO CHECK: call indicaotr mode set API?

          this->base_layout = _create_layout(this->conformant, "baselayout");
          evas_object_size_hint_weight_set(this->base_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
          elm_object_part_content_set(this->conformant, "elm.swallow.content", this->base_layout);

          //NEED TO CHECK: Key event handler add here?

          evas_object_data_set(window,"viewmgr", this);
       }

       ui_viewmgr()
       {
		  LOGI("CALLED");
       }

       virtual bool activate()
         {
            printf("activated\n");

            return EINA_TRUE;
         }
       virtual bool deactivate()
         {
            printf("deactivated\n");

            return EINA_TRUE;
         }

       virtual bool push_view(ui_view *view)
       {
          LOGI("CALLED");
          ui_viewmgr_base :: push_view(view);

          if (!this->animation_job)
            this->animation_job = ecore_job_add(_animation_cb, this);

          return true;
       }
   };
}
