#ifndef _UI_VIEW_C_H_
#define _UI_VIEW_C_H_

namespace efl_viewmananger
{

#ifdef __cplusplus
extern "C" {
#endif
	typedef bool (*ui_view_lifecycle_load_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_unload_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_pause_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_resume_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_activate_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_deactivate_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_lifecycle_destroy_cb) (ui_view *view, void *data);

	typedef bool (*ui_view_event_rotate_cb) (ui_view *view, int degree, void *data);
	typedef bool (*ui_view_event_portrait_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_event_landscape_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_event_back_cb) (ui_view *view, void *data);
	typedef bool (*ui_view_event_menu_cb) (ui_menu *menu, void *data);

	typedef struct
	{
		ui_view_lifecycle_load_cb load;
		ui_view_lifecycle_unload_cb unload;
		ui_view_lifecycle_pause_cb pause;
		ui_view_lifecycle_resume_cb resume;
		ui_view_lifecycle_activate_cb activate;
		ui_view_lifecycle_deactivate_cb deactivate;
		ui_view_lifecycle_destroy_cb destroy;
	} ui_view_lifecycle_callback_s;

	typedef struct
	{
		ui_view_event_rotate_cb rotate;
		ui_view_event_portrait_cb portrait;
		ui_view_event_landscape_cb landscape;
		ui_view_event_back_cb back;
		ui_view_event_menu_cb menu;
	} ui_view_event_callback_s;
//================================== view common APIs ========================================

	bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data);
	bool ui_view_event_callbacks_set(ui_view *view, ui_view_event_callback_s *event_callback, void *data);

	Evas_Object* ui_view_base_get(ui_view *view);

	Evas_Object *ui_view_content_unset(ui_view *view);

	void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator);
	ui_view_indicator ui_view_indicator_get(ui_view *view);

	void ui_view_removable_content_set(ui_view *view, bool remove);
	bool ui_view_removable_content_get(ui_view *view);

	int  ui_view_degree_get(ui_view *view);

	bool ui_view_transition_style_set(ui_view *view, const char *style);
	const char *ui_view_transition_style_get(ui_view *view);

	const ui_menu *ui_view_menu_get(ui_view *view);

	bool ui_view_name_set(ui_view *view, const char *name);
	const char *ui_view_name_get(ui_view *view);

	ui_view_state ui_view_state_get(ui_view *view);

	Evas_Object *ui_view_content_get(ui_view *view);

//================================ ui_standard view APIs =====================================

	ui_view *ui_standard_view_create(const char *name);

	bool ui_standard_view_content_set(ui_view *view, Evas_Object *content,
									  const char *title, const char *subtitle,
									  Evas_Object *title_left_btn, Evas_Object *title_right_btn);

	bool ui_standard_view_title_set(ui_view *view, const char *text);

	bool ui_standard_view_sub_title_set(ui_view *view, const char *text);

	bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text);

	bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn);
	Elm_Button *ui_standard_view_title_right_btn_get(ui_view *view);
	Elm_Button *ui_standard_view_title_right_btn_unset(ui_view *view);

	bool ui_standard_view_title_left_btn_set(ui_view *view, Evas_Object *title_left_btn);
	Elm_Button *ui_standard_view_title_left_btn_get(ui_view *view);
	Elm_Button *ui_standard_view_title_left_btn_unset(ui_view *view);

	bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar);
	Elm_Toolbar *ui_standard_view_toolbar_get(ui_view *view);
	Elm_Toolbar *ui_standard_view_toolbar_unset(ui_view *view);

	bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim);

//==================================== ui_view APIs ==========================================

	ui_view *ui_view_create(const char *name);

	bool ui_view_content_set(ui_view *view, Evas_Object *content);


#ifdef __cplusplus
}
#endif

}
#endif /* _UI_VIEW_C_H_ */
