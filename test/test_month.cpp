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

#include "peelo/chrono/month.hpp"

using namespace peelo;

TEST_CASE("Conversion to integer")
{
  REQUIRE(static_cast<int>(chrono::month::jan) == 0);
  REQUIRE(static_cast<int>(chrono::month::dec) == 11);
}

TEST_CASE("Addition and substraction")
{
  REQUIRE(chrono::month::jan + 3 == chrono::month::apr);
  REQUIRE(chrono::month::sep - 2 == chrono::month::jul);
  REQUIRE(chrono::month::jan + 13 == chrono::month::feb);
  REQUIRE(chrono::month::nov - 13 == chrono::month::oct);
}

TEST_CASE("Conversion to string")
{
  REQUIRE(chrono::to_string(chrono::month::jan) == "January");
  REQUIRE(chrono::to_string(chrono::month::oct) == "October");

  REQUIRE(chrono::to_u32string(chrono::month::jan) == U"January");
  REQUIRE(chrono::to_u32string(chrono::month::oct) == U"October");
}
