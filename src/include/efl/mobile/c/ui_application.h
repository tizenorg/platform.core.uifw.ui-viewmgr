#ifndef _CAPI_UI_APPLICATION_H_
#define _CAPI_UI_APPLICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_APPLICATION ui_application
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_application.
 * @{
 */

/**
 *  @brief Initialize ui_application.
 *
 *  This function initializes ui_application and ui_viewmgr.
 *
 *  @param pkg The name of package.
 *  @param loale_dir The path of locale directory.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @warning Before exit application, call ui_application_term()
 *
 *  @see ui_application_term()
 */
EAPI bool ui_application_init(const char *pkg, const char *locale_dir);

/**
 *  @brief Run ui_application. This triggers application main loops.
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
EAPI int ui_application_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *user_data);

/**
 *  @brief This is ui_application destructor.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_application_init()
 */
EAPI bool ui_application_term(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _CAPI_UI_APPLICATION_H_ */
