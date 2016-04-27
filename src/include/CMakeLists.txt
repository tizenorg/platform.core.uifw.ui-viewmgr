INSTALL(
        DIRECTORY ./ DESTINATION include/${LIBNAME}
        FILES_MATCHING
        PATTERN "efl/mobile/*.h"
        PATTERN "ui_viewmanager.h"
        )

