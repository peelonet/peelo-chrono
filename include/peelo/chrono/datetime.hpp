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

#include <peelo/chrono/date.hpp>
#include <peelo/chrono/time.hpp>

namespace peelo::chrono
{
  /**
   * Combination of date and time.
   */
  class datetime
  {
  public:
    /**
     * Format string for RFC 2822 compliant date and time format.
     */
    static constexpr const char* format_rfc2822 = "%a, %d %b %Y %T %z";

    /**
     * Constructs datetime from given values.
     *
     * \param year   Year of the date
     * \param month  Month of the year
     * \param day    Day of the month
     * \param hour   Hour of the date
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \throw std::invalid_argument If given values do not construct a valid
     *                              date and time
     */
    explicit datetime(
      int year = 1900,
      const enum month& month = month::jan,
      int day = 1,
      int hour = 0,
      int minute = 0,
      int second = 0
    )
      : m_date(year, month, day)
      , m_time(hour, minute, second) {}

    /**
     * Copy constructor.
     */
    datetime(const datetime&) = default;

    /**
     * Move constructor.
     */
    datetime(datetime&&) = default;

    /**
     * Constructs datetime from given date and time.
     */
    datetime(const class date& date, const class time& time)
      : m_date(date)
      , m_time(time) {}

    /**
     * Returns current date and time based on system clock.
     *
     * \throw std::runtime_error If current date and time cannot be extracted
     *                           from the system for reason
     */
    static datetime now()
    {
      const auto now = std::chrono::system_clock::now();
      const auto ts = std::chrono::system_clock::to_time_t(now);
      const auto tm = std::localtime(&ts);

      if (!tm || tm->tm_mon < 0 || tm->tm_mon > 11)
      {
        throw std::runtime_error("localtime() failed");
      }

      return datetime(
        tm->tm_year + 1900,
        static_cast<enum month>(tm->tm_mon),
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec
      );
    }

    /**
     * Constructs date and time from UNIX timestamp.
     */
    static datetime timestamp(long timestamp)
    {
      auto ts = static_cast<std::time_t>(timestamp);
      auto tm = std::localtime(&ts);

      if (!tm || tm->tm_mon < 0 || tm->tm_mon > 11)
      {
        throw std::runtime_error("localtime() failed");
      }

      return datetime(
        tm->tm_year + 1900,
        static_cast<enum month>(tm->tm_mon),
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec
      );
    }

    /**
     * Tests whether given values are a valid date and time.
     *
     * \param year   Year of the date
     * \param month  Month of the year
     * \param day    Day of the month
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the hour
     * \return       A boolean flag indicating whether valid date and time can
     *               be constructed from given values
     */
    static inline bool is_valid(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    )
    {
      return date::is_valid(year, month, day)
        && time::is_valid(hour, minute, second);
    }

    /**
     * Returns date value.
     */
    inline const class date& date() const
    {
      return m_date;
    }

    /**
     * Returns year of the date.
     */
    inline int year() const
    {
      return m_date.year();
    }

    /**
     * Returns month of the year.
     */
    inline const enum month& month() const
    {
      return m_date.month();
    }

    /**
     * Returns day of the month (from 1 to 31) of the date.
     */
    inline int day() const
    {
      return m_date.day();
    }

    /**
     * Returns day of the week for this date.
     */
    inline weekday day_of_week() const
    {
      return m_date.day_of_week();
    }

    /**
     * Returns the day of the year (from 1 to 365 or 366 on leap years) for
     * this date.
     */
    inline int day_of_year() const
    {
      return m_date.day_of_year();
    }

    /**
     * Returns the number of days in the year (365 or 366) for this date.
     */
    inline int days_in_year() const
    {
      return m_date.days_in_year();
    }

    /**
     * Returns <code>true</code> if the year represented by the date is a leap
     * year.
     */
    inline bool is_leap_year() const
    {
      return m_date.is_leap_year();
    }

    /**
     * Returns time value.
     */
    inline const class time& time() const
    {
      return m_time;
    }

    /**
     * Returns hour of the day (from 0 to 23).
     */
    inline int hour() const
    {
      return m_time.hour();
    }

    /**
     * Returns minute of the hour (from 0 to 59).
     */
    inline int minute() const
    {
      return m_time.minute();
    }

    /**
     * Returns second of the minute (from 0 to 59).
     */
    inline int second() const
    {
      return m_time.second();
    }

    /**
     * Calculates UNIX timestamp from date and time.
     */
    inline std::int64_t timestamp() const
    {
      return (
        static_cast<std::int64_t>(m_time.second())
        + (m_time.minute() * 60)
        + (m_time.hour() * 3600)
        + m_date.timestamp()
      );
    }

    /**
     * Uses strftime() function to format the datetime into a string.
     */
    std::string format(const std::string& format) const
    {
      char buffer[BUFSIZ];
      auto tm = make_tm(*this);

      if (!std::strftime(buffer, BUFSIZ, format.c_str(), &tm))
      {
        throw std::runtime_error("strftime() failed");
      }

      return buffer;
    }

    /**
     * Assigns values from another date and time into this one.
     *
     * \param that Other date and time to copy values from
     */
    inline datetime& assign(const datetime& that)
    {
      return assign(that.m_date, that.m_time);
    }

