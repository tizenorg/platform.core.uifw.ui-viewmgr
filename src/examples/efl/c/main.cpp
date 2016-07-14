#include "main.h"

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts.
		Initialize Application base resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */

	create_page1();

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

int
main(int argc, char *argv[])
{
	int ret = 0;
	ui_app_lifecycle_callback_s lifecycle_callback = {0, };

	//Initialize ui_app. ui_app initializes basic resources including ui_viewmgr internally.
	if (!(ret = ui_application_init(PACKAGE, LOCALE_DIR)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_init() is failed. err = %d", ret);
		return ret;
	}

	//Register life cycle callback functions.
	lifecycle_callback.create = app_create;
	lifecycle_callback.app_control = app_control;

	//Run ui_app. Now it requests to run an application mainloop.
	if ((ret = ui_application_run(argc, argv, &lifecycle_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_run() is failed. err = %d", ret);
		return ret;
	}

	//Terminate ui_app. Remove all ui_app resources.
	if (!(ret = ui_application_term()))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_term() is failed. err = %d", ret);
		return ret;
	}

	return 0;
}
