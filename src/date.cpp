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
#include <peelo/chrono/date.hpp>
#include <ctime>
#include <stdexcept>
#if !defined(BUFSIZ)
#  define BUFSIZ 1024
#endif

namespace peelo
{
  static const int seconds_per_day = 86400;

  static std::tm make_tm(const date&);

  date::date(int year, const enum month& month, int day)
    : m_year(year)
    , m_month(month)
    , m_day(day)
  {
    if (!is_valid(year, month, day))
    {
      throw std::invalid_argument("invalid date value");
    }
  }

  date::date(const date& that)
    : m_year(that.m_year)
    , m_month(that.m_month)
    , m_day(that.m_day) {}

  bool date::is_valid(int year, const enum month& month, int day)
  {
    return day > 0 && day <= days_in_month(month, is_leap_year(year));
  }

  date date::today()
  {
    std::time_t ts = std::time(nullptr);
    std::tm* tm = std::localtime(&ts);

    if (!tm || tm->tm_mon < 0 || tm->tm_mon > 11)
    {
      throw std::runtime_error("localtime() failed");
    }

    return date(
      tm->tm_year + 1900,
      static_cast<enum month>(tm->tm_mon),
      tm->tm_mday
    );
  }

  date date::yesterday()
  {
    const date now = today();

    if (now.m_day > 1)
    {
      return date(now.m_year, now.m_month, now.m_day - 1);
    }
    else if (now.m_month == peelo::month::jan)
    {
      return date(now.m_year - 1, peelo::month::dec, 31);
    }

    return date(
      now.m_year,
      now.m_month - 1,
      days_in_month(now.m_month - 1, is_leap_year(now.m_year))
    );
  }

  date date::tomorrow()
  {
    const class date now = today();

    if (now.m_day == now.days_in_month())
    {
      if (now.m_month == peelo::month::dec)
      {
        return date(now.m_year + 1, peelo::month::jan, 1);
      } else {
        return date(now.m_year, now.m_month + 1, 1);
      }
    }

    return date(now.m_year, now.m_month, now.m_day + 1);
  }

  date date::timestamp(long timestamp)
  {
    std::time_t ts = static_cast<std::time_t>(timestamp);
    std::tm* tm = std::localtime(&ts);

    if (!tm || tm->tm_mon < 0 || tm->tm_mon > 11)
    {
      throw std::runtime_error("localtime() failed");
    }

    return date(
      tm->tm_year + 1900,
      static_cast<enum month>(tm->tm_mon),
      tm->tm_mday
    );
  }

  weekday date::day_of_week() const
  {
    std::tm tm = make_tm(*this);

    if (std::mktime(&tm) == -1)
    {
      throw std::runtime_error("mktime() failed");
    }
    else if (tm.tm_wday < 0 && tm.tm_wday > 6)
    {
      throw std::runtime_error("unable to determine day of week");
    }

    return static_cast<enum weekday>(tm.tm_wday);
  }

  int date::day_of_year() const
  {
    const bool leap_year = is_leap_year();
    int result = 0;

    for (enum month i = peelo::month::jan; i < m_month; ++i)
    {
      result += days_in_month(i, leap_year);
    }

    return result + m_day;
  }

  int date::days_in_month() const
  {
    return days_in_month(m_month, is_leap_year());
  }

  int date::days_in_month(const enum month& month, bool leap_year)
  {
    switch (month)
    {
      case peelo::month::apr:
      case peelo::month::jun:
      case peelo::month::sep:
      case peelo::month::nov:
        return 30;

      case peelo::month::jan:
      case peelo::month::mar:
      case peelo::month::may:
      case peelo::month::jul:
      case peelo::month::aug:
      case peelo::month::oct:
      case peelo::month::dec:
        return 31;

      case peelo::month::feb:
        return leap_year ? 29 : 28;
    }

    throw std::runtime_error("unrecognized month");
  }

  int date::days_in_year() const
  {
    return days_in_year(m_year);
  }

  int date::days_in_year(int year)
  {
    return is_leap_year(year) ? 366 : 365;
  }

  bool date::is_leap_year() const
  {
    return is_leap_year(m_year);
  }

