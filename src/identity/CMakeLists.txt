add_library(identity STATIC "")

target_sources(
  identity
  PRIVATE
  identity.cpp)

include(GNUInstallDirs)

target_include_directories(identity PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/identity
  )

install(
  TARGETS identity
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_LOWER_PROJECT_NAME)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  )


## Tests
add_executable(identity_test "")

target_sources(
  identity_test
  PRIVATE
  identity.t.cpp
  )

target_link_libraries(identity_test identity)
target_link_libraries(identity_test gtest)
target_link_libraries(identity_test gtest_main)

include(GoogleTest)
gtest_discover_tests(identity_test)
