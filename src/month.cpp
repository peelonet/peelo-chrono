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
#include <peelo/chrono/month.hpp>

namespace peelo
{
  month& operator++(month& original)
  {
    return original += 1;
  }

  month& operator--(month& original)
  {
    return original -= 1;
  }

  month operator++(month& original, int)
  {
    const month return_value = original;

    original += 1;

    return return_value;
  }

  month operator--(month& original, int)
  {
    const month return_value = original;

    original -= 1;

    return return_value;
  }

  month operator+(const month& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result < 12 ? result + 1 : 1;
      }

      return static_cast<month>(result);
    }

    return original - (-delta);
  }

  month operator-(const month& original, int delta)
  {
    if (delta >= 0)
    {
      int result = static_cast<int>(original);

      for (int i = 0; i < delta; ++i)
      {
        result = result > 1 ? result - 1 : 12;
      }

      return static_cast<month>(result);
    }

    return original + (-delta);
  }

  month& operator+=(month& original, int delta)
  {
    int result = static_cast<int>(original);

    for (int i = 0; i < delta; ++i)
    {
      result = result < 12 ? result + 1 : 1;
    }

    return original = static_cast<month>(result);
  }

  month& operator-=(month& original, int delta)
  {
    int result = static_cast<int>(original);

    for (int i = 0; i < delta; ++i)
    {
      result = result > 1 ? result - 1 : 12;
    }

    return original = static_cast<month>(result);
  }

  std::ostream& operator<<(std::ostream& os, const month& m)
  {
    switch (m)
    {
      case month::jan:
        os << "January";
        break;

      case month::feb:
        os << "February";
        break;

      case month::mar:
        os << "March";
        break;

      case month::apr:
        os << "April";
        break;

      case month::may:
        os << "May";
        break;

      case month::jun:
        os << "June";
        break;

      case month::jul:
        os << "July";
        break;

      case month::aug:
        os << "August";
        break;

      case month::sep:
        os << "September";
        break;

      case month::oct:
        os << "October";
        break;

      case month::nov:
        os << "November";
        break;

      case month::dec:
        os << "December";
        break;
    }

    return os;
  }

  std::wostream& operator<<(std::wostream& os, const month& m)
  {
    switch (m)
    {
      case month::jan:
        os << L"January";
        break;

      case month::feb:
        os << L"February";
        break;

      case month::mar:
        os << L"March";
        break;

      case month::apr:
        os << L"April";
        break;

      case month::may:
        os << L"May";
        break;

      case month::jun:
        os << L"June";
        break;

      case month::jul:
        os << L"July";
        break;

      case month::aug:
        os << L"August";
        break;

      case month::sep:
        os << L"September";
        break;

      case month::oct:
        os << L"October";
        break;

      case month::nov:
        os << L"November";
        break;

      case month::dec:
        os << L"December";
        break;
    }

    return os;
  }
}