    /**
     * Replaces values of the date and time with given values.
     *
     * \param year   Year of the date
     * \param month  Month of the year
     * \param day    Day of the month
     * \param hour   Hour of the date
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \throw std::invalid_argument If given values do not construct a valid
     *                              date and time
     */
    datetime& assign(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    )
    {
      m_date.assign(year, month, day);
      m_time.assign(hour, minute, second);

      return *this;
    }

    /**
     * Replaces values of the date and time with given values.
     */
    datetime& assign(const class date& date, const class time& time)
    {
      m_date.assign(date);
      m_time.assign(time);

      return *this;
    }

    /**
     * Assignment operator.
     */
    datetime& operator=(const datetime&) = default;

    /**
     * Move constructor.
     */
    datetime& operator=(datetime&&) = default;

    /**
     * Tests whether two datetimes are equal.
     *
     * \param that Other date and time to test equality with
     */
    inline bool equals(const datetime& that) const
    {
      return m_date.equals(that.m_date) && m_time.equals(that.m_time);
    }

    /**
     * Tests whether date and time are equal with given values.
     */
    inline bool equals(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    ) const
    {
      return m_date.equals(year, month, day)
        && m_time.equals(hour, minute, second);
    }

    /**
     * Tests whether date and time are equal with given values.
     */
    inline bool equals(const class date& date, const class time& time) const
    {
      return m_date.equals(date) && m_time.equals(time);
    }

    /**
     * Equality testing operator.
     */
    inline bool operator==(const datetime& that) const
    {
      return equals(that);
    }

    /**
     * Non-equality testing operator.
     */
    inline bool operator!=(const datetime& that) const
    {
      return !equals(that);
    }

    /**
     * Compares two datetimes against each other.
     *
     * \param that Other datetime to compare this one against
     * \return     Integer value indicating comparison result
     */
    int compare(const datetime& that) const
    {
      const int cmp = m_date.compare(that.m_date);

      if (cmp != 0)
      {
        return cmp;
      }

      return m_time.compare(that.m_time);
    }

    /**
     * Compares this datetime value against given values.
     */
    int compare(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    ) const
    {
      const int cmp = m_date.compare(year, month, day);

      if (cmp != 0)
      {
        return cmp;
      }

      return m_time.compare(hour, minute, second);
    }

    /**
     * Compares this datetime value against given date and time values.
     */
    int compare(const class date& date, const class time& time) const
    {
      const int cmp = m_date.compare(date);

      if (cmp != 0)
      {
        return cmp;
      }

      return m_time.compare(time);
    }

    /**
     * Comparison operator.
     */
    inline bool operator<(const datetime& that) const
    {
      return compare(that) < 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>(const datetime& that) const
    {
      return compare(that) > 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<=(const datetime& that) const
    {
      return compare(that) <= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>=(const datetime& that) const
    {
      return compare(that) >= 0;
    }

    /**
     * Increments date by one day.
     */
    datetime& operator++()
    {
      ++m_date;

      return *this;
    }

    /**
     * Increments date by one day.
     */
    datetime operator++(int)
    {
      const datetime return_value(*this);

      ++m_date;

      return return_value;
    }

    /**
     * Decrements date by one day.
     */
    datetime& operator--()
    {
      --m_date;

      return *this;
    }

    /**
     * Decrements date by one day.
     */
    datetime operator--(int)
    {
      const datetime return_value(*this);

      --m_date;

      return return_value;
    }

    /**
     * Adds given amount of days to the datetime and returns result.
     */
    inline datetime operator+(int days) const
    {
      return datetime(m_date + days, m_time);
    }

    /**
     * Substracts given amount of days from the datetime and returns result.
     */
    inline datetime operator-(int days) const
    {
      return datetime(m_date - days, m_time);
    }

    /**
     * Adds given amount of days to the datetime.
     */
    datetime& operator+=(int days)
    {
      m_date += days;

      return *this;
    }

    /**
     * Substracts given amount of days from the datetime.
     */
    datetime& operator-=(int days)
    {
      m_date -= days;

      return *this;
    }

    /**
     * Returns the difference between two datetimes.
     */
    duration operator-(const datetime& that) const
    {
      auto tm1 = make_tm(*this);
      auto tm2 = make_tm(that);
      const auto time1 = std::mktime(&tm1);
      const auto time2 = std::mktime(&tm2);

      return duration(std::difftime(time1, time2));
    }

  private:
    static std::tm make_tm(const datetime& dt)
    {
      std::tm tm = {0};

      tm.tm_year = dt.year() - 1900;
      tm.tm_mon = static_cast<int>(dt.month());
      tm.tm_mday = dt.day();
      tm.tm_hour = dt.hour();
      tm.tm_min = dt.minute();
      tm.tm_sec = dt.second();

      return tm;
    }

  private:
    /** Date value of date and time. */
    class date m_date;
    /** Time value of date and time. */
    class time m_time;
  };

  /**
   * Returns textual presentation of date and time into the stream in RFC 2822
   * compliant format.
   */
  inline std::string to_string(const class datetime& datetime)
  {
    return datetime.format(datetime::format_rfc2822);
  }
}
