cmake_minimum_required(VERSION 3.12.2)

project(StudentsManageSystem)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(StudentsManageSystem
  ../../src/extra/sqlite3.c
  ../../src/StudentsManageSystem.cpp
  ../../src/StudentsManageSystem.h
)
# Preprocessor definitions
target_compile_definitions(StudentsManageSystem PRIVATE
  $<$<CONFIG:Debug>:_MBCS;>
  $<$<CONFIG:Release>:_MBCS;>
)

# SDL check
target_compile_options(StudentsManageSystem PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(StudentsManageSystem PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(StudentsManageSystem PRIVATE
    ""
  )
endif ()
