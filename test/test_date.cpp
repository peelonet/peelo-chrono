/*
 * Copyright (c) 2016-2026, peelo.net
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <catch2/catch_test_macros.hpp>

#include "peelo/chrono/date.hpp"

using namespace peelo;

static const chrono::date date(1969, chrono::month::jul, 21);

TEST_CASE("Basic accessor methods")
{
  REQUIRE(date.year() == 1969);
  REQUIRE(date.month() == chrono::month::jul);
  REQUIRE(date.day() == 21);
  REQUIRE(date.day_of_week() == chrono::weekday::mon);
  REQUIRE(date.day_of_year() == 202);
  REQUIRE(date.days_in_month() == 31);
  REQUIRE(date.timestamp() == -16761600L);
}

TEST_CASE("Equality and comparison methods")
{
  REQUIRE(date.equals(1969, chrono::month::jul, 21));
  REQUIRE(date.compare(1969, chrono::month::jul, 20) > 0);
  REQUIRE(date.compare(1969, chrono::month::jul, 22) < 0);
}

TEST_CASE("Addition and removal of days")
{
  REQUIRE(date + 5 == chrono::date(1969, chrono::month::jul, 26));
  REQUIRE(date - 5 == chrono::date(1969, chrono::month::jul, 16));
}

TEST_CASE("Formatting")
{
  REQUIRE(date.format("%d.%m.%Y") == "21.07.1969");
  REQUIRE(chrono::to_string(date) == "21 Jul 1969");
}

TEST_CASE("Duration calculation")
{
  const auto result = chrono::date(1986, chrono::month::sep, 27) - date;

  REQUIRE(result.days() == 6277);
  REQUIRE(result.hours() == 150648);
}

TEST_CASE("Validation")
{
  const auto today = chrono::date::today();

  REQUIRE(chrono::date::is_valid(today.year(), today.month(), today.day()));
}
