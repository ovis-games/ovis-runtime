CPMAddPackage("gh:catchorg/Catch2@3.3.0")

macro(add_simple_test name)
  string(REPLACE "-" "_" file_base_name ${name})
  add_executable(${name} ${file_base_name}.cpp)

  target_link_libraries(
    ${name}
    PRIVATE
      ovis::runtime
      Catch2::Catch2
      Catch2::Catch2WithMain
  )

  add_test(
    NAME ${name}
    COMMAND ${name}
  )
endmacro()

add_simple_test(test-basic-types)
add_simple_test(test-list)
add_simple_test(test-scheduler)

if (OVIS_EMSCRIPTEN)
  add_executable(test-module test_module.cpp)
  target_include_directories(test-module PRIVATE ${OVIS_ROOT}/include)
  if (OVIS_EMSCRIPTEN)
    set_target_properties(
      test-module
      PROPERTIES
        SUFFIX ".wasm"
    )
    target_compile_options(test-module PRIVATE "-sSIDE_MODULE")
    target_link_options(test-module PRIVATE "-sSIDE_MODULE")
    configure_file("test_module.html" "${CMAKE_CURRENT_BINARY_DIR}/../test_module.html")
  else()
  endif()
endif()
