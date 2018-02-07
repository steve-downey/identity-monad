set(identity_sources
  identity.cpp
)

add_library(identity STATIC ${identity_sources})

target_include_directories(identity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
