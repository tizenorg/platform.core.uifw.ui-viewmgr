#ifndef _UI_VIEWMGR_APP_CAPI_H_
#define _UI_VIEWMGR_APP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief This is constructor for initializing ui_viewmgr_app.
 *
 *  @param pkg The name of package
 *  @param loale_dir The path of locale directory
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_viewmgr_app_init(const char *pkg, const char *locale_dir);

/**
 *  @brief This is calling ui_app_main() function with given params to run application's main loop.
 *
 *  @note This is wrapping ui_app_main() function.
 *
 *  @param argc The argument count
 *  @param argv The argument vector
 *  @param lifecycle_callback The set of callback functions to handle application lifecycle events
 *  @param user_data The user data to be passed to the callback functions
 *
 *  @return 0 on success, otherwise a negative error value
 */
int ui_viewmgr_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *user_data);

/**
 *  @brief This is ui_viewmgr_app destructor.
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_viewmgr_app_term(void);

#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_APP_CAPI_H_ */
