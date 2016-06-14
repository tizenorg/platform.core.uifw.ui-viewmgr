#include "main.h"

static bool
app_create(void *data)
{
	create_page1();

	return true;
}

int
main(int argc, char *argv[])
{
	ui_app_lifecycle_callback_s lifecycle_callback = {0, };

	if (!ui_app_init(PACKAGE, LOCALE_DIR))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_init() is failed. err = %d", ret);
		return ret;
	}

	lifecycle_callback.create = app_create;

	if (!ui_app_run(argc, argv, &lifecycle_callback, NULL, NULL))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_run() is failed. err = %d", ret);
		return ret;
	}

	if (!ui_app_term())
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_term() is failed. err = %d", ret);
		return ret;
	}

	return 0;
}
