#include <peelo/chrono/month.hpp>
#include <cassert>

int main()
{
  using namespace peelo;

  assert(static_cast<int>(chrono::month::jan) == 0);

  assert(chrono::month::jan + 3 == chrono::month::apr);
  assert(chrono::month::sep - 2 == chrono::month::jul);
  assert(chrono::month::jan + 13 == chrono::month::feb);
  assert(chrono::month::nov - 13 == chrono::month::oct);

  assert(chrono::to_string(chrono::month::jan) == "January");
  assert(chrono::to_string(chrono::month::oct) == "October");

  return 0;
}
