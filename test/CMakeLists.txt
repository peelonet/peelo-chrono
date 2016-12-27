INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}../include)
ADD_EXECUTABLE(
  peelocpp_chrono_test
  main.cpp
  test_month.cpp
  test_weekday.cpp
)
TARGET_LINK_LIBRARIES(
  peelocpp_chrono_test
  peelocpp_chrono
)
ADD_TEST(NAME MyTest COMMAND peelocpp_chrono_test)
