file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)

    set(TARGET_NAME "${DIR_NAME}_${FILE_NAME}")

    add_executable(${TARGET_NAME} "${SOURCE_FILE}"
            third_exercise.cpp)
endforeach()