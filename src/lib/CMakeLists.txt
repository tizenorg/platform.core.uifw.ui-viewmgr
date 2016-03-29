SET(LIB_SRCS
     interface/ui_iface_controller.cpp
     interface/ui_iface_view.cpp
     interface/ui_iface_viewmgr.cpp
     efl/ui_base_popup.cpp
     efl/ui_base_controller.cpp
     efl/ui_base_view.cpp
     efl/ui_base_viewmgr.cpp
     efl/ui_base_key_listener.cpp
     efl/mobile/ui_controller.cpp
     efl/mobile/ui_menu.cpp
     efl/mobile/ui_view.cpp
     efl/mobile/ui_key_listener.cpp
     efl/mobile/ui_viewmgr.cpp
    )

ADD_LIBRARY(${LIB_NAME} SHARED ${LIB_SRCS})

ADD_DEFINITIONS("-DEXPORT_API=__attribute__((visibility(\"default\")))")
PKG_CHECK_MODULES(LIB_PKGS REQUIRED elementary efl-extension dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

FOREACH(flag ${LIB_PKGS_CFLAGS})
    SET(LIB_CFLAGS "${LIB_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES COMPILE_FLAGS "${LIB_CFLAGS}")
SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES VERSION ${VERSION})
SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES SOVERSION ${VERSION_MAJOR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${LIB_PKGS_LDFLAGS} ${LIB_TARGET_PKGS_LDFLAGS})

SET(GC_SECTIONS_FLAGS "-fdata-sections -ffunction-sections -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -Werror -Wno-unused -Wno-format-extra-args -Wl,--no-undefined -fvisibility=hidden -fPIC -std=c++0x ${GC_SECTIONS_FLAGS}")

INSTALL(TARGETS ${LIB_NAME} DESTINATION lib)
