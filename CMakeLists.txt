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
  include/ovis/runtime/job.h src/job.cpp
  include/ovis/runtime/scene.h src/scene.hpp src/scene.cpp

  src/scheduler.hpp src/scheduler.cpp
  
  # include/ovis/runtime/application.hpp src/application.cpp
  # include/ovis/runtime/vm_bindings.hpp src/vm_bindings.cpp
  # include/ovis/runtime/main_vm.hpp src/main_vm.cpp
  # include/ovis/runtime/event_storage.hpp src/event_storage.cpp
  # include/ovis/runtime/json_schema.hpp src/json_schema.cpp
  # include/ovis/runtime/scheduler.hpp src/scheduler.cpp
  # include/ovis/runtime/job.hpp src/job.cpp
  # include/ovis/runtime/resource.hpp src/resource.cpp
  # include/ovis/runtime/scene.hpp src/scene.cpp
  # include/ovis/runtime/component_storage.hpp src/component_storage.cpp
  # include/ovis/runtime/scene_viewport.hpp src/scene_viewport.cpp
  # include/ovis/runtime/entity.hpp src/entity.cpp
  # include/ovis/runtime/scene_object_animation.hpp src/scene_object_animation.cpp
  # include/ovis/runtime/animator.hpp src/animator.cpp
  # include/ovis/runtime/animator_controller.hpp src/animator_controller.cpp
  # include/ovis/runtime/camera.hpp src/camera.cpp
  # include/ovis/runtime/transform.hpp src/transform.cpp
  # include/ovis/runtime/asset_library.hpp src/asset_library.cpp
  # include/ovis/runtime/vector_types.hpp src/vector_types.cpp
  # include/ovis/runtime/vector.hpp src/vector2.cpp src/vector3.cpp
  # include/ovis/runtime/color_type.hpp src/color_type.cpp
  # include/ovis/runtime/color.hpp src/color.cpp
  # include/ovis/runtime/matrix_types.hpp src/matrix_types.cpp
  # include/ovis/runtime/matrix.hpp src/matrix.cpp
  # include/ovis/runtime/math_operations.hpp src/math_operations.cpp
  # include/ovis/runtime/intersection.hpp src/intersection.cpp
  # include/ovis/runtime/math.hpp src/math.cpp
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
      "-sMAIN_MODULE"
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
  FILES_MATCHING PATTERN "*.h"
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
