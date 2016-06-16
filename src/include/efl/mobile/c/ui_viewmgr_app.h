#ifndef _UI_VIEWMGR_APP_CAPI_H_
#define _UI_VIEWMGR_APP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif


bool ui_viewmgr_app_init(const char *pkg, const char *locale_dir);
int ui_viewmgr_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *data);
bool ui_viewmgr_app_term(void);

#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_APP_CAPI_H_ */
