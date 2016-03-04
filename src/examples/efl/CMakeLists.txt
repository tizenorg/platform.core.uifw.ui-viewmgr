SET(EXAM_NAME viewmgr_demo)
SET(EXAM_SRCS
	  ../../lib/interface/ui_iface_controller.cpp
	  ../../lib/interface/ui_iface_view.cpp
	  ../../lib/interface/ui_iface_viewmgr.cpp
	  ../../lib/efl/ui_controller.cpp
	  ../../lib/efl/ui_view.cpp
	  ../../lib/efl/ui_viewmgr.cpp
	  ../../lib/efl/ui_key_listener.cpp
	  ../../lib/efl/mobile/ui_basic_controller.cpp
	  ../../lib/efl/mobile/ui_basic_view.cpp
	  ../../lib/efl/mobile/ui_basic_key_listener.cpp
	  ../../lib/efl/mobile/ui_basic_viewmgr.cpp
	  main.cpp
   )

ADD_EXECUTABLE(${EXAM_NAME} ${EXAM_SRCS})

PKG_CHECK_MODULES(EXAM_PKGS REQUIRED elementary efl-extension dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

PKG_CHECK_MODULES(EXAM_PKGS REQUIRED elementary dlog efl-extension)

FOREACH(flag ${EXAM_PKGS_CFLAGS})
    SET(EXAM_CFLAGS "${EXAM_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${EXAM_NAME} PROPERTIES COMPILE_FLAGS "${EXAM_CFLAGS}")
TARGET_LINK_LIBRARIES(${EXAM_NAME} ${EXAM_PKGS_LDFLAGS} ${EXAM_TARGET_PKGS_LDFLAGS})
TARGET_LINK_LIBRARIES(${EXAM_NAME} ${EXAM_PKGS_LDFLAGS} ${LIB_NAME})

SET(GC_SECTIONS_FLAGS "-fdata-sections -ffunction-sections -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -Werror -Wno-unused -Wno-format-extra-args -Wl,--no-undefined -fvisibility=hidden -fPIC -std=c++0x ${GC_SECTIONS_FLAGS}")

INSTALL(TARGETS ${EXAM_NAME} DESTINATION /opt/usr/apps/ui-viewmgr/bin)
