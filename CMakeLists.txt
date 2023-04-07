cmake_minimum_required(
  VERSION 3.25
)

project(
  ovis-runtime
  VERSION 0.1.0
  LANGUAGES C CXX
)

set(OVIS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(OVIS_RUNTIME_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(OVIS_RUNTIME_MAIN_PROJECT ON)
endif()

option(OVIS_BUILD_TESTS "Build the tests" ${OVIS_RUNTIME_MAIN_PROJECT})
option(OVIS_COMPILER "Path to the ovis compiler" NONE)

include(CTest)
include(cmake/CPM.cmake)
include(cmake/emscripten.cmake)
include(cmake/ClangFormat.cmake)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

if (OVIS_EMSCRIPTEN)
  set(OVIS_LIBRARY_TYPE STATIC)
else()
  set(OVIS_LIBRARY_TYPE SHARED)
endif()

add_library(
  ovis-runtime ${OVIS_LIBRARY_TYPE}

  include/ovis/runtime.h src/runtime.c
  include/ovis/runtime/type.h src/type.c
  include/ovis/runtime/basic_types.h src/basic_types.c
  include/ovis/runtime/string.h src/string.c
  include/ovis/runtime/list.h src/list.c
  include/ovis/runtime/log.h src/log.c
  include/ovis/runtime/resource.h src/resource.hpp src/resource.cpp
  include/ovis/runtime/input_events.h src/input_events.c
  include/ovis/runtime/job.h src/job.cpp
  include/ovis/runtime/scene.h src/scene.hpp src/scene.cpp
  include/ovis/runtime/canvas.h src/canvas.cpp
  include/ovis/runtime/entity_descriptor.h src/entity_descriptor.cpp
  include/ovis/runtime/shapes.h src/shapes.cpp

  src/scheduler.hpp src/scheduler.cpp
  src/id_list.hpp src/id_list.cpp
  src/resource_storage.hpp src/resource_storage.cpp
  src/scene_component_storage.hpp src/scene_component_storage.cpp
  src/indexed_component_storage.hpp src/indexed_component_storage.cpp
  src/event_storage.hpp src/event_storage.cpp
)

add_clang_format(
  ovis-runtime
)

get_target_property(RUNTIME_SOURCES ovis-runtime SOURCES)
list(TRANSFORM RUNTIME_SOURCES REPLACE "^(.+)$" "${CMAKE_CURRENT_SOURCE_DIR}/\\1")

find_package(Python COMPONENTS Interpreter)

execute_process(
  COMMAND ${Python_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
)

add_custom_target(
  generate-module-file ALL
  COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_module_file.py ${RUNTIME_SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${RUNTIME_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/generate_module_file.py
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/ovis--runtime.json
  DESTINATION share
)

if (OVIS_EMSCRIPTEN)
  add_executable(ovis-runtime-emscripten src/emscripten.cpp)
  target_link_libraries(ovis-runtime-emscripten ovis-runtime)
  target_link_options(
    ovis-runtime-emscripten
    PRIVATE
      "-sMAIN_MODULE"
  )
  target_compile_options(
    ovis-runtime
    PRIVATE
      "-sMAIN_MODULE=1"
  )
  target_compile_options(
    ovis-runtime-emscripten
    PRIVATE
      "-sMAIN_MODULE=1"
      "-sMODULARIZE"
      "-sEXPORT_NAME=createModule"
  )
  target_link_options(
    ovis-runtime-emscripten
    PRIVATE
      "-sMAIN_MODULE=1"
      "-sMODULARIZE"
      "-sEXPORT_NAME=createModule"
      "-sEXPORT_ALL"
  )
  set_target_properties(
    ovis-runtime-emscripten
    PROPERTIES
      OUTPUT_NAME "ovis-runtime"
      SUFFIX ".js"
  )
  install(
    FILES
      "$<TARGET_FILE_DIR:ovis-runtime-emscripten>/$<TARGET_FILE_BASE_NAME:ovis-runtime-emscripten>${CMAKE_EXECUTABLE_SUFFIX}"
      "$<TARGET_FILE_DIR:ovis-runtime-emscripten>/$<TARGET_FILE_BASE_NAME:ovis-runtime-emscripten>.wasm"
    TYPE LIB
  )
else()
  install(TARGETS ovis-runtime)
endif()

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  TYPE INCLUDE
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
)

add_library(ovis::runtime ALIAS ovis-runtime)

target_include_directories(
  ovis-runtime
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

# target_link_libraries(
#   ovis-runtime
#   PUBLIC
#     ovis::utils
#     ovis::vm
# )

# target_add_schemas(
#   ovis-runtime

#   schemas/scene.schema.json
#   schemas/entity.schema.json
# )

# target_add_assets(
#   ovis-runtime

#   assets/runtime.script_documentation.en-US.json
#   assets/vector2.script_documentation.en-US.json
# )

if (OVIS_BUILD_TESTS)
  add_subdirectory(test)

  # target_add_assets(
  #   ovis-runtime-test

  #   test/assets/template.scene_object.json
  #   test/assets/recursive_template.scene_object.json
  #   test/assets/child_recursion_template.scene_object.json
  #   test/assets/indirect_recursion1.scene_object.json
  #   test/assets/indirect_recursion2.scene_object.json
  #   test/assets/animation_test.scene_object.json
  #   test/assets/test_script_type.script_type.json
  #   test/assets/test_script.script.json
  # )
  # target_embed_assets(ovis-runtime-test)
endif ()
