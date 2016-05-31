//This is to check CAPIs.
#include "main.h"

Evas_Object*
create_landscape_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb)
{
	char buf[PATH_MAX];
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Scroller *scroller;
	Elm_Button *btn;
	Elm_Image *image;

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
	elm_grid_pack(grid, layout, 0, 0, 50, 100);

	/* Image */
	image = elm_image_add(grid);
	snprintf(buf, sizeof(buf), "%s/data/images/tizen.png", BINDIR);
	elm_image_file_set(image, buf, NULL);
	evas_object_show(image);
	elm_grid_pack(grid, image, 50, 0, 50, 85);

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


Evas_Object*
create_title_handle_content(Evas_Object *parent, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb,
				Evas_Smart_Cb title_show_btn_clicked_cb, Evas_Smart_Cb title_hide_btn_clicked_cb,
				Evas_Smart_Cb title_show_anim_btn_clicked_cb, Evas_Smart_Cb title_hide_anim_btn_clicked_cb, ui_view *view)
{
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Button *btn;

	/* Grid */
	grid = elm_grid_add(parent);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", NULL);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Box */
	box = elm_box_add(grid);
	//elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	//elm_box_padding_set(box, ELM_SCALE_SIZE(50), 0);
	evas_object_show(box);
	elm_grid_pack(grid, box, 25, 15, 50, 50);

	/* Title Show Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Show");
	evas_object_smart_callback_add(btn, "clicked", title_show_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Hide Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Hide");
	evas_object_smart_callback_add(btn, "clicked", title_hide_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Show Anim Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Show Anim");
	evas_object_smart_callback_add(btn, "clicked", title_show_anim_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Hide Anim Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Hide Anim");
	evas_object_smart_callback_add(btn, "clicked", title_hide_anim_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 1.0);
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

	return grid;
}

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

Evas_Object*
create_scrolling_content(Evas_Object *parent)
{
	char buf[PATH_MAX];
	Elm_Image *image;

	/* Image */
	image = elm_image_add(parent);
	snprintf(buf, sizeof(buf), "%s/data/images/bg.png", BINDIR);
	elm_image_file_set(image, buf, NULL);
	elm_image_resizable_set(image, EINA_FALSE, EINA_FALSE);
	evas_object_show(image);

	return image;
}

Elm_Toolbar*
create_toolbar(Evas_Object *parent, const char *style)
{
	Elm_Toolbar *toolbar;

	toolbar = elm_toolbar_add(parent);

	//FIXME: :( UI_View can set this style instead.
	elm_object_style_set(toolbar, style);

	//FIXME: If not call below API, toolbar items create with min size.
	//       It looks toolbar bug.
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);

	elm_toolbar_item_append(toolbar, NULL, "Tab1", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab2", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab3", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab4", NULL, NULL);

	return toolbar;
}

//=================================================================================
//================================== View 16 ======================================
//=================================================================================

static void
view16_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view16_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_DEACTIVATE();
}

static void
view16_title_show_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	ui_standard_view_title_visible_set(view, true, false);
}

static void
view16_title_hide_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	ui_standard_view_title_visible_set(view, false, false);
}

static void
view16_title_show_anim_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	ui_standard_view_title_visible_set(view, true, true);
}

static void
view16_title_hide_anim_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	ui_standard_view_title_visible_set(view, false, true);
}

static void
view16_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_title_handle_content(base_layout,
			view16_prev_btn_clicked_cb, view16_next_btn_clicked_cb,
			view16_title_show_btn_clicked_cb, view16_title_hide_btn_clicked_cb,
			view16_title_show_anim_btn_clicked_cb, view16_title_hide_anim_btn_clicked_cb, view);

	ui_standard_view_content_set(view, content, "Page16", NULL, NULL, NULL);
}

static void
create_page16()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view16_load_cb;

	ui_view *view = ui_standard_view_create("page16");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 15 ======================================
//=================================================================================

static void
view15_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page16();
}

static void
view15_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_scrolling_content(base_layout);

	ui_standard_view_content_set(view, content, "Page 15 Scroller In Viewmgr", NULL, NULL, NULL);

	//Title Right button
	Elm_Button *right_btn = elm_button_add(base_layout);
	elm_object_text_set(right_btn, "Next");
	evas_object_smart_callback_add(right_btn, "clicked", view15_btn_clicked_cb, NULL);

	ui_standard_view_title_right_btn_set(view, right_btn);
}

static void
create_page15()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view15_load_cb;

	ui_view *view = ui_standard_view_create("page15");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 14 ======================================
//=================================================================================

static void
view14_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view14_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page15();
}

static void
view14_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>None Transition",
			view14_prev_btn_clicked_cb, view14_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page14", NULL, NULL, NULL);
}

static void
create_page14()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view14_load_cb;

	ui_view *view = ui_standard_view_create("page14");
	ui_view_transition_style_set(view, "none");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 13 ======================================
//=================================================================================

static void
view13_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view13_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page14();
}

static void
view13_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Fade Transition",
			view13_prev_btn_clicked_cb, view13_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page13", NULL, NULL, NULL);
}

static void
create_page13()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view13_load_cb;

	ui_view *view = ui_standard_view_create("page13");
	ui_view_transition_style_set(view, "fade");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 12 ======================================
//=================================================================================

static void
view12_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view12_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page13();
}

static void
popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
popup_timeout_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	//FIXME: remove dismissed callback because this callback is called twice.
	//It seems this is an efl or popup error, not this ui_popup nor example.
	evas_object_smart_callback_del(obj, "dismissed", popup_dismissed_cb);
	ui_popup *popup = static_cast<ui_popup *>(data);

	//Is It right?
	ui_popup_del(popup);
}

