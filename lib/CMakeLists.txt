set(LIBNAME "QtH3C")
add_definitions(-DQH3C_VERSION="${PROJECT_VERSION}")

set(SOURCE
    QtH3C)

set(HEADERS
    QtH3C)

include(h3c/CMakeLists.txt)
include(types/CMakeLists.txt)
include(util/CMakeLists.txt)

add_library(${LIBNAME} ${SOURCE})

target_link_libraries(${LIBNAME}
    PUBLIC Qt5::Core)

foreach(LIB Qt5Core)
    set(PRIVATE_LIBS "${PRIVATE_LIBS} -l${LIB}")
endforeach()

install(TARGETS ${LIBNAME}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
install(FILES ${HEADERS}
DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME})
