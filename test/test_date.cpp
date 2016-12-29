#include <peelo/chrono/date.hpp>
#include <cassert>
#include <sstream>

static std::string date_to_string(const peelo::date& date)
{
  std::stringstream ss;

  ss << date;

  return ss.str();
}

int main()
{
  peelo::date date(1969, peelo::month::jul, 21);

  assert(date.year() == 1969);
  assert(date.month() == peelo::month::jul);
  assert(date.day() == 21);
  assert(date.day_of_week() == peelo::weekday::mon);
  assert(date.day_of_year() == 202);
  assert(date.days_in_month() == 31);
  assert(date.timestamp() == -16761600L);

  assert(date.equals(1969, peelo::month::jul, 21));
  assert(date.compare(1969, peelo::month::jul, 20) > 0);
  assert(date.compare(1969, peelo::month::jul, 22) < 0);

  assert(date + 5 == peelo::date(1969, peelo::month::jul, 26));
  assert(date - 5 == peelo::date(1969, peelo::month::jul, 16));

  assert(date.format("%d.%m.%Y") == "21.07.1969");
  assert(date_to_string(date) == "21 Jul 1969");
  assert(peelo::date(1986, peelo::month::sep, 27) - date == 6277);

  return 0;
}
