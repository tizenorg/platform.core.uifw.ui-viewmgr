#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_app.h"

using namespace efl_viewmanager;

extern "C" {
	int ui_app_init(const char *pkg, const char *locale_dir)
	{
		//TODO
		return 1;
	}

	int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data)
	{
		//TODO
		return 1;
	}
}
