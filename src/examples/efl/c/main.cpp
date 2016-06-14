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
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s lifecycle_callback = {0,};

	ret = ui_app_init(PACKAGE, LOCALE_DIR);
	if (!ret) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_init() is failed. err = %d", ret);
	}

	lifecycle_callback.create = app_create;

	ret = ui_app_run(argc, argv, &lifecycle_callback, NULL, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_run() is failed. err = %d", ret);
	}

	return ret;
}
