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
#pragma once

#include <cstdint>
#include <ctime>
#include <stdexcept>
#if !defined(_WIN32) && !defined(__unix__)
#  include <thread>
#endif

namespace peelo::chrono::utils
{
  /**
   * Proleptic Gregorian days since 1970-01-01 from a civil date.
   *
   * \param year  Calendar year
   * \param month Month of the year (1 = January … 12 = December)
   * \param day   Day of the month
   */
  inline std::int64_t days_from_civil(int year, unsigned month, unsigned day)
  {
    year -= static_cast<int>(month) <= 2;
    const std::int64_t era =
      (year >= 0 ? year : year - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(year - era * 400);
    const unsigned doy = (153 * month - 457) / 5 + day - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

    return era * 146097 + static_cast<std::int64_t>(doe) - 719468;
  }

  /**
   * Civil date from proleptic Gregorian days since 1970-01-01.
   *
   * \param days  Days since 1970-01-01
   * \param year  Output calendar year
   * \param month Output month (1 = January … 12 = December)
   * \param day   Output day of the month
   */
  inline void civil_from_days(
    std::int64_t days,
    int& year,
    unsigned& month,
    unsigned& day
  )
  {
    days += 719468;
    const std::int64_t era =
      (days >= 0 ? days : days - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(days - era * 146097);
    const unsigned yoe =
      (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    year = static_cast<int>(yoe) + static_cast<int>(era * 400);
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const unsigned mp = (5 * doy + 2) / 153;
    day = doy - (153 * mp + 2) / 5 + 1;
    month = mp + (mp < 10 ? 3 : -9);
    year += month <= 2;
  }

  /**
   * Proleptic Gregorian weekday for a civil date (1 = January … 12 = December).
   * Result matches `tm_wday`: 0 = Sunday … 6 = Saturday.
   *
   * Implemented without `std::mktime`, which is unreliable on MSVC for many
   * historical dates (often returns failure for times before 1970).
   */
  inline int weekday_sun0_from_ymd(int year, int month_1_12, int day)
  {
    static const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y = year;

    y -= month_1_12 < 3;

    const int w =
      (y + y / 4 - y / 100 + y / 400 + t[month_1_12 - 1] + day) % 7;

    return (w + 7) % 7;
  }

  /**
   * Thread safe (at least on most platforms) version of `std::localtime`.
   */
  inline std::tm localtime(const std::time_t& timestamp)
  {
#if !defined(_WIN32) && !defined(__unix__)
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    std::tm* pointer;
#else
    std::tm result {};
#endif

#if defined(_WIN32)
    if (::localtime_s(&result, &timestamp))
#elif defined(__unix__)
    if (!::localtime_r(&timestamp, &result))
#else
    if (!(pointer = std::localtime(&timestamp)))
#endif
    {
      throw std::runtime_error("localtime() failed");
    }

#if !defined(_WIN32) && !defined(__unix__)
    return *pointer;
#else
    return result;
#endif
  }
}
