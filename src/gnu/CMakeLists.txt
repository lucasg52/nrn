add_library(
  nrngnu STATIC
  ACG.cpp
  Binomial.cpp
  DiscUnif.cpp
  Erlang.cpp
  Geom.cpp
  HypGeom.cpp
  Isaac64.cpp
  LogNorm.cpp
  MCellRan4.cpp
  MLCG.cpp
  NegExp.cpp
  Normal.cpp
  nrnran123.cpp
  Poisson.cpp
  Rand.cpp
  Random123RNG.cpp
  RndInt.cpp
  RNG.cpp
  Uniform.cpp
  Weibull.cpp)
set_property(TARGET nrngnu PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(nrngnu SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/external/Random123/include")