static void
view12_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);

	//Create popup.
	//FIXME: is overlay a proper name?
	ui_popup *popup = ui_popup_create(view);

	Elm_Popup *elm_popup = elm_popup_add(ui_view_base_get(view));
	elm_object_text_set(elm_popup, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
	elm_popup_timeout_set(elm_popup, 3.0);
	evas_object_smart_callback_add(elm_popup, "dismissed", popup_dismissed_cb, popup);
	evas_object_smart_callback_add(elm_popup, "block,clicked", popup_block_clicked_cb, NULL);
	evas_object_smart_callback_add(elm_popup, "timeout", popup_timeout_cb, NULL);

	ui_popup_content_set(popup, elm_popup);
	ui_popup_activate(popup);
}

static void
view12_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Popup",
			view12_prev_btn_clicked_cb, view12_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page12", NULL, NULL, NULL);

	//Title Right button
	Elm_Button *right_btn = elm_button_add(base_layout);
	elm_object_text_set(right_btn, "popup");
	evas_object_smart_callback_add(right_btn, "clicked", view12_btn_clicked, view);

	ui_standard_view_title_right_btn_set(view, right_btn);
}

static void
create_page12()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	lifecycle_callback.load = view12_load_cb;

	ui_view *view = ui_standard_view_create("page12");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 11 ======================================
//=================================================================================

static void
view11_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view11_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page12();
}

static void
view11_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Menu Popup",
			view11_prev_btn_clicked_cb, view11_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page11", NULL, NULL, NULL);
}

static void ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = static_cast<Elm_Object_Item *>(event_info);
	elm_ctxpopup_dismiss(obj);
	LOGE("Item (%s) is selected", elm_object_item_text_get(it));
}

static void
view11_menu_cb(ui_menu *menu, void *data)
{
	Elm_Ctxpopup *ctxpopup = elm_ctxpopup_add(menu->get_base());
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);

	ui_menu_content_set(menu, ctxpopup);
}



static void
create_page11()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view11_load_cb;
	event_callback.menu = view11_menu_cb;

	ui_view *view = ui_standard_view_create("page11");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	ret = ui_view_event_callbacks_set(view, &event_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//=================================================================================
//================================== View 10 ======================================
//=================================================================================

static void
view10_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view10_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page11();
}

static void
view10_rotate_cb(ui_view *view, int degree, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	if (degree == 0 || degree == 180)
	{
		Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10", NULL, NULL, NULL);
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_DEFAULT);
	}
	else
	{
		Evas_Object *content = create_landscape_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10", NULL, NULL, NULL);
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_OPTIMAL);
	}
}

static void
view10_load_cb(ui_view *view, void *data)
{
	view10_rotate_cb(view, ui_view_degree_get(view), data);
}

static void
create_page10()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view10_load_cb;
	event_callback.rotate = view10_rotate_cb;

	ui_view *view = ui_standard_view_create("page10");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	ret = ui_view_event_callbacks_set(view, &event_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 9 ======================================
//================================================================================

static void
view9_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view9_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page10();
}

static void
view9_portrait_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Portrait/Landscape",
			view9_prev_btn_clicked_cb, view9_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page9", NULL, NULL, NULL);
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_DEFAULT);
}

static void
view9_landscape_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_landscape_content(base_layout, "ViewMgr Demo<br>Portrait/Landscape",
			view9_prev_btn_clicked_cb, view9_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page9", NULL, NULL, NULL);
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_OPTIMAL);
}

static void
view9_load_cb(ui_view *view, void *data)
{
	if (ui_view_degree_get(view) == 90 || ui_view_degree_get(view) == 270)
		view9_landscape_cb(view, data);
	else
		view9_portrait_cb(view, data);
}

static void
create_page9()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view9_load_cb;

	event_callback.portrait = view9_portrait_cb;
	event_callback.landscape = view9_landscape_cb;

	ui_view *view = ui_standard_view_create("page9");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	ret = ui_view_event_callbacks_set(view, &event_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 8 ======================================
//================================================================================

static void
view8_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view8_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page9();
}

static void
create_page8()
{
	ui_view *view = ui_standard_view_create("page8");

	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Content Preload",
			view8_prev_btn_clicked_cb, view8_next_btn_clicked_cb);

	ui_view_removable_content(view, false);
	ui_standard_view_content_set(view, content, "Page8", NULL, NULL, NULL);

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 7 ======================================
//================================================================================

static void
view7_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view7_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page8();
}

static void
view7_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Navigationbarr",
			view7_prev_btn_clicked_cb, view7_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page7", NULL, NULL, NULL);
	Elm_Toolbar *toolbar = create_toolbar(base_layout, "navigationbar");
	ui_standard_view_toolbar_set(view, toolbar);
}

static void
create_page7()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view7_load_cb;

	ui_view *view = ui_standard_view_create("page7");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 6 ======================================
//================================================================================

static void
view6_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view6_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page7();
}

static void
view6_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Toolbar",
			view6_prev_btn_clicked_cb, view6_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page6", NULL, NULL, NULL);
	Elm_Toolbar *toolbar = create_toolbar(base_layout, "toolbar_with_title");
	ui_standard_view_toolbar_set(view, toolbar);
}

static void
create_page6()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	lifecycle_callback.load = view6_load_cb;

	ui_view *view = ui_standard_view_create("page6");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 5 ======================================
//================================================================================

static void
view5_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view5_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page6();
}

static void
view5_load_cb(ui_view *view, void *data)
{
	LOGE("view5 load!");
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Full View",
			view5_prev_btn_clicked_cb, view5_next_btn_clicked_cb);

	ui_view_content_set(view, content);
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_HIDE);
}

static void
create_page5()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view5_load_cb;

	ui_view *view = ui_view_create("page5");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
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
	create_page5();
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
