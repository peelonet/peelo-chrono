#include <peelo/chrono/datetime.hpp>
#include <cassert>

int main()
{
  using namespace peelo;

  chrono::datetime dt(1969, chrono::month::jul, 21, 2, 56, 0);

  assert(dt.year() == 1969);
  assert(dt.month() == chrono::month::jul);
  assert(dt.day() == 21);
  assert(dt.hour() == 2);
  assert(dt.minute() == 56);
  assert(dt.second() == 0);
  assert(dt.day_of_week() == chrono::weekday::mon);
  assert(dt.day_of_year() == 202);
  assert(dt.timestamp() == -16751040L);

  assert(dt.equals(1969, chrono::month::jul, 21, 2, 56, 0));
  assert(dt.compare(1969, chrono::month::jul, 20, 2, 56, 0) > 0);
  assert(dt.compare(1969, chrono::month::jul, 22, 2, 56, 0) < 0);
  assert(dt.compare(1969, chrono::month::jul, 21, 2, 55, 0) > 0);
  assert(dt.compare(1969, chrono::month::jul, 21, 2, 57, 0) < 0);

  ++dt;
  assert(dt.equals(1969, chrono::month::jul, 22, 2, 56, 0));

  assert(dt + 5 == chrono::datetime(1969, chrono::month::jul, 27, 2, 56, 0));
  assert(dt - 5 == chrono::datetime(1969, chrono::month::jul, 17, 2, 56, 0));
  assert(dt - chrono::datetime(1969, chrono::month::jul, 22, 2, 50, 0) == 360);

  assert(dt.format("%d.%m.%Y %H:%M:%S") == "22.07.1969 02:56:00");
  assert(chrono::to_string(dt) == "Sun, 22 Jul 1969 02:56:00 +0000");

  const auto now = chrono::datetime::now();

  assert(chrono::datetime::is_valid(
    now.year(),
    now.month(),
    now.day(),
    now.hour(),
    now.minute(),
    now.second()
  ));

  return 0;
}
