#ifndef _UI_APP_CAPI_H_
#define _UI_APP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ui_app_event_cb)(app_event_info_h event_info, void *data);

typedef struct
{
	ui_app_event_cb low_battery;
	ui_app_event_cb low_memory;
	ui_app_event_cb orient_changed;
	ui_app_event_cb lang_changed;
	ui_app_event_cb region_changed;
} ui_app_event_callback_s;

bool ui_app_init(const char *pkg, const char *locale_dir);
int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, ui_app_event_callback_s *event_callback, void *data);
ui_viewmgr *ui_app_viewmgr_get();
bool ui_app_term(void);

#ifdef __cplusplus
}
#endif

#endif /* _UI_APP_CAPI_H_ */
