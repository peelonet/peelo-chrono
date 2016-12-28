#include <peelo/chrono/time.hpp>
#include <cassert>
#include <sstream>

static std::string time_to_string(const peelo::time& time)
{
  std::stringstream ss;

  ss << time;

  return ss.str();
}

void test_time()
{
  peelo::time time = peelo::time(0, 0, 0);

  assert(time.hour() == 0);
  assert(time.minute() == 0);
  assert(time.second() == 0);

  time.assign(23, 59, 58);
  assert(time.equals(23, 59, 58));

  ++time;
  assert(time.equals(23, 59, 59));
  ++time;
  assert(time.equals(0, 0, 0));
  --time;
  assert(time.equals(23, 59, 59));

  time -= 59;
  assert(time.equals(23, 59, 0));
  assert(time.compare(23, 59, 59) < 0);
  assert(time.compare(23, 58, 59) > 0);

  time -= 3600;
  assert(time.equals(22, 59, 0));

  assert(time_to_string(time) == "22:59:00");
}
