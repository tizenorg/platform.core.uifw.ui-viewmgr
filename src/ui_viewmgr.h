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
		 _window_delete_cb(void *data, Evas* e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
		 {
			printf("window delete!\n");
			//ui_viewmgr *viewmgr = data;
			//ui_viewmgr_del(viewmgr);
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
			 char group[100] = {0};

			 // create a layout using given style
			 layout = elm_layout_add(parent);
			 if (!style) style = "default";
			 snprintf(group, sizeof(group), "layout/viewmgr/%s", style);
			 //elm_layout_file_set(layout, "/usr/share/edje/ui-viewmgr/ui-viewmgr.edj", group);
			 //elm_layout_file_set(layout, ELM_DEMO_EDJ, group);
			 return layout;
		 }

		 static void
		 _delete_layout(Evas_Object* layout)
		 {
		    Evas_Object *content;
		    if(layout) {
		       content = elm_object_part_content_unset(layout, "swallow.view.this");
		       if(content)
		          evas_object_hide(content);
		       content = elm_object_part_content_unset(layout, "swallow.view.other");
		       if(content)
		          evas_object_hide(content);
		       evas_object_del(layout);
		    }
		 }

		 static void
		 _appear_finished_cb(void *data, Evas_Object *obj, const char *emision, const char *source)
		 {
			 printf("=========appear finished==============\n");
             ui_viewmgr *viewmgr = (ui_viewmgr *)data;
			 viewmgr->animation_ongoing = false;
		 }
		 static void
		 _appear_effect(ui_viewmgr *viewmgr)
		 {
			 Evas_Object *layout;
			 layout = _create_layout(viewmgr->base_layout, NULL);
			 elm_object_part_content_set(viewmgr->base_layout, "swallow.front", layout);
			 evas_object_show(layout);

			 //TODO: check the content is?
			 //TODO: event freeze?

			 ui_view_base<Evas_Object *> *appear_view = viewmgr->view_list.back();
			 //view appear start
             elm_object_part_content_set(layout,"swallow.view.this", appear_view->get_content());

			 // delete old layout if any
			 _delete_layout(elm_object_part_content_get(viewmgr->base_layout, "swallow.back"));

			 printf("layout signal emit and callback add\n");
			 // start the animation
			 elm_object_signal_emit(layout, "appear,effect", "elm");
			 elm_object_signal_callback_add(layout, "appear,effect,finished", "*", _appear_finished_cb, viewmgr);

		 }

		 static void _animation_cb(void *data)
		 {
			ui_viewmgr *viewmgr = (ui_viewmgr *)data;
			viewmgr->animation_job = NULL;

            printf("animation cb! %d\n", viewmgr->animation_ongoing);

			if (viewmgr->animation_ongoing)
			{
				printf("job add!!\n");
				viewmgr->animation_job = ecore_job_add(_animation_cb, viewmgr);
				return;
			}
			else
			{
				printf("ongoing flag make it true\n");
				viewmgr->animation_ongoing = true;
			}

			//TODO: separate up with appear, disappar case.

			_appear_effect(viewmgr);
		 }

      public:
		 ui_viewmgr(Evas_Object *window)
	     {
			 printf("ui view mgr add!\n");
			 if (!window) return;
             if (!evas_object_smart_type_check(window, "elm_win")) return;
			 //TODO: Check whether window has view manager or not already.

			 this->window = window;
			 evas_object_event_callback_add(this->window, EVAS_CALLBACK_DEL, _window_delete_cb, NULL);

			 //create conformant
			 this->conformant = _create_conformant(this->window);
			 //TODO: indicator property set.

			 this->base_layout = _create_layout(this->conformant, "baselayout");
			 evas_object_size_hint_weight_set(this->base_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			 elm_object_part_content_set(this->conformant, "elm.swallow.content", this->base_layout);

			 //TODO: Add key event handler?

	     }
		 ui_viewmgr()
		 {
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

		 //param should be ui_view
		 //virtual bool push_view(ui_view_base<Evas_Object *> *view)
		 virtual bool push_view(ui_view *view)
		 {
			 ui_viewmgr_base :: push_view(view);

			 printf("push view in efl side\n");

			 if (!this->animation_job)
			   this->animation_job = ecore_job_add(_animation_cb, this);

			 return true;
		 }
   };
}
