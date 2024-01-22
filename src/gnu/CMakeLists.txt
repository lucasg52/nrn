add_library(
  nrngnu STATIC
  ACG.cpp
  Isaac64.cpp
  MCellRan4.cpp
  MLCG.cpp
  nrnran123.cpp
  Rand.cpp
  Random123RNG.cpp
  RNG.cpp)
set_property(TARGET nrngnu PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(nrngnu SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/external/Random123/include")
