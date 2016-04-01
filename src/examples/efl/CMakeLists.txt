SET(BINNAME ui.viewmgr.demo)

SET(SRCS
      main.cpp
   )

ADD_EXECUTABLE(${BINNAME} ${SRCS})

PKG_CHECK_MODULES(BIN_PKGS REQUIRED elementary dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

FOREACH(flag ${BIN_PKGS_CFLAGS})
    SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET_TARGET_PROPERTIES(${BINNAME} PROPERTIES COMPILE_FLAGS "${PKG_CFLAGS}" LINK_FLAGS -pie)
TARGET_LINK_LIBRARIES(${BINNAME} ${BIN_PKGS_LDFLAGS} ${LIBNAME})

SET(CMAKE_CXX_FLAGS "-Wall -g -fPIE -std=c++0x")

INSTALL(TARGETS ${BINNAME} DESTINATION ${BINDIR}/bin)
