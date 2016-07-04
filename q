[1mdiff --git a/src/examples/efl/cpp/page9.h b/src/examples/efl/cpp/page9.h[m
[1mindex 345043e..f921033 100644[m
[1m--- a/src/examples/efl/cpp/page9.h[m
[1m+++ b/src/examples/efl/cpp/page9.h[m
[36m@@ -27,7 +27,7 @@[m [mprotected:[m
 		UiStandardView::onLoad();[m
 [m
 		//FIXME: Change below code to more convenient and clear way.[m
[31m-		if (this->getDegree() == 90 || this->getDegree() == 270)[m
[32m+[m		[32mif (this->getOrientationMode() == UI_VIEW_ORIENTATION_MODE_PORTRAIT)[m
 			this->onLandscape();[m
 		else[m
 			this->onPortrait();[m
[1mdiff --git a/src/include/efl/mobile/UiView.h b/src/include/efl/mobile/UiView.h[m
[1mindex 06cbcb6..30f1ef6 100644[m
[1m--- a/src/include/efl/mobile/UiView.h[m
[1m+++ b/src/include/efl/mobile/UiView.h[m
[36m@@ -127,6 +127,7 @@[m [mprotected:[m
 	 */[m
 	virtual void onDeactivate();[m
 [m
[32m+[m	[32mvirtual UiViewOrientationMode getOrientationMode();[m
 private:[m
 	/**[m
 	 *  @brief Push given popup instance in the internal popup stack.[m
[1mdiff --git a/src/include/interface/UiIfaceTypes.h b/src/include/interface/UiIfaceTypes.h[m
[1mindex 65d29b7..49f27d9 100644[m
[1m--- a/src/include/interface/UiIfaceTypes.h[m
[1m+++ b/src/include/interface/UiIfaceTypes.h[m
[36m@@ -47,4 +47,13 @@[m [menum UiViewState[m
 };[m
 typedef enum UiViewState ui_view_state;[m
 [m
[32m+[m[32menum UiViewOrientationMode[m
[32m+[m[32m{[m
[32m+[m	[32mUI_VIEW_ORIENTATION_MODE_UNKOWN = 0,[m
[32m+[m	[32mUI_VIEW_ORIENTATION_MODE_PORTRAIT,[m
[32m+[m	[32mUI_VIEW_ORIENTATION_MODE_LANDSCAPE,[m
[32m+[m	[32mUI_VIEW_ORIENTATION_MODE_LAST,[m
[32m+[m[32m};[m
[32m+[m[32mtypedef enum UiViewOrientationMode ui_view_orient_mode;[m
[32m+[m
 #endif /* _UI_IFACE_TYPES_H_ */[m
[1mdiff --git a/src/lib/efl/mobile/UiView.cpp b/src/lib/efl/mobile/UiView.cpp[m
[1mindex 38813ea..4c03743 100644[m
[1m--- a/src/lib/efl/mobile/UiView.cpp[m
[1m+++ b/src/lib/efl/mobile/UiView.cpp[m
[36m@@ -46,6 +46,7 @@[m [mprotected:[m
 	void onPortrait();[m
 	void onLandscape();[m
 	bool onBack();[m
[32m+[m	[32mUiViewOrientationMode getOrientationMode();[m
 [m
 public:[m
 	UiViewImpl(UiView *view);[m
[36m@@ -157,6 +158,23 @@[m [mvoid UiViewImpl::onLandscape()[m
 	this->_menu->onLandscape();[m
 }[m
 [m
[32m+[m[32mUiViewOrientationMode UiViewImpl::getOrientationMode()[m
[32m+[m[32m{[m
[32m+[m	[32mswitch (this->_view->getDegree()) {[m
[32m+[m		[32mcase 0:[m
[32m+[m		[32mcase 180:[m
[32m+[m			[32mreturn UI_VIEW_ORIENTATION_MODE_PORTRAIT;[m
[32m+[m			[32mbreak;[m
[32m+[m		[32mcase 90:[m
[32m+[m		[32mcase 270:[m
[32m+[m			[32mreturn UI_VIEW_ORIENTATION_MODE_LANDSCAPE;[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m	[32mreturn UI_VIEW_ORIENTATION_MODE_UNKOWN;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m
 /***********************************************************************************************/[m
 /* External class Implementation                                                               */[m
 /***********************************************************************************************/[m
[36m@@ -234,6 +252,11 @@[m [mvoid UiView::onLandscape()[m
 	this->_impl->onLandscape();[m
 }[m
 [m
[32m+[m[32mUiViewOrientationMode UiView::getOrientationMode()[m
[32m+[m[32m{[m
[32m+[m	[32mreturn this->_impl->getOrientationMode();[m
[32m+[m[32m}[m
[32m+[m
 const UiMenu *UiView::getMenu()[m
 {[m
 	return this->_impl->getMenu();[m
