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
#ifndef PEELO_CHRONO_TIME_HPP_GUARD
#define PEELO_CHRONO_TIME_HPP_GUARD

#include <iostream>
#include <string>

namespace peelo
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
    explicit time(int hour = 0, int minute = 0, int second = 0);

    /**
     * Copy constructor.
     */
    time(const time& that);

    /**
     * Returns current time based on system clock.
     *
     * \throw std::runtime_error If current time cannot be extracted from the
     *                           system for some reason
     */
    static time now();

    /**
     * Tests whether given values are valid time.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       A boolean flag indicating whether an valid time can be
     *               constructed from given values
     */
    static bool is_valid(int hour, int minute, int day);

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
    std::string format(const std::string& format) const;

    /**
     * Assigns values from another time into this one.
     *
     * \param that Other time to copy values from
     */
    time& assign(const time& that);

    /**
     * Replaces values of the time with given values.
     *
     * \param hour   New hour of the day
     * \param minute New minute of the hour
     * \param second New second of the minute
     * \throw std::invalid_argument If given values do not construct a valid
     *                              time
     */
    time& assign(int hour, int minute, int second);

    /**
     * Assignment operator.
     */
    inline time& operator=(const time& that)
    {
      return assign(that);
    }

    /**
     * Tests whether two time values are equal.
     *
     * \param that Other time value to test equality with
     */
    bool equals(const time& that) const;

    /**
     * Tests whether this time has given values.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       A boolean flag indicating whether this time has given
     *               values or not
     */
    bool equals(int hour, int minute, int second) const;

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
    int compare(const time& that) const;

    /**
     * Compares time against given values.
     *
     * \param hour   Hour of the day
     * \param minute Minute of the hour
     * \param second Second of the minute
     * \return       Integer value indicating comparison result
     */
    int compare(int hour, int minute, int second) const;

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
    time& operator++();

    /**
     * Increments time by one second.
     */
    time operator++(int);

    /**
     * Decrements time by one second.
     */
    time& operator--();

    /**
     * Decrements time by one second.
     */
    time operator--(int);

    /**
     * Adds given number of seconds to the time and returns result.
     */
    time operator+(int seconds) const;

    /**
     * Substracts given number of seconds from the time and returns result.
     */
    time operator-(int seconds) const;

    /**
     * Adds given number of seconds to the time.
     */
    time& operator+=(int seconds);

    /**
     * Substracts given number of seconds from the time.
     */
    time& operator-=(int seconds);

  private:
    /** Hour of the day. */
    int m_hour;
    /** Minute of the hour. */
    int m_minute;
    /** Second of the minute. */
    int m_second;
  };

  /**
   * Writes textual presentation of the time into the stream in RFC 2822
   * compliant format.
   */
  std::ostream& operator<<(std::ostream&, const time&);
}

#endif /* !PEELO_CHRONO_TIME_HPP_GUARD */
