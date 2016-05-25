#ifndef _UI_APP_C_H_
#define _UI_APP_C_H_

using namespace efl_viewmanager;

#ifdef __cplusplus
extern "C" {
#endif
	int ui_app_init(const char *pkg, const char *locale_dir);
	int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data);
#ifdef __cplusplus
}
#endif

#endif /* _UI_APP_C_H_ */
