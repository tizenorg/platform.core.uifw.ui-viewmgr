//This is to check CAPIs.
#include "main.h"

static bool
app_create(void *data)
{
	ui_app_init(NULL, NULL);
	ui_app_run(0, NULL, NULL, NULL);
	ui_menu_content_set(NULL, NULL);
	ui_popup_content_set(NULL, NULL);
	ui_popup_activate(NULL);
	ui_popup_del(NULL);
	ui_standard_view_create(NULL);
	ui_view_lifecycle_callbacks_set(NULL, NULL, NULL);
	ui_view_base_get(NULL);
	ui_view_content_set(NULL, NULL);
	ui_standard_view_content_set(NULL, NULL, NULL, NULL, NULL, NULL);
	ui_standard_view_title_badge_set(NULL, NULL);
	ui_view_indicator_set(NULL, UI_VIEW_INDICATOR_DEFAULT);
	ui_standard_view_toolbar_set(NULL, NULL);
	ui_view_removable_content(NULL, false);
	ui_view_event_callbacks_set(NULL, NULL, NULL);
	ui_standard_view_title_right_btn_set(NULL, NULL);
	ui_standard_view_title_visible_set(NULL, false, false);
	UI_VIEWMGR_VIEW_DEACTIVATE();
	UI_VIEWMGR_VIEW_PUSH(NULL);
	UI_VIEWMGR_VIEW_POP();

    return true;
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	ret = ui_app_init(PACKAGE, LOCALE_DIR);

	event_callback.create = app_create;

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}
