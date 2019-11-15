#include <peelo/chrono/time.hpp>
#include <cassert>

int main()
{
  using namespace peelo;

  chrono::time time(0, 0, 0);

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

  assert(time.format("%H:%M:%S") == "22:59:00");
  assert(chrono::to_string(time) == "22:59:00");

  const auto now = chrono::time::now();

  assert(chrono::time::is_valid(now.hour(), now.minute(), now.second()));

  return 0;
}
