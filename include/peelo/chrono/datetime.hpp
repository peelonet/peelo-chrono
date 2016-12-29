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
#ifndef PEELO_CHRONO_DATETIME_HPP_GUARD
#define PEELO_CHRONO_DATETIME_HPP_GUARD

#include <peelo/chrono/date.hpp>
#include <peelo/chrono/time.hpp>

namespace peelo
{
  /**
   * Combination of date and time.
   */
  class datetime
  {
  public:
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
      const enum month& month = peelo::month::jan,
      int day = 1,
      int hour = 0,
      int minute = 0,
      int second = 0
    );

    /**
     * Copy constructor.
     */
    datetime(const datetime& that);

    /**
     * Constructs datetime from given date and time.
     */
    datetime(const class date& date, const class time& time);

    /**
     * Returns current date and time based on system clock.
     *
     * \throw std::runtime_error If current date and time cannot be extracted
     *                           from the system for reason
     */
    static datetime now();

    /**
     * Constructs date and time from UNIX timestamp.
     */
    static datetime timestamp(long timestamp);

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
    static bool is_valid(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    );

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
    long timestamp() const;

    /**
     * Uses strftime() function to format the datetime into a string.
     */
    std::string format(const std::string& format) const;

    /**
     * Assigns values from another date and time into this one.
     *
     * \param that Other date and time to copy values from
     */
    datetime& assign(const datetime& that);

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
    );

    /**
     * Replaces values of the date and time with given values.
     */
    datetime& assign(const class date& date, const class time& time);

    /**
     * Assignment operator.
     */
    inline datetime& operator=(const datetime& that)
    {
      return assign(that);
    }

    /**
     * Tests whether two datetimes are equal.
     *
     * \param that Other date and time to test equality with
     */
    bool equals(const datetime& that) const;

    /**
     * Tests whether date and time are equal with given values.
     */
    bool equals(
      int year,
      const enum month& month,
      int day,
      int hour,
      int minute,
      int second
    ) const;

    /**
     * Tests whether date and time are equal with given values.
     */
    bool equals(const class date& date, const class time& time) const;

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
    int compare(const datetime& that) const;

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
    ) const;

    /**
     * Compares this datetime value against given date and time values.
     */
    int compare(const class date& date, const class time& time) const;

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
    datetime& operator++();

    /**
     * Increments date by one day.
     */
    datetime operator++(int);

    /**
     * Decrements date by one day.
     */
    datetime& operator--();

    /**
     * Decrements date by one day.
     */
    datetime operator--(int);

    /**
     * Adds given amount of days to the datetime and returns result.
     */
    datetime operator+(int days) const;

    /**
     * Substracts given amount of days from the datetime and returns result.
     */
    datetime operator-(int days) const;

    /**
     * Adds given amount of days to the datetime.
     */
    datetime& operator+=(int days);

    /**
     * Substracts given amount of days from the datetime.
     */
    datetime& operator-=(int days);

    /**
     * Returns the difference (in seconds) between two datetimes.
     */
    int operator-(const datetime& that) const;

  private:
    /** Date value of date and time. */
    class date m_date;
    /** Time value of date and time. */
    class time m_time;
  };

  std::ostream& operator<<(std::ostream&, const datetime&);
}

#endif /* !PEELO_CHRONO_DATETIME_HPP_GUARD */
