#ifndef _UI_TIZEN_APP_CAPI_H_
#define _UI_TIZEN_APP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Initialize ui_tizen_app.
 *
 *  This function initializes ui_tizen_app and ui_viewmgr.
 *
 *  @param pkg The name of package.
 *  @param loale_dir The path of locale directory.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @warning Before exit application, call ui_tizen_app_term()
 *
 *  @see ui_tizen_app_term()
 */
bool ui_tizen_app_init(const char *pkg, const char *locale_dir);

/**
 *  @brief Run ui_tizen_app. This triggers application main loops.
 *
 *  @note This is wrapping ui_app_main() function.
 *
 *  @param argc The argument count.
 *  @param argv The argument vector.
 *  @param lifecycle_callback The set of callback functions to handle application lifecycle events.
 *  @param user_data The user data to be passed to the gieven @p life_cycle_callback functions.
 *
 *  @return 0 on success, otherwise a negative error value
 */
int ui_tizen_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *user_data);

/**
 *  @brief This is ui_tizen_app destructor.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_tizen_app_init()
 */
bool ui_tizen_app_term(void);

#ifdef __cplusplus
}
#endif

#endif /* _UI_TIZEN_APP_CAPI_H_ */
