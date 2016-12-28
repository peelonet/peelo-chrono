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
#ifndef PEELO_CHRONO_DATE_HPP_GUARD
#define PEELO_CHRONO_DATE_HPP_GUARD

#include <peelo/chrono/month.hpp>
#include <peelo/chrono/weekday.hpp>

namespace peelo
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
      const enum month& month = peelo::month::jan,
      int day = 1
    );

    /**
     * Copy constructor.
     */
    date(const date& that);

    /**
     * Returns current date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date today();

    /**
     * Returns yesterdays date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date yesterday();

    /**
     * Returns tomorrows date based on system clock.
     *
     * \throw std::runtime_error If current date cannot be retrieved from the
     *                           system for some reason
     */
    static date tomorrow();

    /**
     * Constructs date value from UNIX timestamp.
     */
    static date timestamp(long timestamp);

    /**
     * Tests whether given values are a valid date.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      A boolean flag indicating whether an valid date can be
     *              constructed from given values
     */
    static bool is_valid(int year, const enum month& month, int day);

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
    weekday day_of_week() const;

    /**
     * Returns the day of the year (from 1 to 365 or 366 on leap years) for
     * this date.
     */
    int day_of_year() const;

    /**
     * Returns the number of days in the month (28-31) for this date.
     */
    int days_in_month() const;

    /**
     * Returns the number of days in the month (28-31) for given month.
     *
     * \param month     Month to retrieve number of days for
     * \param leap_year Whether the year is leap year or not
     */
    static int days_in_month(const enum month& month, bool leap_year);

    /**
     * Returns the number of days in the year (365 or 366) for this date.
     */
    int days_in_year() const;

    /**
     * Returns the number of days in the year (365 or 366) for the given year.
     *
     * \param year Year to retrieve number of days for
     */
    static int days_in_year(int year);

    /**
     * Returns <code>true</code> if the year represented by the date is a leap
     * year.
     */
    bool is_leap_year() const;

    /**
     * Returns <code>true</code> if the given year is leap year.
     *
     * \param year Year to test for leap year
     */
    static bool is_leap_year(int year);

    /**
     * Calculates UNIX timestamp from date.
     */
    long timestamp() const;

    /**
     * Assigns values from another date into this one.
     *
     * \param that Other date to copy values from
     */
    date& assign(const date& that);

    /**
     * Replaces values of the date with given values.
     *
     * \param year  New year of the date
     * \param month New month of the year
     * \param day   New day of the month
     * \throw std::invalid_argument If given values do not construct a valid
     *                              date
     */
    date& assign(int year, const enum month& month, int day);

    /**
     * Assignment operator.
     */
    inline date& operator=(const date& that)
    {
      return assign(that);
    }

    /**
     * Tests whether two dates are equal or not.
     *
     * \param that Another date to compare this one with
     * \return     A boolean flag indicating whether the dates are equal or not
     */
    bool equals(const date& that) const;

    /**
     * Tests whether this date has given values.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      A boolean flag indicating whether this date has given
     *              values or not
     */
    bool equals(int year, const enum month& month, int day) const;

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
    int compare(const date& that) const;

    /**
     * Compares date against given values.
     *
     * \param year  Year of the date
     * \param month Month of the year
     * \param day   Day of the month
     * \return      Integer value indicating comparison result
     */
    int compare(int year, const enum month& month, int day) const;

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
    date& operator++();

    /**
     * Increments date by one day.
     */
    date operator++(int);

    /**
     * Decrements date by one day.
     */
    date& operator--();

    /**
     * Decrements date by one day.
     */
    date operator--(int);

    /**
     * Adds given number of days to the date and returns result.
     */
    date operator+(int days) const;

    /**
     * Substracts given number of days from the date and returns result.
     */
    date operator-(int days) const;

    /**
     * Adds given number of days to the date.
     */
    date& operator+=(int days);

    /**
     * Substracts given number of days from the date.
     */
    date& operator-=(int days);

    /**
     * Returns the difference (in days) between two dates.
     */
    int operator-(const date& that) const;

  private:
    /** Year of the date. */
    int m_year;
    /** Month of the year. */
    enum month m_month;
    /** Day of the month. */
    int m_day;
  };

  std::ostream& operator<<(std::ostream&, const date&);
  std::wostream& operator<<(std::wostream&, const date&);
}

#endif /* !PEELO_CHRONO_DATE_HPP_GUARD */
