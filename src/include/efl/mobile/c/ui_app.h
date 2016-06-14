#ifndef _UI_APP_CAPI_H_
#define _UI_APP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

//FIXME: rename prefix
bool ui_app_init(const char *pkg, const char *locale_dir);
int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *data);
ui_viewmgr *ui_app_viewmgr_get();
bool ui_app_term(void);

#ifdef __cplusplus
}
#endif

#endif /* _UI_APP_CAPI_H_ */
