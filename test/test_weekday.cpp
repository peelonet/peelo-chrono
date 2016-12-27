#include <peelo/chrono/weekday.hpp>
#include <cassert>
#include <sstream>

static std::string weekday_to_string(const peelo::weekday& day)
{
  std::stringstream ss;

  ss << day;

  return ss.str();
}

void test_weekday()
{
  assert(static_cast<int>(peelo::weekday::mon) == 1);
  assert(static_cast<int>(peelo::weekday::sun) == 0);

  assert(peelo::weekday::mon + 3 == peelo::weekday::thu);
  assert(peelo::weekday::sat - 2 == peelo::weekday::thu);
  assert(peelo::weekday::mon + 8 == peelo::weekday::tue);
  assert(peelo::weekday::sat - 11 == peelo::weekday::tue);

  assert(weekday_to_string(peelo::weekday::mon) == "Monday");
  assert(weekday_to_string(peelo::weekday::fri) == "Friday");
}
