#include <peelo/chrono/date.hpp>
#include <cassert>

int main()
{
  using namespace peelo;

  chrono::date date(1969, chrono::month::jul, 21);

  assert(date.year() == 1969);
  assert(date.month() == chrono::month::jul);
  assert(date.day() == 21);
  assert(date.day_of_week() == chrono::weekday::mon);
  assert(date.day_of_year() == 202);
  assert(date.days_in_month() == 31);
  assert(date.timestamp() == -16761600L);

  assert(date.equals(1969, chrono::month::jul, 21));
  assert(date.compare(1969, chrono::month::jul, 20) > 0);
  assert(date.compare(1969, chrono::month::jul, 22) < 0);

  assert(date + 5 == chrono::date(1969, chrono::month::jul, 26));
  assert(date - 5 == chrono::date(1969, chrono::month::jul, 16));

  assert(date.format("%d.%m.%Y") == "21.07.1969");
  assert(chrono::to_string(date) == "21 Jul 1969");
  assert(chrono::date(1986, chrono::month::sep, 27) - date == 6277);

  const auto today = chrono::date::today();

  assert(chrono::date::is_valid(
    today.year(),
    today.month(),
    today.day()
  ));

  return 0;
}
