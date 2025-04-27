cmake_minimum_required(VERSION 3.14)
project(sqlite_orm_project)

include(FetchContent)
message(STATUS "start fetching")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SQLite3_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/sqlite3-src)
set(SQLite3_LIBRARY ${CMAKE_BINARY_DIR}/libsqlite3.a)
# Fetch sqlite_orm
FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_SHALLOW TRUE
    GIT_TAG master # Use a stable tag if needed
)

# Fetch SQLite amalgamation
message(STATUS "sqlite3")
FetchContent_Declare(
    sqlite3
    URL https://www.sqlite.org/2025/sqlite-amalgamation-3490100.zip # Example URL, check SQLite's official site for the latest version
    URL_HASH SHA3_256=e7eb4cfb2d95626e782cfa748f534c74482f2c3c93f13ee828b9187ce05b2da7
)

set(SQLite3_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/sqlite3-src)
set(SQLite3_LIBRARY ${CMAKE_BINARY_DIR}/libsqlite3.a)

FetchContent_MakeAvailable(sqlite3 sqlite_orm)
message(STATUS "finished")
file(GLOB SQLITE_FILES ${sqlite3_SOURCE_DIR}/sqlite3.c)
file(GLOB SQLITE_INCLUDES ${sqlite3_SOURCE_DIR}/)


message(STATUS "SQLite3 source dir: ${sqlite3_SOURCE_DIR}")
message(STATUS "SQLite3 include dir: ${sqlite3_SOURCE_DIR}")
# Add SQLite3 as a library
message(STATUS "SQLite3 target status: $<TARGET_EXISTS:sqlite3>")

add_library(sqlite3 STATIC ${sqlite3_SOURCE_DIR}/sqlite3.c)

# Link dependencies
add_executable(${PROJECT_NAME} program.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLite3_LIBRARY} sqlite_orm)

target_include_directories(${PROJECT_NAME} PRIVATE ${sqlite3_SOURCE_DIR} )

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json from build directory to source directory"
)
