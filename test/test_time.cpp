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

#include "peelo/chrono/time.hpp"

using namespace peelo;

TEST_CASE("Basic accessor methods")
{
  const chrono::time time(13, 40, 25);

  REQUIRE(time.hour() == 13);
  REQUIRE(time.minute() == 40);
  REQUIRE(time.second() == 25);
}

TEST_CASE("Equality testing, incrementation and decrementation")
{
  chrono::time time(23, 59, 58);

  REQUIRE(time.equals(23, 59, 58));

  ++time;
  REQUIRE(time.equals(23, 59, 59));
  ++time;
  REQUIRE(time.equals(0, 0, 0));
  --time;
  REQUIRE(time.equals(23, 59, 59));

  time -= 59;
  REQUIRE(time.equals(23, 59, 0));
  REQUIRE(time.compare(23, 59, 59) < 0);
  REQUIRE(time.compare(23, 58, 59) > 0);

  time -= 3600;
  REQUIRE(time.equals(22, 59, 0));
}

TEST_CASE("Formatting")
{
  const chrono::time time(22, 59, 0);

  REQUIRE(time.format("%H %M %S") == "22 59 00");
  REQUIRE(chrono::to_string(time) == "22:59:00");
}

TEST_CASE("Validation")
{
  const auto now = chrono::time::now();

  REQUIRE(chrono::time::is_valid(now.hour(), now.minute(), now.second()));
}
