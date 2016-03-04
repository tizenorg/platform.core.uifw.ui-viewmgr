INSTALL(
        DIRECTORY ./ DESTINATION include/${LIB_NAME}
        FILES_MATCHING
        PATTERN "interface/*.h"
        PATTERN "efl/*.h"
        PATTERN "efl/mobile/*.h"
        PATTERN "ui_viewmanager.h"
        )

