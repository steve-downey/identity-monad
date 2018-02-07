include_directories(${gtest_SOURCE_DIR}/include)
set(test_sources
  test1.cpp
  identity.t.cpp
)
add_executable(identitytest ${test_sources})
target_link_libraries(identitytest gtest_main identity)
enable_testing()
add_test(NAME IdentityTest COMMAND identitytest)
