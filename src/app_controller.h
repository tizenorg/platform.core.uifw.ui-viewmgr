#include "ui_controller.h"

class app_controller1 : public ui_controller
{
 public:
    app_controller1()
      {
      }

    ~app_controller1()
      {
      }

    void load()
      {
         ui_view *view = ui_controller :: get_view();
         Evas_Object *btn = elm_button_add(view->get_parent());
         elm_object_text_set(btn, "Page 1");
         view->set_content(btn);
         LOGE("controller1");
      }

    void unload()
      {
         ui_view *view = ui_controller :: get_view();
         Evas_Object *btn = view->set_content(NULL);
         evas_object_del(btn);
         LOGE("controller1");
      }

    void active()
      {
         LOGE("controller1");
      }

    void inactive()
      {
         LOGE("controller1");
      }
};




class app_controller2 : public ui_controller
{

static void
page2_clicked_cb(void *data, Evas_Object *obj, void *event_info)

        {
           appdata_s *ad = static_cast<appdata_s *>(data);
           ad->viewmgr->pop_view();
        }
 private:
   appdata_s *ad;
   Evas_Object *content;

 public:
   app_controller2(appdata_s *ad) : ad(ad), content(NULL)
   {
   }

   ~app_controller2()
     {
        LOGE("controller 2");
     }

   void load()
     {
        ui_view *view = this->get_view();
        Evas_Object *btn = elm_button_add(view->get_parent());
        elm_object_text_set(btn, "Page 2");
        view->set_content(btn);
        LOGI("CALLED btn = %p view = %p", btn, view);

        evas_object_smart_callback_add(btn, "clicked", page2_clicked_cb, this->ad);

        this->content = btn;
     }

   void unload()
     {
        LOGE("controller2");
        evas_object_del(this->content);
        ui_view *view = this->get_view();
        view->set_content(NULL);
     }

   void active()
     {
        LOGE("controller2");
     }

   void inactive()
     {
        LOGE("controller2");
     }

   void destroy()
     {
        LOGE("controller2");
     }
};
