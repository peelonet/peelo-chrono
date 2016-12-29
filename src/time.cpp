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
#include <peelo/chrono/time.hpp>
#include <stdexcept>
#include <ctime>
#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif
#if !defined(BUFSIZ)
#  define BUFSIZ 1024
#endif

namespace peelo
{
  static const int seconds_per_minute = 60;
  static const int seconds_per_hour = seconds_per_minute * 60;
  static const int seconds_per_day = seconds_per_hour * 24;

  static void normalize(int&, int&, int&);
  static std::tm make_tm(const time&);

  time::time(int hour, int minute, int second)
    : m_hour(hour)
    , m_minute(minute)
    , m_second(second)
  {
    if (!is_valid(hour, minute, second))
    {
      throw std::invalid_argument("invalid time value");
    }
  }

  time::time(const time& that)
    : m_hour(that.m_hour)
    , m_minute(that.m_minute)
    , m_second(that.m_second) {}

  time time::now()
  {
    int hour;
    int minute;
    int second;

#if defined(_WIN32)
    SYSTEMTIME lt;

    ::GetLocalTime(&lt);
    hour = lt.wHour;
    minute = lt.wMinute;
    second = lt.wSecond;
#else
    std::time_t ts = std::time(nullptr);
    std::tm* tm = std::localtime(&ts);

    if (!tm)
    {
      throw std::runtime_error("localtime() failed");
    }
    hour = tm->tm_hour;
    minute = tm->tm_min;
    second = tm->tm_sec;
#endif

    return time(hour, minute, second);
  }

  bool time::is_valid(int hour, int minute, int second)
  {
    return (hour >= 0 && hour <= 23)
      && (minute >= 0 && minute <= 59)
      && (second >= 0 && second <= 59);
  }

  std::string time::format(const std::string& format) const
  {
    char buffer[BUFSIZ];
    std::tm tm = make_tm(*this);

    if (std::strftime(buffer, BUFSIZ, format.c_str(), &tm) == 0)
    {
      throw std::runtime_error("strftime() failed");
    }

    return buffer;
  }

  time& time::assign(const time& that)
  {
    return assign(that.m_hour, that.m_minute, that.m_second);
  }

  time& time::assign(int hour, int minute, int second)
  {
    if (!is_valid(hour, minute, second))
    {
      throw std::invalid_argument("invalid time value");
    }
    m_hour = hour;
    m_minute = minute;
    m_second = second;

    return *this;
  }

  bool time::equals(const time& that) const
  {
    return equals(that.m_hour, that.m_minute, that.m_second);
  }

  bool time::equals(int hour, int minute, int second) const
  {
    return hour == m_hour && m_minute == minute && m_second == second;
  }

  int time::compare(const time& that) const
  {
    return compare(that.m_hour, that.m_minute, that.m_second);
  }

  int time::compare(int hour, int minute, int second) const
  {
    if (m_hour != hour)
    {
      return m_hour > hour ? 1 : -1;
    }
    else if (m_minute != minute)
    {
      return m_minute > minute ? 1 : -1;
    }
    else if (m_second != second)
    {
      return m_second > second ? 1 : -1;
    } else {
      return 0;
    }
  }

  time& time::operator++()
  {
    if (++m_second >= 60)
    {
      m_second = 0;
      if (++m_minute >= 60)
      {
        m_minute = 0;
        if (++m_hour >= 24)
        {
          m_hour = 0;
        }
      }
    }

    return *this;
  }

  time time::operator++(int)
  {
    const time return_value(*this);

    if (++m_second >= 60)
    {
      m_second = 0;
      if (++m_minute >= 60)
      {
        m_minute = 0;
        if (++m_hour >= 24)
        {
          m_hour = 0;
        }
      }
    }

    return return_value;
  }

  time& time::operator--()
  {
    if (--m_second < 0)
    {
      m_second = 59;
      if (--m_minute < 0)
      {
        m_minute = 59;
        if (--m_hour < 0)
        {
          m_hour = 23;
        }
      }
    }

    return *this;
  }

  time time::operator--(int)
  {
    const time return_value(*this);

    if (--m_second < 0)
    {
      m_second = 59;
      if (--m_minute < 0)
      {
        m_minute = 59;
        if (--m_hour < 0)
        {
          m_hour = 23;
        }
      }
    }

    return return_value;
  }

  time time::operator+(int seconds) const
  {
    return time(*this) += seconds;
  }

  time time::operator-(int seconds) const
  {
    return time(*this) -= seconds;
  }

  time& time::operator+=(int seconds)
  {
    int second = ((m_hour * 60 * 60) + (m_minute * 60) + m_second) + seconds;
    int minute;
    int hour;

    normalize(second, minute, hour);
    if (!is_valid(hour, minute, second))
    {
      throw std::invalid_argument("invalid time value");
    }
    m_hour = hour;
    m_minute = minute;
    m_second = second;

    return *this;
  }

  time& time::operator-=(int seconds)
  {
    int second = ((m_hour * 60 * 60) + (m_minute * 60) + m_second) - seconds;
    int minute;
    int hour;

    normalize(second, minute, hour);
    if (!is_valid(hour, minute, second))
    {
      throw std::invalid_argument("invalid time value");
    }
    m_hour = hour;
    m_minute = minute;
    m_second = second;

    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const class time& time)
  {
    os << time.format("%T");

    return os;
  }

  static void normalize(int& second, int& minute, int& hour)
  {
    while (second > seconds_per_day)
    {
      second -= seconds_per_day;
    }
    hour = second / seconds_per_hour;
    if (hour > 0)
    {
      second -= hour * seconds_per_hour;
    }
    minute = second / seconds_per_minute;
    if (minute > 0)
    {
      second -= minute * seconds_per_minute;
    }
  }

  static std::tm make_tm(const class time& time)
  {
    std::tm tm = {0};

    tm.tm_year = 90;
    tm.tm_mon = 0;
    tm.tm_mday = 1;
    tm.tm_hour = time.hour();
    tm.tm_min = time.minute();
    tm.tm_sec = time.second();

    return tm;
  }
}
