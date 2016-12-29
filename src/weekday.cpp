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
#include <peelo/chrono/weekday.hpp>

namespace peelo
{
  weekday& operator++(weekday& original)
  {
    return original += 1;
  }

  weekday& operator--(weekday& original)
  {
    return original -= 1;
  }

  weekday operator++(weekday& original, int)
  {
    const weekday return_value = original;

    original += 1;

    return return_value;
  }

  weekday operator--(weekday& original, int)
  {
    const weekday return_value = original;

    original -= 1;

    return return_value;
  }

  weekday operator+(const weekday& original, int delta)
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

  weekday operator-(const weekday& original, int delta)
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

  weekday& operator+=(weekday& original, int delta)
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

  weekday& operator-=(weekday& original, int delta)
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

  std::ostream& operator<<(std::ostream& os, const weekday& day)
  {
    switch (day)
    {
      case weekday::sun:
        os << "Sunday";
        break;

      case weekday::mon:
        os << "Monday";
        break;

      case weekday::tue:
        os << "Tuesday";
        break;

      case weekday::wed:
        os << "Wednesday";
        break;

      case weekday::thu:
        os << "Thursday";
        break;

      case weekday::fri:
        os << "Friday";
        break;

      case weekday::sat:
        os << "Saturday";
        break;
    }

    return os;
  }
}
