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

#include "peelo/chrono/duration.hpp"

using namespace peelo;

TEST_CASE("Constructors")
{
  const auto d = chrono::duration(60);

  REQUIRE(d.seconds() == 60);
  REQUIRE(d.minutes() == 1);
  REQUIRE(chrono::duration(d).seconds() == 60);
  REQUIRE(chrono::duration::of_days(5).days() == 5);
  REQUIRE(chrono::duration::of_hours(5).hours() == 5);
  REQUIRE(chrono::duration::of_minutes(5).minutes() == 5);
}

TEST_CASE("days()")
{
  REQUIRE(chrono::duration(86400).days() == 1);
  REQUIRE(chrono::duration(89000).days() == 1);
  REQUIRE(chrono::duration(85400).days() == 0);
  REQUIRE(chrono::duration(172800).days() == 2);
}

TEST_CASE("hours()")
{
  REQUIRE(chrono::duration(3600).hours() == 1);
  REQUIRE(chrono::duration(3700).hours() == 1);
  REQUIRE(chrono::duration(3500).hours() == 0);
  REQUIRE(chrono::duration(7200).hours() == 2);
}

TEST_CASE("minutes()")
{
  REQUIRE(chrono::duration(60).minutes() == 1);
  REQUIRE(chrono::duration(70).minutes() == 1);
  REQUIRE(chrono::duration(50).minutes() == 0);
  REQUIRE(chrono::duration(120).minutes() == 2);
}

TEST_CASE("seconds()")
{
  REQUIRE(chrono::duration(5).seconds() == 5);
  REQUIRE(chrono::duration(-5).seconds() == -5);
  REQUIRE(chrono::duration::of_days(1).seconds() == 86400);
  REQUIRE(chrono::duration::of_hours(1).seconds() == 3600);
  REQUIRE(chrono::duration::of_minutes(1).seconds() == 60);
}

TEST_CASE("Assignment")
{
  auto d = chrono::duration();

  d.assign(500);
  REQUIRE(d.seconds() == 500);

  d.assign(chrono::duration(1500));
  REQUIRE(d.seconds() == 1500);

  d = 2000;
  REQUIRE(d.seconds() == 2000);

  d = chrono::duration(2500);
  REQUIRE(d.seconds() == 2500);
}

TEST_CASE("Equality testing")
{
  const auto d1 = chrono::duration(20);
  const auto d2 = chrono::duration(40);

  REQUIRE(d1.equals(d1));
  REQUIRE(!d1.equals(d2));

  REQUIRE((d1 == d1) == true);
  REQUIRE((d1 == d2) == false);

  REQUIRE((d1 != d1) == false);
  REQUIRE((d1 != d2) == true);
}

TEST_CASE("Comparison")
{
  const auto d1 = chrono::duration(1200);
  const auto d2 = chrono::duration(1000);
  const auto d3 = chrono::duration(1400);

  REQUIRE(d1.compare(d1) == 0);
  REQUIRE(d1.compare(d2) == 1);
  REQUIRE(d1.compare(d3) == -1);

  REQUIRE((d1 < d1) == false);
  REQUIRE((d1 < d2) == false);
  REQUIRE((d1 < d3) == true);

  REQUIRE((d1 > d1) == false);
  REQUIRE((d1 > d2) == true);
  REQUIRE((d1 > d3) == false);

  REQUIRE((d1 <= d1) == true);
  REQUIRE((d1 <= d2) == false);
  REQUIRE((d1 <= d3) == true);

  REQUIRE((d1 >= d1) == true);
  REQUIRE((d1 >= d2) == true);
  REQUIRE((d1 >= d3) == false);
}

TEST_CASE("Increment")
{
  auto d = chrono::duration(59);

  REQUIRE((++d).minutes() == 1);
  REQUIRE((d++).seconds() == 60);
  REQUIRE(d.seconds() == 61);
}

TEST_CASE("Decrement")
{
  auto d = chrono::duration(61);

  REQUIRE((--d).minutes() == 1);
  REQUIRE((d--).seconds() == 60);
  REQUIRE(d.seconds() == 59);
}

TEST_CASE("Addition")
{
  auto d = chrono::duration(30);

  REQUIRE((d + 60).seconds() == 90);
  REQUIRE((d + -60).seconds() == -30);
}

TEST_CASE("Substraction")
{
  auto d = chrono::duration(30);

  REQUIRE((d - 60).seconds() == -30);
  REQUIRE((d - -60).seconds() == 90);
}

TEST_CASE("Addition assignment")
{
  auto d = chrono::duration(30);

  d += 60;
  REQUIRE(d.seconds() == 90);

  d += -60;
  REQUIRE(d.seconds() == 30);
}

TEST_CASE("Substraction assignment")
{
  auto d = chrono::duration(30);

  d -= 60;
  REQUIRE(d.seconds() == -30);

  d -= -60;
  REQUIRE(d.seconds() == 30);
}
