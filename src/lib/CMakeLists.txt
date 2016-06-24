IF("${TARGET_LANGUAGE}" STREQUAL "c++")
SET(SRCS
     interface/ui_iface_overlay.cpp
     interface/ui_iface_view.cpp
     interface/ui_iface_viewmgr.cpp
     interface/ui_iface_app.cpp
     efl/ui_base_view.cpp
     efl/ui_base_viewmgr.cpp
     efl/ui_base_key_listener.cpp
     efl/ui_base_overlay.cpp
     efl/mobile/ui_app.cpp
     efl/mobile/ui_menu.cpp
     efl/mobile/ui_popup.cpp
     efl/mobile/ui_view.cpp
     efl/mobile/ui_standard_view.cpp
     efl/mobile/ui_key_listener.cpp
     efl/mobile/ui_viewmgr.cpp
    )
ELSE()
SET(SRCS
     interface/ui_iface_overlay.cpp
     interface/ui_iface_view.cpp
     interface/ui_iface_viewmgr.cpp
     interface/ui_iface_app.cpp
     efl/ui_base_view.cpp
     efl/ui_base_viewmgr.cpp
     efl/ui_base_key_listener.cpp
     efl/ui_base_overlay.cpp
     efl/mobile/ui_app.cpp
     efl/mobile/ui_menu.cpp
     efl/mobile/ui_popup.cpp
     efl/mobile/ui_view.cpp
     efl/mobile/ui_standard_view.cpp
     efl/mobile/ui_key_listener.cpp
     efl/mobile/ui_viewmgr.cpp
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
