if (${CMAKE_CXX_COMPILER} MATCHES "emscripten")
  set(OVIS_EMSCRIPTEN TRUE)
else()
  set(OVIS_EMSCRIPTEN FALSE)
endif()

if (OVIS_EMSCRIPTEN)
  add_definitions("-DOVIS_EMSCRIPTEN=1")
endif()
