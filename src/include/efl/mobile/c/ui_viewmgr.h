#ifndef _UI_VIEWMGR_C_H_
#define _UI_VIEWMGR_C_H_

using namespace efl_viewmananger;

#ifdef __cplusplus
extern "C" {
#endif
	//TODO
	#define UI_VIEWMGR_DEACTIVATE() (ui_app_capi::get_instance()->get_viewmgr())->deactivate()
	#define UI_VIEWMGR_VIEW_PUSH(x) (ui_app_capi::get_instance()->get_viewmgr())->push_view(x)
	#define UI_VIEWMGR_VIEW_POP() (ui_app_capi::get_instance()->get_viewmgr())->pop_view()
#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_C_H_ */
