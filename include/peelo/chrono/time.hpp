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
#include <string>

#if !defined(BUFSIZ)
# define BUFSIZ 1024
#endif

namespace peelo::chrono
{
  /**
   * Time value based on 24 hour clock.
   */
  class time
  {
  public:
    /**
     * Constructs new instance of time from given values.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \throw std::invalid_argument If given values cannot be used to construct
     *                              valid time
     */
    explicit time(int hour = 0, int minute = 0, int second = 0)
      : m_hour(hour)
      , m_minute(minute)
      , m_second(second)
    {
      if (!is_valid(hour, minute, second))
      {
        throw std::invalid_argument("invalid time value");
      }
    }

    /**
     * Copy constructor.
     */
    time(const time&) = default;

    /**
     * Move constructor.
     */
    time(time&&) = default;

    /**
     * Returns current time based on system clock.
     *
     * \throw std::runtime_error If current time cannot be extracted from the
     *                           system for some reason
     */
    static time now()
    {
      const auto now = std::chrono::system_clock::now();
      const auto ts = std::chrono::system_clock::to_time_t(now);
      const auto tm = std::localtime(&ts);

      if (!tm)
      {
        throw std::runtime_error("localtime() failed");
      }

      return time(tm->tm_hour, tm->tm_min, tm->tm_sec);
    }

    /**
     * Tests whether given values are valid time.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       A boolean flag indicating whether an valid time can be
     *               constructed from given values
     */
    static inline bool is_valid(int hour, int minute, int second)
    {
      return (hour >= 0 && hour <= 23)
        && (minute >= 0 && minute <= 59)
        && (second >= 0 && second <= 59);
    }

    /**
     * Returns hour of the day (from 0 to 23).
     */
    inline int hour() const
    {
      return m_hour;
    }

    /**
     * Returns minute of the hour (from 0 to 59).
     */
    inline int minute() const
    {
      return m_minute;
    }

    /**
     * Returns second of the minute (from 0 to 59).
     */
    inline int second() const
    {
      return m_second;
    }

    /**
     * Uses strftime() function to format the time into a string.
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
     * Assigns values from another time into this one.
     *
     * \param that Other time to copy values from
     */
    inline time& assign(const time& that)
    {
      return assign(that.m_hour, that.m_minute, that.m_second);
    }

    /**
     * Replaces values of the time with given values.
     *
     * \param hour   New hour of the day
     * \param minute New minute of the hour
     * \param second New second of the minute
     * \throw std::invalid_argument If given values do not construct a valid
     *                              time
     */
    time& assign(int hour, int minute, int second)
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

    /**
     * Assignment operator.
     */
    time& operator=(const time&) = default;

    /**
     * Move constructor.
     */
    time& operator=(time&&) = default;

    /**
     * Tests whether two time values are equal.
     *
     * \param that Other time value to test equality with
     */
    inline bool equals(const time& that) const
    {
      return equals(that.m_hour, that.m_minute, that.m_second);
    }

    /**
     * Tests whether this time has given values.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       A boolean flag indicating whether this time has given
     *               values or not
     */
    inline bool equals(int hour, int minute, int second) const
    {
      return hour == m_hour && m_minute == minute && m_second == second;
    }

    /**
     * Equality testing operator.
     */
    inline bool operator==(const time& that) const
    {
      return equals(that);
    }

    /**
     * Non-equality testing operator.
     */
    inline bool operator!=(const time& that) const
    {
      return !equals(that);
    }

    /**
     * Compares two times against each other.
     *
     * \param that Other time to compare this one against
     * \return     Integer value indicating comparison result
     */
    inline int compare(const time& that) const
    {
      return compare(that.m_hour, that.m_minute, that.m_second);
    }

    /**
     * Compares time against given values.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       Integer value indicating comparison result
     */
    int compare(int hour, int minute, int second) const
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

    /**
     * Comparison operator.
     */
    inline bool operator<(const time& that) const
    {
      return compare(that) < 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>(const time& that) const
    {
      return compare(that) > 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<=(const time& that) const
    {
      return compare(that) <= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>=(const time& that) const
    {
      return compare(that) >= 0;
    }

    /**
     * Increments time by one second.
     */
    time& operator++()
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

    /**
     * Increments time by one second.
     */
    time operator++(int)
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

    /**
     * Decrements time by one second.
     */
    time& operator--()
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

    /**
     * Decrements time by one second.
     */
    time operator--(int)
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

    /**
     * Adds given number of seconds to the time and returns result.
     */
    inline time operator+(int seconds) const
    {
      return time(*this) += seconds;
    }

    /**
     * Substracts given number of seconds from the time and returns result.
     */
    inline time operator-(int seconds) const
    {
      return time(*this) -= seconds;
    }

    /**
     * Adds given number of seconds to the time.
     */
    time& operator+=(int seconds)
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

    /**
     * Substracts given number of seconds from the time.
     */
    time& operator-=(int seconds)
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

  private:
    static void normalize(int& second, int& minute, int& hour)
    {
      static const int seconds_per_minute = 60;
      static const int seconds_per_hour = seconds_per_minute * 60;
      static const int seconds_per_day = seconds_per_hour * 24;

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

  private:
    /** Hour of the day. */
    int m_hour;
    /** Minute of the hour. */
    int m_minute;
    /** Second of the minute. */
    int m_second;
  };

  /**
   * Returns textual presentation of the time into the stream in RFC 2822
   * compliant format.
   */
  inline std::string to_string(const class time& time)
  {
    return time.format("%T");
  }
}
