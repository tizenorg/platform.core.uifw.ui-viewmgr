CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ui-viewmgr)
SET(PACKAGE org.tizen.ui-viewmgr)

SET(SRCS
	src/interface/ui_controller_interface.cpp
	src/interface/ui_view_interface.cpp
	src/interface/ui_viewmgr_interface.cpp
	src/efl/ui_controller.cpp
	src/efl/ui_view.cpp
	src/efl/ui_viewmgr.cpp
	src/efl/ui_key_listener.cpp
	src/efl/mobile/ui_basic_view.cpp
	src/efl/mobile/ui_basic_key_listener.cpp
	src/efl/example/main.cpp
   )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/inc)

FIND_LIBRARY(LIB_M m)
#FIXME: pthread is added for preventing build error
SET(PKG_LDFLAGS "-pthread ${LIB_M} -pie")
SET(PKG_CFLAGS "-g -Wall -fPIE")

INCLUDE(FindPkgConfig)
pkg_check_modules(BASE_PKG REQUIRED elementary efl-extension)
FOREACH(flag ${BASE_PKG_CFLAGS})
	SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)
FOREACH(flag ${BASE_PKG_LDFLAGS})
	SET(PKG_LDFLAGS "${PKG_LDFLAGS} ${flag}")
ENDFOREACH(flag)

pkg_check_modules(TIZEN_PKG REQUIRED dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)
FOREACH(flag ${TIZEN_PKG_CFLAGS})
	SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)
FOREACH(flag ${TIZEN_PKG_LDFLAGS})
	SET(PKG_LDFLAGS "${PKG_LDFLAGS} ${flag}")
ENDFOREACH(flag)

SET(GC_SECTIONS_FLAGS "-fdata-sections -ffunction-sections -Wl,--gc-sections")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PKG_CFLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -Werror -Wno-unused -Wno-format-extra-args -Wl,--no-undefined -fvisibility=hidden -fPIC -std=c++0x ${GC_SECTIONS_FLAGS}")

# install desktop file & icon
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(BINDIR "${PREFIX}/bin")
SET(RESDIR "${PREFIX}/res")
SET(DATADIR "${PREFIX}/data")
SET(LOCALEDIR "${RESDIR}/locale")
SET(IMGDIR "${RESDIR}/images")

ADD_DEFINITIONS("-DPACKAGE=\"${PACKAGE}\"")
ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DRESDIR=\"${RESDIR}\"")
ADD_DEFINITIONS("-DDATADIR=\"${DATADIR}\"")
ADD_DEFINITIONS("-DLOCALE_DIR=\"${LOCALEDIR}\"")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PKG_LDFLAGS})

ADD_CUSTOM_TARGET(${PROJECT_NAME}.edj
	COMMAND edje_cc -no-save -id ${CMAKE_CURRENT_SOURCE_DIR}/res
	${CMAKE_SOURCE_DIR}/res/${PROJECT_NAME}.edc ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.edj
	DEPENDS ${CMAKE_SOURCE_DIR}/res/${PROJECT_NAME}.edc
	)
ADD_DEPENDENCIES(${PROJECT_NAME} ${PROJECT_NAME}.edj)

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${BINDIR})
# for workaround taskmanager behaviour
INSTALL(FILES ${CMAKE_SOURCE_DIR}/data/${PACKAGE}.png DESTINATION /usr/share/icons/default/small/)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.edj DESTINATION ${RESDIR})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PACKAGE}.xml DESTINATION /usr/share/packages/)
