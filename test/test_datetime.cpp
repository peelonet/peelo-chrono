#include <peelo/chrono/datetime.hpp>
#include <cassert>
#include <sstream>

static std::string datetime_to_string(const peelo::datetime& dt)
{
  std::stringstream ss;

  ss << dt;

  return ss.str();
}

int main()
{
  peelo::datetime dt(1969, peelo::month::jul, 21, 2, 56, 0);

  assert(dt.year() == 1969);
  assert(dt.month() == peelo::month::jul);
  assert(dt.day() == 21);
  assert(dt.hour() == 2);
  assert(dt.minute() == 56);
  assert(dt.second() == 0);
  assert(dt.day_of_week() == peelo::weekday::mon);
  assert(dt.day_of_year() == 202);
  assert(dt.timestamp() == -16751040L);

  assert(dt.equals(1969, peelo::month::jul, 21, 2, 56, 0));
  assert(dt.compare(1969, peelo::month::jul, 20, 2, 56, 0) > 0);
  assert(dt.compare(1969, peelo::month::jul, 22, 2, 56, 0) < 0);
  assert(dt.compare(1969, peelo::month::jul, 21, 2, 55, 0) > 0);
  assert(dt.compare(1969, peelo::month::jul, 21, 2, 57, 0) < 0);

  ++dt;
  assert(dt.equals(1969, peelo::month::jul, 22, 2, 56, 0));

  assert(dt + 5 == peelo::datetime(1969, peelo::month::jul, 27, 2, 56, 0));
  assert(dt - 5 == peelo::datetime(1969, peelo::month::jul, 17, 2, 56, 0));
  assert(dt - peelo::datetime(1969, peelo::month::jul, 22, 2, 50, 0) == 360);

  assert(dt.format("%d.%m.%Y %H:%M:%S") == "22.07.1969 02:56:00");
  assert(datetime_to_string(dt) == "1969-07-22T02:56:00Z");

  return 0;
}
