/*
 * Copyright (c) 2016-2019, peelo.net
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
#ifndef PEELO_CHRONO_WEEKDAY_HPP_GUARD
#define PEELO_CHRONO_WEEKDAY_HPP_GUARD

#include <string>

namespace peelo::chrono
{
  /**
   * Enumerated type which represents day of the week, where Sunday is the
   * first day of the week.
   */
  enum class weekday
  {
    /** Sunday. */
    sun = 0,
    /** Monday. */
    mon = 1,
    /** Tuesday. */
    tue = 2,
    /** Wednesday. */
    wed = 3,
    /** Thursday. */
    thu = 4,
    /** Friday. */
    fri = 5,
    /** Saturday. */
    sat = 6
  };

  weekday operator-(const weekday&, int);
  weekday& operator-=(weekday&, int);

  /**
   * Increments weekday by given amount of days.
   */
  inline weekday operator+(const weekday& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result < 6 ? result + 1 : 0;
      }

      return static_cast<weekday>(result);
    }

    return original - (-delta);
  }

  /**
   * Decrements weekday by given amount of days.
   */
  inline weekday operator-(const weekday& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result > 0 ? result - 1 : 6;
      }

      return static_cast<weekday>(result);
    }

    return original + (-delta);
  }

  /**
   * Adds given number of days into the weekday.
   */
  inline weekday& operator+=(weekday& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result < 6 ? result + 1 : 0;
      }

      return original = static_cast<weekday>(result);
    }

    return original -= (-delta);
  }

  /**
   * Substracts given number of days from the weekday.
   */
  inline weekday& operator-=(weekday& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result > 0 ? result - 1 : 6;
      }

      return original = static_cast<weekday>(result);
    }

    return original += (-delta);
  }

  /**
   * Increments weekday by one, wrapping to Sunday if the weekday is Monday.
   */
  inline weekday& operator++(weekday& original)
  {
    return original += 1;
  }

  /**
   * Decrements weekday by one, wrapping to Monday if the weekday is Sunday.
   */
  inline weekday& operator--(weekday& original)
  {
    return original -= 1;
  }

  /**
   * Increments weekday by one, wrapping to Sunday if the weekday is Monday.
   */
  inline weekday operator++(weekday& original, int)
  {
    const weekday return_value = original;

    original += 1;

    return return_value;
  }

  /**
   * Decrements weekday by one, wrapping to Monday if the weekday is Sunday.
   */
  inline weekday operator--(weekday& original, int)
  {
    const weekday return_value = original;

    original -= 1;

    return return_value;
  }

  /**
   * Returns full name of the weekday (in English) to the stream.
   */
  inline std::string to_string(const weekday& day)
  {
    switch (day)
    {
      case weekday::sun:
        return "Sunday";

      case weekday::mon:
        return "Monday";

      case weekday::tue:
        return "Tuesday";

      case weekday::wed:
        return "Wednesday";

      case weekday::thu:
        return "Thursday";

      case weekday::fri:
        return "Friday";

      case weekday::sat:
        return "Saturday";
    }

    return "Unknown";
  }
}

#endif /* !PEELO_CHRONO_WEEKDAY_HPP_GUARD */
