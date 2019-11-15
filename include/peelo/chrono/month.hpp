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
#ifndef PEELO_CHRONO_MONTH_HPP_GUARD
#define PEELO_CHRONO_MONTH_HPP_GUARD

#include <string>

namespace peelo::chrono
{
  /**
   * Enum type which represents month on Gregorian calendar.
   *
   * <b>Note:</b> Months are zero indexed, so January is month 0.
   */
  enum class month
  {
    /** January. */
    jan = 0,
    /** February. */
    feb = 1,
    /** March. */
    mar = 2,
    /** April. */
    apr = 3,
    /** May. */
    may = 4,
    /** June. */
    jun = 5,
    /** July. */
    jul = 6,
    /** August. */
    aug = 7,
    /** September. */
    sep = 8,
    /** October. */
    oct = 9,
    /** November. */
    nov = 10,
    /** December. */
    dec = 11
  };

  month operator-(const month&, int);
  month& operator-=(month&, int);

  /**
   * Increments month by given amount of months.
   */
  inline month operator+(const month& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result < 11 ? result + 1 : 0;
      }

      return static_cast<month>(result);
    }

    return original - (-delta);
  }

  /**
   * Decrements month by given amount of months.
   */
  inline month operator-(const month& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result > 0 ? result - 1 : 11;
      }

      return static_cast<month>(result);
    }

    return original + (-delta);
  }

  /**
   * Adds given number of months into the month.
   */
  inline month& operator+=(month& original, int delta)
  {
    int result = static_cast<int>(original);

    for (int i = 0; i < delta; ++i)
    {
      result = result < 11 ? result + 1 : 0;
    }

    return original = static_cast<month>(result);
  }

  /**
   * Substracts given number of months from the month.
   */
  inline month& operator-=(month& original, int delta)
  {
    int result = static_cast<int>(original);

    for (int i = 0; i < delta; ++i)
    {
      result = result > 0 ? result - 1 : 11;
    }

    return original = static_cast<month>(result);
  }

  /**
   * Increments month by one, wrapping to January if the month is December.
   */
  inline month& operator++(month& original)
  {
    return original += 1;
  }

  /**
   * Decrements month by one, wrapping to December if the month is January.
   */
  inline month& operator--(month& original)
  {
    return original -= 1;
  }

  /**
   * Increments month by one, wrapping to January if the month is December.
   */
  inline month operator++(month& original, int)
  {
    const month return_value = original;

    original += 1;

    return return_value;
  }

  /**
   * Decrements month by one, wrapping to December if the month is January.
   */
  inline month operator--(month& original, int)
  {
    const month return_value = original;

    original -= 1;

    return return_value;
  }

  /**
   * Returns name of the month (in English) into the stream.
   */
  inline std::string to_string(const enum month& month)
  {
    switch (month)
    {
      case month::jan:
        return "January";

      case month::feb:
        return "February";

      case month::mar:
        return "March";

      case month::apr:
        return "April";

      case month::may:
        return "May";

      case month::jun:
        return "June";

      case month::jul:
        return "July";

      case month::aug:
        return "August";

      case month::sep:
        return "September";

      case month::oct:
        return "October";

      case month::nov:
        return "November";

      case month::dec:
        return "December";
    }

    return "Unknown";
  }
}

#endif /* !PEELO_CHRONO_MONTH_HPP_GUARD */
