include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY
    https://github.com/catchorg/Catch2.git
  GIT_TAG
    v3.7.1
)
FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(TEST_FILENAME ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_FILENAME} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_FILENAME})

  target_include_directories(
    ${TEST_NAME}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/../include
  )

  if(MSVC)
    target_compile_options(
      ${TEST_NAME}
      PRIVATE
        /W4 /WX
    )
  else()
    target_compile_options(
      ${TEST_NAME}
      PRIVATE
        -Wall -Werror
    )
  endif()

  target_compile_features(
    ${TEST_NAME}
    PUBLIC
      cxx_std_17
  )

  target_link_libraries(
    ${TEST_NAME}
    Catch2::Catch2WithMain
    PeeloChrono
  )

  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# POSIX: TZ is read by the child; MSVC still needs _tzset() in test_environment.hpp.
set_tests_properties(test_date test_datetime PROPERTIES ENVIRONMENT "TZ=UTC")
