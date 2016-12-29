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
#ifndef PEELO_CHRONO_WEEKDAY_HPP_GUARD
#define PEELO_CHRONO_WEEKDAY_HPP_GUARD

#include <iostream>

namespace peelo
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

  weekday& operator++(weekday&);
  weekday& operator--(weekday&);
  weekday operator++(weekday&, int);
  weekday operator--(weekday&, int);
  weekday operator+(const weekday&, int);
  weekday operator-(const weekday&, int);
  weekday& operator+=(weekday&, int);
  weekday& operator-=(weekday&, int);

  std::ostream& operator<<(std::ostream&, const weekday&);
}

#endif /* !PEELO_CHRONO_WEEKDAY_HPP_GUARD */
