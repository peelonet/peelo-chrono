#include <peelo/chrono/weekday.hpp>
#include <cassert>

int main()
{
  using namespace peelo;

  assert(static_cast<int>(chrono::weekday::mon) == 1);
  assert(static_cast<int>(chrono::weekday::sun) == 0);

  assert(chrono::weekday::mon + 3 == chrono::weekday::thu);
  assert(chrono::weekday::sat - 2 == chrono::weekday::thu);
  assert(chrono::weekday::mon + 8 == chrono::weekday::tue);
  assert(chrono::weekday::sat - 11 == chrono::weekday::tue);

  assert(chrono::to_string(chrono::weekday::mon) == "Monday");
  assert(chrono::to_string(chrono::weekday::fri) == "Friday");

  return 0;
}
