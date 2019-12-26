/*
 * Copyright (c) 2019, peelo.net
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
#include <cassert>

#include <peelo/chrono/duration.hpp>

using namespace peelo;

static void test_constructor()
{
  const auto d = chrono::duration(60);

  assert(d.seconds() == 60);
  assert(d.minutes() == 1);
  assert(chrono::duration(d).seconds() == 60);
}

static void test_of_days()
{
  assert(chrono::duration::of_days(5).days() == 5);
}

static void test_of_hours()
{
  assert(chrono::duration::of_hours(5).hours() == 5);
}

static void test_of_minutes()
{
  assert(chrono::duration::of_minutes(5).minutes() == 5);
}

static void test_days()
{
  assert(chrono::duration(86400).days() == 1);
  assert(chrono::duration(89000).days() == 1);
  assert(chrono::duration(85400).days() == 0);
  assert(chrono::duration(172800).days() == 2);
}

static void test_hours()
{
  assert(chrono::duration(3600).hours() == 1);
  assert(chrono::duration(3700).hours() == 1);
  assert(chrono::duration(3500).hours() == 0);
  assert(chrono::duration(7200).hours() == 2);
}

static void test_minutes()
{
  assert(chrono::duration(60).minutes() == 1);
  assert(chrono::duration(70).minutes() == 1);
  assert(chrono::duration(50).minutes() == 0);
  assert(chrono::duration(120).minutes() == 2);
}

static void test_seconds()
{
  assert(chrono::duration(5).seconds() == 5);
  assert(chrono::duration(-5).seconds() == -5);
  assert(chrono::duration::of_days(1).seconds() == 86400);
  assert(chrono::duration::of_hours(1).seconds() == 3600);
  assert(chrono::duration::of_minutes(1).seconds() == 60);
}

static void test_assign()
{
  auto d = chrono::duration();

  d.assign(500);
  assert(d.seconds() == 500);

  d.assign(chrono::duration(1500));
  assert(d.seconds() == 1500);

  d = 2000;
  assert(d.seconds() == 2000);

  d = chrono::duration(2500);
  assert(d.seconds() == 2500);
}

static void test_equals()
{
  const auto d1 = chrono::duration(20);
  const auto d2 = chrono::duration(40);

  assert(d1.equals(d1));
  assert(!d1.equals(d2));

  assert((d1 == d1) == true);
  assert((d1 == d2) == false);

  assert((d1 != d1) == false);
  assert((d1 != d2) == true);
}

static void test_compare()
{
  const auto d1 = chrono::duration(1200);
  const auto d2 = chrono::duration(1000);
  const auto d3 = chrono::duration(1400);

  assert(d1.compare(d1) == 0);
  assert(d1.compare(d2) == 1);
  assert(d1.compare(d3) == -1);

  assert((d1 < d1) == false);
  assert((d1 < d2) == false);
  assert((d1 < d3) == true);

  assert((d1 > d1) == false);
  assert((d1 > d2) == true);
  assert((d1 > d3) == false);

  assert((d1 <= d1) == true);
  assert((d1 <= d2) == false);
  assert((d1 <= d3) == true);

  assert((d1 >= d1) == true);
  assert((d1 >= d2) == true);
  assert((d1 >= d3) == false);
}

static void test_inc()
{
  auto d = chrono::duration(59);

  assert((++d).minutes() == 1);
  assert((d++).seconds() == 60);
  assert(d.seconds() == 61);
}

static void test_dec()
{
  auto d = chrono::duration(61);

  assert((--d).minutes() == 1);
  assert((d--).seconds() == 60);
  assert(d.seconds() == 59);
}

static void test_add()
{
  auto d = chrono::duration(30);

  assert((d + 60).seconds() == 90);
  assert((d + - 60).seconds() == -30);
}

static void test_sub()
{
  auto d = chrono::duration(30);

  assert((d - 60).seconds() == -30);
  assert((d - -60).seconds() == 90);
}

static void test_assign_add()
{
  auto d = chrono::duration(30);

  d += 60;
  assert(d.seconds() == 90);

  d += -60;
  assert(d.seconds() == 30);
}

static void test_assign_sub()
{
  auto d = chrono::duration(30);

  d -= 60;
  assert(d.seconds() == -30);

  d -= -60;
  assert(d.seconds() == 30);
}

int main()
{
  test_constructor();
  test_of_days();
  test_of_hours();
  test_of_minutes();
  test_days();
  test_hours();
  test_minutes();
  test_seconds();
  test_assign();
  test_equals();
  test_compare();
  test_inc();
  test_dec();
  test_add();
  test_sub();
  test_assign_add();
  test_assign_sub();
}
