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
   */
  enum class month
  {
    /** January. */
    jan = 1,
    /** February. */
    feb = 2,
    /** March. */
    mar = 3,
    /** April. */
    apr = 4,
    /** May. */
    may = 5,
    /** June. */
    jun = 6,
    /** July. */
    jul = 7,
    /** August. */
    aug = 8,
    /** September. */
    sep = 9,
    /** October. */
    oct = 10,
    /** November. */
    nov = 11,
    /** December. */
    dec = 12
  };

  month& operator++(month&);
  month& operator--(month&);
  month operator++(month&, int);
  month operator--(month&, int);
  month operator+(const month&, int);
  month operator-(const month&, int);
  month& operator+=(month&, int);
  month& operator-=(month&, int);

  std::ostream& operator<<(std::ostream&, const month&);
  std::wostream& operator<<(std::wostream&, const month&);
}

#endif /* !PEELO_CHRONO_MONTH_HPP_GUARD */
