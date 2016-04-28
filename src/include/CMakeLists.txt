INSTALL(
        DIRECTORY ./ DESTINATION include/${LIBNAME}
        FILES_MATCHING
        PATTERN "interface/*.h"
        PATTERN "efl/*.h"
        PATTERN "efl/mobile/*.h"
        PATTERN "*.h"
        )

