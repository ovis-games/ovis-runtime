find_program(
  CLANG_FORMAT
  clang-format
  REQUIRED
)

function(add_clang_format target)
  get_target_property(
    sources
    ${target}
    SOURCES
  )
  add_custom_target(
    ${target}-clang-format
    ${CLANG_FORMAT} -i ${sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endfunction()
  
