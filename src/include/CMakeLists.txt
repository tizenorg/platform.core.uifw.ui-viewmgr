INSTALL(
        DIRECTORY ./ DESTINATION include/${LIBNAME}
        FILES_MATCHING
        PATTERN "efl/mobile/*.h"
        PATTERN "efl/*.h"
        )

