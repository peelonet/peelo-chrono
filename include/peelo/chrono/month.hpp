/*
 * Copyright (c) 2016, peelo.net
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

#include <iostream>

namespace peelo
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

  /**
   * Increments month by one, wrapping to January if the month is December.
   */
  month& operator++(month&);

  /**
   * Decrements month by one, wrapping to December if the month is January.
   */
  month& operator--(month&);

  /**
   * Increments month by one, wrapping to January if the month is December.
   */
  month operator++(month&, int);

  /**
   * Decrements month by one, wrapping to December if the month is January.
   */
  month operator--(month&, int);

  /**
   * Increments month by given amount of months.
   */
  month operator+(const month&, int);

  /**
   * Decrements month by given amount of months.
   */
  month operator-(const month&, int);

  /**
   * Adds given number of months into the month.
   */
  month& operator+=(month&, int);

  /**
   * Substracts given number of months from the month.
   */
  month& operator-=(month&, int);

  /**
   * Writes name of the month (in English) into the stream.
   */
  std::ostream& operator<<(std::ostream&, const month&);
}

#endif /* !PEELO_CHRONO_MONTH_HPP_GUARD */
