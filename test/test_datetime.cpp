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

#include "peelo/chrono/datetime.hpp"

using namespace peelo;

static const chrono::datetime dt(1969, chrono::month::jul, 21, 2, 56, 0);

TEST_CASE("Basic accessor methods")
{
  REQUIRE(dt.year() == 1969);
  REQUIRE(dt.month() == chrono::month::jul);
  REQUIRE(dt.day() == 21);
  REQUIRE(dt.hour() == 2);
  REQUIRE(dt.minute() == 56);
  REQUIRE(dt.second() == 0);
  REQUIRE(dt.day_of_week() == chrono::weekday::mon);
  REQUIRE(dt.day_of_year() == 202);
  REQUIRE(dt.timestamp() == -16751040L);
}

TEST_CASE("Equality and comparison methods")
{
  REQUIRE(dt.equals(1969, chrono::month::jul, 21, 2, 56, 0));
  REQUIRE(dt.compare(1969, chrono::month::jul, 20, 2, 56, 0) > 0);
  REQUIRE(dt.compare(1969, chrono::month::jul, 22, 2, 56, 0) < 0);
  REQUIRE(dt.compare(1969, chrono::month::jul, 21, 2, 55, 0) > 0);
  REQUIRE(dt.compare(1969, chrono::month::jul, 21, 2, 57, 0) < 0);
}

TEST_CASE("Addition and removal of days")
{
  REQUIRE(dt + 5 == chrono::datetime(1969, chrono::month::jul, 26, 2, 56, 0));
  REQUIRE(dt - 5 == chrono::datetime(1969, chrono::month::jul, 16, 2, 56, 0));
}

TEST_CASE("Duration calculation")
{
  const auto result = dt - chrono::datetime(
    1969,
    chrono::month::jul,
    21,
    2,
    50,
    0
  );

  REQUIRE(result.seconds() == 360);
}

TEST_CASE("Formatting")
{
  REQUIRE(dt.format("%d.%m.%Y %H:%M:%S") == "21.07.1969 02:56:00");
  REQUIRE(chrono::to_string(dt) == "Mon, 21 Jul 1969 02:56:00 +0000");
}

TEST_CASE("Validation")
{
  const auto now = chrono::datetime::now();

  REQUIRE(chrono::datetime::is_valid(
    now.year(),
    now.month(),
    now.day(),
    now.hour(),
    now.minute(),
    now.second()
  ));
}
