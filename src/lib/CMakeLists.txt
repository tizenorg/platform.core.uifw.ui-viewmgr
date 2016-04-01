SET(LIBNAME ${BINNAME})

SET(SRCS
     efl/ui_base_view.cpp
     efl/ui_base_viewmgr.cpp
     efl/ui_base_key_listener.cpp
     efl/mobile/ui_menu.cpp
     efl/mobile/ui_popup.cpp
     efl/mobile/ui_view.cpp
     efl/mobile/ui_key_listener.cpp
     efl/mobile/ui_viewmgr.cpp
    )

ADD_LIBRARY(${LIBNAME} SHARED ${SRCS})

ADD_DEFINITIONS("-DEXPORT_API=__attribute__((visibility(\"default\")))")
PKG_CHECK_MODULES(LIB_PKGS REQUIRED elementary dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

FOREACH(flag ${LIB_PKGS_CFLAGS})
    SET(LIB_CFLAGS "${LIB_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES COMPILE_FLAGS "${LIB_CFLAGS}")
SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES VERSION ${VERSION})
SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES SOVERSION ${VERSION_MAJOR})
TARGET_LINK_LIBRARIES(${LIBNAME} ${LIB_PKGS_LDFLAGS} ${LIB_TARGET_PKGS_LDFLAGS})

SET(GC_SECTIONS_FLAGS "-fdata-sections -ffunction-sections -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -Werror -Wno-unused -Wno-format-extra-args -Wl,--no-undefined -fvisibility=hidden -fPIC -std=c++0x ${GC_SECTIONS_FLAGS}")

INSTALL(TARGETS ${LIBNAME} DESTINATION lib)
