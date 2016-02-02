#include "ui_controller.h"

class app_controller1: public ui_controller
{
private:
	appdata_s *ad;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		ad->viewmgr->deactivate();
	}

public:
	app_controller1(appdata_s *ad) :
			ad(ad)
	{
	}

	~app_controller1()
	{
	}

	void load()
	{
		ui_view *view = ui_controller::get_view();
		Evas_Object *btn = elm_button_add(view->get_parent());
		elm_object_text_set(btn, "Page 1");
		view->set_content(btn);
		LOGE("controller1");

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);
	}

	void unload()
	{
		ui_view *view = ui_controller::get_view();
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

class app_controller2: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{
		appdata_s *ad = static_cast<appdata_s *>(data);
		ad->viewmgr->pop_view();
	}

public:
	app_controller2(appdata_s *ad) :
			ad(ad), content(NULL)
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

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);

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

class app_controller4: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{

		appdata_s *ad = static_cast<appdata_s *>(data);

	}

public:
	app_controller4(appdata_s *ad) :
			ad(ad), content(NULL)
	{
	}

	~app_controller4()
	{
		LOGE("controller 4");
	}

	void load()
	{
		LOGE("view 4 button create");
		ui_view *view = this->get_view();
		Evas_Object *btn = elm_button_add(view->get_parent());
		elm_object_text_set(btn, "Page 4");
		view->set_content(btn);

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);

		this->content = btn;
	}

	void unload()
	{
		LOGE("controller4");
		evas_object_del(this->content);
		ui_view *view = this->get_view();
		view->set_content(NULL);
	}

	void active()
	{
		LOGE("controller4");
	}

	void inactive()
	{
		LOGE("controller4");
	}

	void destroy()
	{
		LOGE("controller4");
	}
};

class app_controller3: public ui_controller
{
private:
	appdata_s *ad;
	Evas_Object *content;

	static void page_clicked_cb(void *data, Evas_Object *obj, void *event_info)
	{

		appdata_s *ad = static_cast<appdata_s *>(data);

		//View 4

		app_controller4 *controller = new app_controller4(ad);
		ad->viewmgr->push_view(new ui_basic_view(controller));

	}

public:
	app_controller3(appdata_s *ad) :
			ad(ad), content(NULL)
	{
	}

	~app_controller3()
	{
		LOGE("controller 3");
	}

	void load()
	{
		ui_view *view = this->get_view();
		Evas_Object *btn = elm_button_add(view->get_parent());
		elm_object_text_set(btn, "Page 3");
		view->set_content(btn);

		evas_object_smart_callback_add(btn, "clicked", page_clicked_cb, this->ad);

		this->content = btn;
	}

	void unload()
	{
		LOGE("controller3");
		evas_object_del(this->content);
		ui_view *view = this->get_view();
		view->set_content(NULL);
	}

	void active()
	{
		LOGE("controller3");
	}

	void inactive()
	{
		LOGE("controller3");
	}

	void destroy()
	{
		LOGE("controller3");
	}
};