  bool date::is_leap_year(int year)
  {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

  long date::timestamp() const
  {
    static const int days_before_month[12] =
    {
      0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    // Compute days in a year.
    long days = (m_day - 1) + (days_before_month[static_cast<int>(m_month) - 1]);

    // Leap year adjustment.
    if (m_month > peelo::month::jan && is_leap_year())
    {
      ++days;
    }

    // Compute days from other years.
    if (m_year > 1970)
    {
      for (int year = 1970; year < m_year; ++year)
      {
        days += days_in_year(year);
      }
    }
    else if (m_year < 1970)
    {
      for (int year = 1969; year >= m_year; --year)
      {
        days -= days_in_year(year);
      }
    }

    return days * seconds_per_day;
  }

  std::string date::format(const std::string& format) const
  {
    char buffer[BUFSIZ];
    std::tm tm = make_tm(*this);

    if (std::strftime(buffer, BUFSIZ, format.c_str(), &tm) == 0)
    {
      throw std::runtime_error("strftime() failed");
    }

    return buffer;
  }

  date& date::assign(const date& that)
  {
    return assign(that.m_year, that.m_month, that.m_day);
  }

  date& date::assign(int year, const enum month& month, int day)
  {
    if (!is_valid(year, month, day))
    {
      throw std::invalid_argument("invalid date value");
    }
    m_year = year;
    m_month = month;
    m_day = day;

    return *this;
  }

  bool date::equals(const date& that) const
  {
    return equals(that.m_year, that.m_month, that.m_day);
  }

  bool date::equals(int year, const enum month& month, int day) const
  {
    return m_year == year && m_month == month && m_day == day;
  }

  int date::compare(const date& that) const
  {
    return compare(that.m_year, that.m_month, that.m_day);
  }

  int date::compare(int year, const enum month& month, int day) const
  {
    if (m_year != year)
    {
      return m_year > year ? 1 : -1;
    }
    else if (m_month != month)
    {
      return m_month > month ? 1 : -1;
    }
    else if (m_day != day)
    {
      return m_day > day ? 1 : -1;
    } else {
      return 0;
    }
  }

  date& date::operator++()
  {
    if (m_day == days_in_month())
    {
      m_day = 1;
      if (m_month == peelo::month::dec)
      {
        m_month = peelo::month::jan;
        ++m_year;
      } else {
        ++m_month;
      }
    } else {
      ++m_day;
    }

    return *this;
  }

  date date::operator++(int)
  {
    const date return_value = date(*this);

    if (m_day == days_in_month())
    {
      m_day = 1;
      if (m_month == peelo::month::dec)
      {
        m_month = peelo::month::jan;
        ++m_year;
      } else {
        ++m_month;
      }
    } else {
      ++m_day;
    }

    return return_value;
  }

  date& date::operator--()
  {
    if (m_day > 1)
    {
      --m_day;
    }
    else if (m_month == peelo::month::jan)
    {
      --m_year;
      m_month = peelo::month::dec;
      m_day = 31;
    } else {
      m_day = days_in_month(--m_month, m_year);
    }

    return *this;
  }

  date date::operator--(int)
  {
    const date return_value = date(*this);

    if (m_day > 1)
    {
      --m_day;
    }
    else if (m_month == peelo::month::jan)
    {
      --m_year;
      m_month = peelo::month::dec;
      m_day = 31;
    } else {
      m_day = days_in_month(--m_month, m_year);
    }

    return return_value;
  }

  date date::operator+(int days) const
  {
    std::tm tm = make_tm(*this);

    if (days > 0)
    {
      tm.tm_mday += days;
    } else {
      tm.tm_mday -= -days;
    }
    if (std::mktime(&tm) == -1 || tm.tm_mon < 0 || tm.tm_mon > 11)
    {
      throw std::runtime_error("mktime() failed");
    }

    return date(
      tm.tm_year + 1900,
      static_cast<enum month>(tm.tm_mon),
      tm.tm_mday
    );
  }

  date date::operator-(int days) const
  {
    std::tm tm = make_tm(*this);

    if (days > 0)
    {
      tm.tm_mday -= days;
    } else {
      tm.tm_mday += -days;
    }
    if (std::mktime(&tm) == -1 || tm.tm_mon < 0 || tm.tm_mon > 11)
    {
      throw std::runtime_error("mktime() failed");
    }

    return date(
      tm.tm_year + 1900,
      static_cast<enum month>(tm.tm_mon),
      tm.tm_mday
    );
  }

  date& date::operator+=(int days)
  {
    std::tm tm = make_tm(*this);

    if (days > 0)
    {
      tm.tm_mday += days;
    } else {
      tm.tm_mday -= -days;
    }
    if (std::mktime(&tm) == -1 || tm.tm_mon < 0 || tm.tm_mon > 11)
    {
      throw std::runtime_error("mktime() failed");
    }

    return assign(
      tm.tm_year - 1900,
      static_cast<enum month>(tm.tm_mon),
      tm.tm_mday
    );
  }

  date& date::operator-=(int days)
  {
    std::tm tm = make_tm(*this);

    if (days > 0)
    {
      tm.tm_mday -= days;
    } else {
      tm.tm_mday += -days;
    }
    if (std::mktime(&tm) == -1 || tm.tm_mon < 0 || tm.tm_mon > 11)
    {
      throw std::runtime_error("mktime() failed");
    }

    return assign(
      tm.tm_year - 1900,
      static_cast<enum month>(tm.tm_mon),
      tm.tm_mday
    );
  }

  int date::operator-(const date& that) const
  {
    std::tm tm1 = make_tm(*this);
    std::tm tm2 = make_tm(that);
    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);
    std::time_t difference = std::difftime(time1, time2);

    return difference / seconds_per_day;
  }

  std::ostream& operator<<(std::ostream& os, const class date& date)
  {
    int year = date.year();
    const int month = static_cast<int>(date.month()) + 1;
    const int day = date.day();

    if (year < 0)
    {
      year = -year - 1;
      os << '-';
    }
    if (year < 1000)
    {
      os << '0';
      if (year < 100)
      {
        os << '0';
        if (year < 10)
        {
          os << '0';
        }
      }
    }
    os << year << '-';
    if (month < 10)
    {
      os << '0';
    }
    os << month << '-';
    if (day < 10)
    {
      os << '0';
    }
    os << day;

    return os;
  }

  std::wostream& operator<<(std::wostream& os, const class date& date)
  {
    int year = date.year();
    const int month = static_cast<int>(date.month()) + 1;
    const int day = date.day();

    if (year < 0)
    {
      year = -year - 1;
      os << L'-';
    }
    if (year < 1000)
    {
      os << L'0';
      if (year < 100)
      {
        os << L'0';
        if (year < 10)
        {
          os << L'0';
        }
      }
    }
    os << year << L'-';
    if (month < 10)
    {
      os << L'0';
    }
    os << month << L'-';
    if (day < 10)
    {
      os << L'0';
    }
    os << day;

    return os;
  }

  static std::tm make_tm(const class date& date)
  {
    std::tm tm = {0};

    tm.tm_year = date.year() - 1900;
    tm.tm_mon = static_cast<int>(date.month());
    tm.tm_mday = date.day();
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    return tm;
  }
}
