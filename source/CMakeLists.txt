cmake_minimum_required(VERSION 3.16)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# The version number here is the canonical one for the project.
# Run rs-bump-version to increment the patch number
# and propagate the new version to version.hpp.

project(rs-sqlite
    VERSION 0.1.2
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
    add_compile_options(/EHsc /Gy /MP /O2 /sdl /utf-8 /W4 /WX)
else()
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    add_compile_options(-fdiagnostics-color=always -finput-charset=UTF-8 -march=native -O2 -Wall -Wextra -Wpedantic -Werror)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-Wsuggest-override -Wsuggest-destructor-override)
    endif()
endif()

if(WIN32)
    add_compile_definitions(NOMINMAX=1 UNICODE=1 _UNICODE=1 WINVER=0x601 _WIN32_WINNT=0x601)
else()
    add_compile_definitions(_REENTRANT=1 _XOPEN_SOURCE=700)
    if(APPLE)
        add_compile_definitions(_DARWIN_C_SOURCE=1)
    endif()
endif()

function(check_for_library required library header repo)
    find_file(found ${header})
    if(NOT found)
        if(required)
            message(SEND_ERROR "Required library not found: ${library}\nDownload from: ${repo}\n")
        else()
            message(WARNING "Optional library not found: ${library}\nDownload from: ${repo}\n")
        endif()
    endif()
endfunction()

check_for_library(yes rs-format rs-format.hpp https://github.com/CaptainCrowbar/rs-format)
check_for_library(yes rs-tl rs-tl.hpp https://github.com/CaptainCrowbar/rs-tl)
check_for_library(no rs-unit-test rs-unit-test.hpp https://github.com/CaptainCrowbar/rs-unit-test)

set(library rs-sqlite)
set(unittest test-${library})

set(executable PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

include_directories(.)
find_package(Threads REQUIRED)

add_library(${library} STATIC
    ${library}/sqlite.cpp
)

add_executable(${unittest}
    test/sqlite-test.cpp
    test/version-test.cpp
    test/unit-test.cpp
)

target_link_libraries(${unittest}
    PRIVATE ${library}
    PRIVATE sqlite3
    PRIVATE Threads::Threads
)

install(DIRECTORY ${library} DESTINATION include)
install(TARGETS ${library} LIBRARY DESTINATION lib)
