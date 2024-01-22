add_library(
  nrngnu STATIC
  nrnran123.cpp
  Random123RNG.cpp)
set_property(TARGET nrngnu PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(nrngnu SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/external/Random123/include")
