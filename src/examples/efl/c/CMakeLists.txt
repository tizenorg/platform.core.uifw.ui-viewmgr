SET(SRCS
      main.cpp
      contents.cpp
      page1.cpp
      page2.cpp
      page3.cpp
      page4.cpp
      page5.cpp
      page6.cpp
      page7.cpp
      page8.cpp
      page9.cpp
      page10.cpp
      page11.cpp
      page12.cpp
      page13.cpp
      page14.cpp
      page15.cpp
      page16.cpp
   )

ADD_EXECUTABLE(${BINNAME} ${SRCS})

ADD_DEFINITIONS("-DBINDIR=\"${BINDIR}\"")

PKG_CHECK_MODULES(BIN_PKGS REQUIRED elementary dlog capi-appfw-application capi-system-system-settings appcore-efl capi-appfw-app-manager)

FOREACH(flag ${BIN_PKGS_CFLAGS})
    SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)

TARGET_LINK_LIBRARIES(${BINNAME} ${BIN_PKGS_LDFLAGS} ${LIBNAME})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CFLAGS} -Wall -fPIE")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -pie")

INSTALL(TARGETS ${BINNAME} DESTINATION ${BINDIR}/bin)
