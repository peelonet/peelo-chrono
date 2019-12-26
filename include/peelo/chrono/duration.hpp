/*
 * Copyright (c) 2019, peelo.net
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
#ifndef PEELO_CHRONO_DURATION_HPP_GUARD
#define PEELO_CHRONO_DURATION_HPP_GUARD

#include <cstdint>

namespace peelo::chrono
{
  /**
   * Time based amount of time, such as '34.5 minutes'.
   */
  class duration
  {
  public:
    using value_type = std::int64_t;

    static const value_type hours_per_day = 24;
    static const value_type minutes_per_hour = 60;
    static const value_type minutes_per_day = 1440;
    static const value_type seconds_per_minute = 60;
    static const value_type seconds_per_hour = 3600;
    static const value_type seconds_per_day = 86400;

    /**
     * Constructs new duration instance which spans given number of seconds.
     *
     * \param seconds Seconds of the duration.
     */
    explicit duration(value_type seconds = 0)
      : m_seconds(seconds) {}

    /**
     * Constructs new duration instance which spans given number of days.
     *
     * \param days Number of days in the duration.
     */
    static inline duration of_days(value_type days)
    {
      return duration(days * seconds_per_day);
    }

    /**
     * Constructs new duration instance which spans given number of hours.
     *
     * \param hours Number of hours in the duration.
     */
    static inline duration of_hours(value_type hours)
    {
      return duration(hours * seconds_per_hour);
    }

    /**
     * Constructs new duration instance which spans given number of minutes.
     *
     * \param minutes Number of minutes in the duration.
     */
    static inline duration of_minutes(value_type minutes)
    {
      return duration(minutes * seconds_per_minute);
    }

    /**
     * Copy constructor.
     *
     * \param that Other duration value to construct copy of.
     */
    duration(const duration& that)
      : m_seconds(that.m_seconds) {}

    /**
     * Returns the number of days in the duration.
     */
    inline value_type days() const
    {
      return m_seconds / seconds_per_day;
    }

    /**
     * Returns the number of hours in the duration.
     */
    inline value_type hours() const
    {
      return m_seconds / seconds_per_hour;
    }

    /**
     * Returns the number of minutes in the duration.
     */
    inline value_type minutes() const
    {
      return m_seconds / seconds_per_minute;
    }

    /**
     * Returns the number of seconds in the duration.
     */
    inline value_type seconds() const
    {
      return m_seconds;
    }

    /**
     * Assigns value from another duration into this one.
     *
     * \param that Other duration to copy seconds from.
     */
    inline duration& assign(const duration& that)
    {
      m_seconds = that.m_seconds;

      return *this;
    }

    /**
     * Replaces seconds in the duration with given number of seconds.
     *
     * \param seconds Number of seconds in the duration.
     */
    inline duration& assign(value_type seconds)
    {
      m_seconds = seconds;

      return *this;
    }

    /**
     * Assignment operator.
     */
    inline duration& operator=(const duration& that)
    {
      return assign(that);
    }

    /**
     * Assignment operator.
     */
    inline duration& operator=(value_type seconds)
    {
      return assign(seconds);
    }

    /**
     * Tests whether two duration instances are equal or not.
     *
     * \param that Another duration to compare this one with.
     * \return     A boolean flag indicating whether the two durations are
     *             equal or not.
     */
    inline bool equals(const duration& that) const
    {
      return m_seconds == that.m_seconds;
    }

    /**
     * Tests whether the duration contains given number of seconds or not.
     *
     * \param seconds Seconds to compare the duration against.
     * \return        A boolean flag to indicate whether the duration contains
     *                exactly given number of seconds.
     */
    inline bool equals(value_type seconds) const
    {
      return m_seconds == seconds;
    }

    /**
     * Equality testing operator.
     */
    inline bool operator==(const duration& that) const
    {
      return equals(that);
    }

    /**
     * Equality testing operator.
     */
    inline bool operator==(value_type seconds) const
    {
      return equals(seconds);
    }

    /**
     * Non-equality testing operator.
     */
    inline bool operator!=(const duration& that) const
    {
      return !equals(that);
    }

    /**
     * Non-equality testing operator.
     */
    inline bool operator!=(value_type seconds) const
    {
      return !equals(seconds);
    }

    /**
     * Compares two durations against each other.
     *
     * \param that Other duration to compare this one against.
     * \return     Integer value indicating comparison result.
     */
    inline int compare(const duration& that) const
    {
      if (m_seconds > that.m_seconds)
      {
        return 1;
      }
      else if (m_seconds < that.m_seconds)
      {
        return -1;
      } else {
        return 0;
      }
    }

    /**
     * Compares duration against given number of seconds.
     *
     * \param seconds Number of seconds to compare the duration against.
     * \return        Integer value indicating comparison result.
     */
    inline int compare(value_type seconds) const
    {
      if (m_seconds > seconds)
      {
        return 1;
      }
      else if (m_seconds < seconds)
      {
        return -1;
      } else {
        return 0;
      }
    }

    /**
     * Comparison operator.
     */
    inline bool operator<(const duration& that) const
    {
      return compare(that) < 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<(value_type seconds) const
    {
      return compare(seconds) < 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>(const duration& that) const
    {
      return compare(that) > 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>(value_type seconds) const
    {
      return compare(seconds) > 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<=(const duration& that) const
    {
      return compare(that) <= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator<=(value_type seconds) const
    {
      return compare(seconds) <= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>=(const duration& that) const
    {
      return compare(that) >= 0;
    }

    /**
     * Comparison operator.
     */
    inline bool operator>=(value_type seconds) const
    {
      return compare(seconds) >= 0;
    }

    /**
     * Increments duration by one second.
     */
    duration& operator++()
    {
      ++m_seconds;

      return *this;
    }

    /**
     * Increments duration by one second.
     */
    duration operator++(int)
    {
      const duration return_value = duration(*this);

      ++m_seconds;

      return return_value;
    }

    /**
     * Decrements duration by one second.
     */
    duration& operator--()
    {
      --m_seconds;

      return *this;
    }

    /**
     * Decrements duration by one second.
     */
    duration operator--(int)
    {
      const duration return_value = duration(*this);

      --m_seconds;

      return return_value;
    }

    /**
     * Adds given number of seconds to the duration and returns result.
     */
    duration operator+(value_type seconds) const
    {
      return duration(m_seconds + seconds);
    }

    /**
     * Substracts given number of seconds from the duration and returns result.
     */
    duration operator-(value_type seconds) const
    {
      return duration(m_seconds - seconds);
    }

    /**
     * Adds given number of seconds to the duration.
     */
    duration& operator+=(value_type seconds)
    {
      m_seconds += seconds;

      return *this;
    }

    /**
     * Substracts given number of seconds from the duration.
     */
    duration& operator-=(value_type seconds)
    {
      m_seconds -= seconds;

      return *this;
    }

  private:
    /** Number of seconds in the duration. */
    value_type m_seconds;
  };
}

#endif /* !PEELO_CHRONO_DURATION_HPP_GUARD */
