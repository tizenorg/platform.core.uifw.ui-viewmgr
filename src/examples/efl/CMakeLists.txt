SET(DEMO_NAME ui-viewmgr-demo)
SET(LIBNAME ${BINNAME})
SET(SRCS
	  ../../lib/efl/ui_base_view.cpp
	  ../../lib/efl/ui_base_viewmgr.cpp
	  ../../lib/efl/ui_base_key_listener.cpp
	  ../../lib/efl/mobile/ui_menu.cpp
	  ../../lib/efl/mobile/ui_popup.cpp
	  ../../lib/efl/mobile/ui_view.cpp
	  ../../lib/efl/mobile/ui_key_listener.cpp
	  ../../lib/efl/mobile/ui_viewmgr.cpp
	  main.cpp
   )

ADD_EXECUTABLE(${DEMO_NAME} ${SRCS})

PKG_CHECK_MODULES(DEMO_PKGS REQUIRED elementary efl-extension dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)
PKG_CHECK_MODULES(EXAM_PKGS REQUIRED elementary dlog efl-extension)

FOREACH(flag ${DEMO_PKGS_CFLAGS})
    SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${DEMO_NAME} PROPERTIES COMPILE_FLAGS "${PKG_CFLAGS}")
TARGET_LINK_LIBRARIES(${DEMO_NAME} ${DEMO_PKGS_LDFLAGS} ${DEMO_TARGET_PKGS_LDFLAGS})
TARGET_LINK_LIBRARIES(${DEMO_NAME} ${DEMO_PKGS_LDFLAGS} ${LIBNAME})
 
SET(GC_SECTIONS_FLAGS "-fdata-sections -ffunction-sections -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -Werror -Wno-unused -Wno-format-extra-args -Wl,--no-undefined -fvisibility=hidden -fPIE -g -std=c++0x ${GC_SECTIONS_FLAGS}")

INSTALL(TARGETS ${DEMO_NAME} DESTINATION /opt/usr/apps/${DEMO_NAME}/bin)
