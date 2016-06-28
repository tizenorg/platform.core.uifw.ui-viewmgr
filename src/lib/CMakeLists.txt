IF("${TARGET_LANGUAGE}" STREQUAL "c++")
SET(SRCS
     interface/UiIfaceOverlay.cpp
     interface/UiIfaceView.cpp
     interface/UiIfaceViewmgr.cpp
     interface/UiIfaceApp.cpp
     efl/UiBaseView.cpp
     efl/UiBaseViewmgr.cpp
     efl/UiBaseKeyListener.cpp
     efl/UiBaseOverlay.cpp
     efl/mobile/UiApp.cpp
     efl/mobile/UiMenu.cpp
     efl/mobile/UiPopup.cpp
     efl/mobile/UiView.cpp
     efl/mobile/UiStandardView.cpp
     efl/mobile/UiKeyListener.cpp
     efl/mobile/UiViewmgr.cpp
    )
ELSE()
SET(SRCS
     interface/UiIfaceOverlay.cpp
     interface/UiIfaceView.cpp
     interface/UiIfaceViewmgr.cpp
     interface/UiIfaceApp.cpp
     efl/UiBaseView.cpp
     efl/UiBaseViewmgr.cpp
     efl/UiBaseKeyListener.cpp
     efl/UiBaseOverlay.cpp
     efl/mobile/UiApp.cpp
     efl/mobile/UiMenu.cpp
     efl/mobile/UiPopup.cpp
     efl/mobile/UiView.cpp
     efl/mobile/UiStandardView.cpp
     efl/mobile/UiKeyListener.cpp
     efl/mobile/UiViewmgr.cpp
     efl/mobile/c/ui_application.cpp
     efl/mobile/c/ui_menu.cpp
     efl/mobile/c/ui_popup.cpp
     efl/mobile/c/ui_view.cpp
     efl/mobile/c/ui_standard_view.cpp
     efl/mobile/c/ui_viewmgr.cpp
    )
ENDIF()

ADD_LIBRARY(${LIBNAME} SHARED ${SRCS})
ADD_DEFINITIONS("-DEXPORT_API=__attribute__((visibility(\"default\")))")
ADD_DEFINITIONS("-DEDJ_PATH=\"${EDJDIR}\"")

PKG_CHECK_MODULES(LIB_PKGS REQUIRED elementary dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

FOREACH(flag ${LIB_PKGS_CFLAGS})
    SET(LIB_CFLAGS "${LIB_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES COMPILE_FLAGS "${LIB_CFLAGS}" VERSION ${VERSION})
TARGET_LINK_LIBRARIES(${LIBNAME} ${LIB_PKGS_LDFLAGS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS}")

INSTALL(TARGETS ${LIBNAME} DESTINATION ${LIBDIR})
