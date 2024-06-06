/*
 * Copyright (c) 2016-2024, peelo.net
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

#include <chrono>
#include <ctime>
#include <stdexcept>
#if !defined(BUFSIZ)
#  define BUFSIZ 1024
#endif

#include <peelo/chrono/duration.hpp>
#include <peelo/chrono/month.hpp>
#include <peelo/chrono/weekday.hpp>

namespace peelo::chrono
{
  /**
   * Gregorian calendar based date value.
   */
  class date
  {
  public:
    /**
     * Constructs a date from given values.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \throw std::invalid_argument If given values do not construct a valid
     *                              date
     */
    explicit date(
      int year = 1900,
      const enum month& month = month::jan,
      int day = 1
    )
      : m_year(year)
      , m_month(month)
      , m_day(day)
    {
      if (!is_valid(year, month, day))
      {
        throw std::invalid_argument("invalid date value");
      }
    }

    /**
     * Copy constructor.
     */
    date(const date&) = default;

    /**
     * Move constructor.
     */
    date(date&&) = default;

    /**
     * Returns current date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date today()
    {
      const auto now = std::chrono::system_clock::now();
      const auto ts = std::chrono::system_clock::to_time_t(now);
      const auto tm = std::localtime(&ts);

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

    /**
     * Returns yesterdays date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date yesterday()
    {
      const auto now = today();

      if (now.m_day > 1)
      {
        return date(now.m_year, now.m_month, now.m_day - 1);
      }
      else if (now.m_month == month::jan)
      {
        return date(now.m_year - 1, month::dec, 31);
      }

      return date(
        now.m_year,
        now.m_month - 1,
        days_in_month(now.m_month - 1, is_leap_year(now.m_year))
      );
    }

    /**
     * Returns tomorrows date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date tomorrow()
    {
      const auto now = today();

      if (now.m_day == now.days_in_month())
      {
        if (now.m_month == month::dec)
        {
          return date(now.m_year + 1, month::jan, 1);
        } else {
          return date(now.m_year, now.m_month + 1, 1);
        }
      }

      return date(now.m_year, now.m_month, now.m_day + 1);
    }

    /**
     * Constructs date value from UNIX timestamp.
     */
    static date timestamp(long timestamp)
    {
      auto ts = static_cast<std::time_t>(timestamp);
      auto tm = std::localtime(&ts);

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

    /**
     * Tests whether given values are a valid date.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      A boolean flag indicating whether an valid date can be
     *              constructed from given values
     */
    static inline bool is_valid(int year, const enum month& month, int day)
    {
      return day > 0 && day <= days_in_month(month, is_leap_year(year));
    }

    /**
     * Returns year of the date.
     */
    inline int year() const
    {
      return m_year;
    }

    /**
     * Returns month of the year.
     */
    inline const enum month& month() const
    {
      return m_month;
    }

    /**
     * Returns day of the month (from 1 to 31) of the date.
     */
    inline int day() const
    {
      return m_day;
    }

    /**
     * Returns week of day for this date.
     *
     * \throw runtime_error If day of the week cannot be determined for some
     *                      system specific reason
     */
    weekday day_of_week() const
    {
      auto tm = make_tm(*this);

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

    /**
     * Returns the day of the year (from 1 to 365 or 366 on leap years) for
     * this date.
     */
    int day_of_year() const
    {
      const bool leap_year = is_leap_year();
      int result = 0;

      for (enum month i = month::jan; i < m_month; ++i)
      {
        result += days_in_month(i, leap_year);
      }

      return result + m_day;
    }

    /**
     * Returns the number of days in the month (28-31) for this date.
     */
    inline int days_in_month() const
    {
      return days_in_month(m_month, is_leap_year());
    }

    /**
     * Returns the number of days in the month (28-31) for given month.
     *
     * \param month     Month to retrieve number of days for
     * \param leap_year Whether the year is leap year or not
     */
    static int days_in_month(const enum month& month, bool leap_year)
    {
      switch (month)
      {
        case month::apr:
        case month::jun:
        case month::sep:
        case month::nov:
          return 30;

        case month::jan:
        case month::mar:
        case month::may:
        case month::jul:
        case month::aug:
        case month::oct:
        case month::dec:
          return 31;

        case month::feb:
        default:
          return leap_year ? 29 : 28;
      }
    }

    /**
     * Returns the number of days in the year (365 or 366) for this date.
     */
    inline int days_in_year() const
    {
      return days_in_year(m_year);
    }

    /**
     * Returns the number of days in the year (365 or 366) for the given year.
     *
     * \param year Year to retrieve number of days for
     */
    static inline int days_in_year(int year)
    {
      return is_leap_year(year) ? 366 : 365;
    }

    /**
     * Returns <code>true</code> if the year represented by the date is a leap
     * year.
     */
    inline bool is_leap_year() const
    {
      return is_leap_year(m_year);
    }

    /**
     * Returns <code>true</code> if the given year is leap year.
     *
     * \param year Year to test for leap year
     */
    static inline bool is_leap_year(int year)
    {
      return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    /**
     * Calculates UNIX timestamp from date.
     */
    std::int64_t timestamp() const
    {
      static const int seconds_per_day = 86400;
      static const int days_before_month[12] =
      {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
      };
      // Compute days in a year.
      auto days = (
        (static_cast<std::int64_t>(m_day) - 1) +
        (days_before_month[static_cast<int>(m_month) - 1])
      );

      // Leap year adjustment.
      if (m_month > month::jan && is_leap_year())
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

    /**
     * Uses strftime() function to format the date into a string.
     */
    std::string format(const std::string& format) const
    {
      char buffer[BUFSIZ];
      auto tm = make_tm(*this);

      if (std::strftime(buffer, BUFSIZ, format.c_str(), &tm) == 0)
      {
        throw std::runtime_error("strftime() failed");
      }

      return buffer;
    }

    /**
     * Assigns values from another date into this one.
     *
     * \param that Other date to copy values from
     */
    inline date& assign(const date& that)
    {
      return assign(that.m_year, that.m_month, that.m_day);
    }

    /**
     * Replaces values of the date with given values.
     *
     * \param year  New year of the date
     * \param month New month of the year
     * \param day   New day of the month
     * \throw std::invalid_argument If given values do not construct a valid
     *                              date
     */
    date& assign(int year, const enum month& month, int day)
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

    /**
     * Assignment operator.
     */
    date& operator=(const date&) = default;

    /**
     * Move operator.
     */
    date& operator=(date&&) = default;

    /**
     * Tests whether two dates are equal or not.
     *
     * \param that Another date to compare this one with
     * \return     A boolean flag indicating whether the dates are equal or not
     */
    inline bool equals(const date& that) const
    {
      return equals(that.m_year, that.m_month, that.m_day);
    }

    /**
     * Tests whether this date has given values.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      A boolean flag indicating whether this date has given
     *              values or not
     */
    inline bool equals(int year, const enum month& month, int day) const
    {
      return m_year == year && m_month == month && m_day == day;
    }

    /**
     * Equality testing operator.
     */
    inline bool operator==(const date& that) const
    {
      return equals(that);
    }

    /**
     * Non-equality testing operator.
     */
    inline bool operator!=(const date& that) const
    {
      return !equals(that);
    }

    /**
     * Compares two dates against each other.
     *
     * \param that Other date to compare this one against
     * \return     Integer value indicating comparison result
     */
    inline int compare(const date& that) const
    {
      return compare(that.m_year, that.m_month, that.m_day);
    }

    /**
     * Compares date against given values.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      Integer value indicating comparison result
     */
    int compare(int year, const enum month& month, int day) const
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

    /**
     * Comparison operator.
     */
    inline bool operator<(const date& that) const
    {
      return compare(that) < 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>(const date& that) const
    {
      return compare(that) > 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<=(const date& that) const
    {
      return compare(that) <= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>=(const date& that) const
    {
      return compare(that) >= 0;
    }

    /**
     * Increments date by one day.
     */
    date& operator++()
    {
      if (m_day == days_in_month())
      {
        m_day = 1;
        if (m_month == month::dec)
        {
          m_month = month::jan;
          ++m_year;
        } else {
          ++m_month;
        }
      } else {
        ++m_day;
      }

      return *this;
    }

    /**
     * Increments date by one day.
     */
    date operator++(int)
    {
      const date return_value = date(*this);

      if (m_day == days_in_month())
      {
        m_day = 1;
        if (m_month == month::dec)
        {
          m_month = month::jan;
          ++m_year;
        } else {
          ++m_month;
        }
      } else {
        ++m_day;
      }

      return return_value;
    }

    /**
     * Decrements date by one day.
     */
    date& operator--()
    {
      if (m_day > 1)
      {
        --m_day;
      }
      else if (m_month == month::jan)
      {
        --m_year;
        m_month = month::dec;
        m_day = 31;
      } else {
        m_day = days_in_month(--m_month, m_year);
      }

      return *this;
    }

    /**
     * Decrements date by one day.
     */
    date operator--(int)
    {
      const date return_value = date(*this);

      if (m_day > 1)
      {
        --m_day;
      }
      else if (m_month == month::jan)
      {
        --m_year;
        m_month = month::dec;
        m_day = 31;
      } else {
        m_day = days_in_month(--m_month, m_year);
      }

      return return_value;
    }

    /**
     * Adds given number of days to the date and returns result.
     */
    date operator+(int days) const
    {
      auto tm = make_tm(*this);

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

    /**
     * Substracts given number of days from the date and returns result.
     */
    date operator-(int days) const
    {
      auto tm = make_tm(*this);

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

    /**
     * Adds given number of days to the date.
     */
    date& operator+=(int days)
    {
      auto tm = make_tm(*this);

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

    /**
     * Substracts given number of days from the date.
     */
    date& operator-=(int days)
    {
      auto tm = make_tm(*this);

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

    /**
     * Returns the difference between two dates.
     */
    duration operator-(const date& that) const
    {
      auto tm1 = make_tm(*this);
      auto tm2 = make_tm(that);
      const auto time1 = std::mktime(&tm1);
      const auto time2 = std::mktime(&tm2);
      const auto difference = std::difftime(time1, time2);

      return duration(difference);
    }

  private:
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

  private:
    /** Year of the date. */
    int m_year;
    /** Month of the year. */
    enum month m_month;
    /** Day of the month. */
    int m_day;
  };

  /**
   * Returns textual presentation of the date into the stream in RFC 2822
   * compliant format.
   */
  inline std::string to_string(const class date& date)
  {
    return date.format("%d %b %Y");
  }
}
