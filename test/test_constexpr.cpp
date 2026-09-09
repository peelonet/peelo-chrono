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

using namespace peelo::chrono;

static_assert(date::from_ymd(1970, month::jan, 1).timestamp() == 0);
static_assert(date::from_ymd(1969, month::jul, 21).timestamp() == -14169600L);
static_assert(date::from_ymd(1969, month::jul, 21).day_of_year() == 202);
static_assert(date::from_ymd(1969, month::jul, 21).day_of_week() == weekday::mon);
static_assert(date::is_valid(2000, month::feb, 29));
static_assert(!date::is_valid(1900, month::feb, 29));
static_assert(date::from_ymd(1969, month::jul, 21) + 5
  == date::from_ymd(1969, month::jul, 26));
static_assert(
  date::from_ymd(1986, month::sep, 27) - date::from_ymd(1969, month::jul, 21)
  == duration::of_days(6277)
);
static_assert(time::from_hms(2, 56, 0).hour() == 2);
static_assert(time::from_hms(2, 56, 0).minute() == 56);
static_assert(
  datetime::from_ymd_hms(1969, month::jul, 21, 2, 56, 0).timestamp()
  == -14159040L
);
static_assert(datetime::is_valid(1969, month::jul, 21, 2, 56, 0));

TEST_CASE("Compile-time calendar constants")
{
  constexpr auto moon_landing = date::from_ymd(1969, month::jul, 21);
  constexpr auto duration_span =
    date::from_ymd(1986, month::sep, 27) - moon_landing;

  REQUIRE(moon_landing.year() == 1969);
  REQUIRE(duration_span.days() == 6277);
}
