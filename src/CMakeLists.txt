ADD_LIBRARY(
  peelocpp_chrono
  weekday.cpp
)
INSTALL(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/peelo
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)
INSTALL(
  TARGETS peelocpp_chrono
  ARCHIVE
  DESTINATION lib
)
