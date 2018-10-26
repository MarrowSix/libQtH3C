set(TASK "qth3c")

set(SOURCE
    main.cpp client.cpp client.h)

add_executable(${TASK} ${SOURCE})

target_link_libraries(${TASK} Qt5::Core QtH3C)
target_include_directories(${TASK}
        PUBLIC ${PROJECT_SOURCE_DIR}/lib)

install(TARGETS ${TASK} RUNTIME DESTINATION bin)