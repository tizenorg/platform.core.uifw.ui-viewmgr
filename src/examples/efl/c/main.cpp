//This is to check CAPIs.
#include "main.h"

Evas_Object*
create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb)
{
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Scroller *scroller;
	Elm_Button *btn;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* Grid */
	grid = elm_grid_add(scroller);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", text);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, ELM_SCALE_SIZE(50), 0);
	evas_object_show(box);
	elm_grid_pack(grid, box, 0, 0, 100, 100);

	/* Previous Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Next Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(scroller, grid);

	return scroller;
}

//================================================================================
//================================== View 4 ======================================
//================================================================================

static void
view4_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view4_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	//create_page5();
}

static void
view4_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Badge",
			view4_prev_btn_clicked_cb, view4_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page4 We put a long title here intentionally", NULL, NULL, NULL);
	ui_standard_view_title_badge_set(view, "999+");
}

static void
create_page4()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	lifecycle_callback.load = view4_load_cb;

	ui_view *view = ui_standard_view_create("page4");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (!ret)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 3 ======================================
//================================================================================

static void
view3_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view3_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page4();
}

static void
view3_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Subtitle",
			view3_prev_btn_clicked_cb, view3_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page3", "Subtitle", NULL, NULL);
}

static void
create_page3()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view3_load_cb;

	ui_view *view = ui_standard_view_create("page3");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (!ret)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
	}


	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 2 ======================================
//================================================================================

static void
view2_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view2_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page3();
}

static void
view2_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Buttons",
			view2_prev_btn_clicked_cb, view2_next_btn_clicked_cb);

	//Title left button
	Elm_Button *left_title_btn = elm_button_add(base_layout);
	elm_object_text_set(left_title_btn, "Cancel");

	//Title right button
	Elm_Button *right_title_btn = elm_button_add(base_layout);
	elm_object_text_set(right_title_btn, "Done");

	ui_standard_view_content_set(view, content, "Page2", NULL, left_title_btn, right_title_btn);
}

static void
create_page2()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view2_load_cb;

	ui_view *view = ui_standard_view_create("page2");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (!ret)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 1 ======================================
//================================================================================

static void
view1_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_DEACTIVATE();
}

static void
view1_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page2();
}

static void
view1_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Basic View",
			view1_prev_btn_clicked_cb, view1_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page1", NULL, NULL, NULL);
}

static void
create_page1()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view1_load_cb;

	ui_view *view = ui_standard_view_create("page1");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (!ret)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
	}

	UI_VIEWMGR_VIEW_PUSH(view);

}

static bool
app_create(void *data)
{
	create_page1();

	return true;
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	ret = ui_app_init(PACKAGE, LOCALE_DIR);
	if (!ret) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_init() is failed. err = %d", ret);
	}

	event_callback.create = app_create;

	ret = ui_app_run(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_run() is failed. err = %d", ret);
	}

	return ret;
}
