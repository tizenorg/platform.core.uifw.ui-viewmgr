#ifndef _UI_APP_C_H_
#define _UI_APP_C_H_

namespace efl_viewmanager
{

#ifdef __cplusplus
extern "C" {
#endif
	bool ui_app_init(const char *pkg, const char *locale_dir);

	int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data);

	ui_viewmgr *ui_app_viewmgr_get();

	ui_app *ui_app_app_get();
#ifdef __cplusplus
}
#endif

}
#endif /* _UI_APP_C_H_ */
