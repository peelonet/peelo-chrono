#include <peelo/chrono/month.hpp>
#include <cassert>
#include <sstream>

static std::string month_to_string(const peelo::month& month)
{
  std::stringstream ss;

  ss << month;

  return ss.str();
}

int main()
{
  assert(static_cast<int>(peelo::month::jan) == 0);

  assert(peelo::month::jan + 3 == peelo::month::apr);
  assert(peelo::month::sep - 2 == peelo::month::jul);
  assert(peelo::month::jan + 13 == peelo::month::feb);
  assert(peelo::month::nov - 13 == peelo::month::oct);

  assert(month_to_string(peelo::month::jan) == "January");
  assert(month_to_string(peelo::month::oct) == "October");

  return 0;
}
