set(LIB_SPH 
  app.h
  app.cpp
  sph_common.h 
  sph_particle.h
  sph_particle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c
  ${CMAKE_CURRENT_SOURCE_DIR}/KHR/khrplatform.h
)

add_library(libsph STATIC ${LIB_SPH})
target_link_libraries(libsph glfw glm)
target_include_directories(libsph PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/../sph
)