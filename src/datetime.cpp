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
#include <peelo/chrono/datetime.hpp>
#include <ctime>
#include <stdexcept>

namespace peelo
{
  static std::tm make_tm(const datetime&);

  datetime::datetime(int year,
                     const enum month& month,
                     int day,
                     int hour,
                     int minute,
                     int second)
    : m_date(year, month, day)
    , m_time(hour, minute, second) {}

  datetime::datetime(const datetime& that)
    : m_date(that.m_date)
    , m_time(that.m_time) {}

  datetime::datetime(const class date& date, const class time& time)
    : m_date(date)
    , m_time(time) {}

  datetime datetime::now()
  {
    return datetime(); // TODO
  }

  datetime datetime::timestamp(long timestamp)
  {
    std::time_t ts = static_cast<std::time_t>(timestamp);
    std::tm* tm = std::localtime(&ts);

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

  bool datetime::is_valid(int year,
                          const enum month& month,
                          int day,
                          int hour,
                          int minute,
                          int second)
  {
    return date::is_valid(year, month, day)
      && time::is_valid(hour, minute, second);
  }

  long datetime::timestamp() const
  {
    return (
      m_time.second()
      + (m_time.minute() * 60)
      + (m_time.hour() * 3600)
      + m_date.timestamp()
    );
  }

  datetime& datetime::assign(const datetime& that)
  {
    return assign(that.m_date, that.m_time);
  }

  datetime& datetime::assign(int year,
                             const enum month& month,
                             int day,
                             int hour,
                             int minute,
                             int second)
  {
    m_date.assign(year, month, day);
    m_time.assign(hour, minute, second);

    return *this;
  }

  datetime& datetime::assign(const class date& date, const class time& time)
  {
    m_date.assign(date);
    m_time.assign(time);

    return *this;
  }

  bool datetime::equals(const datetime& that) const
  {
    return m_date.equals(that.m_date) && m_time.equals(that.m_time);
  }

  bool datetime::equals(int year,
                        const enum month& month,
                        int day,
                        int hour,
                        int minute,
                        int second) const
  {
    return m_date.equals(year, month, day)
      && m_time.equals(hour, minute, second);
  }

  bool datetime::equals(const class date& date, const class time& time) const
  {
    return m_date.equals(date) && m_time.equals(time);
  }

  int datetime::compare(const datetime& that) const
  {
    const int cmp = m_date.compare(that.m_date);

    if (cmp != 0)
    {
      return cmp;
    }

    return m_time.compare(that.m_time);
  }

  int datetime::compare(int year,
                        const enum month& month,
                        int day,
                        int hour,
                        int minute,
                        int second) const
  {
    const int cmp = m_date.compare(year, month, day);

    if (cmp != 0)
    {
      return cmp;
    }

    return m_time.compare(hour, minute, second);
  }

  datetime& datetime::operator++()
  {
    ++m_date;

    return *this;
  }

  datetime datetime::operator++(int)
  {
    const datetime return_value(*this);

    ++m_date;

    return return_value;
  }

  datetime& datetime::operator--()
  {
    --m_date;

    return *this;
  }

  datetime datetime::operator--(int)
  {
    const datetime return_value(*this);

    --m_date;

    return return_value;
  }

  datetime datetime::operator+(int days) const
  {
    return datetime(m_date + days, m_time);
  }

  datetime datetime::operator-(int days) const
  {
    return datetime(m_date - days, m_time);
  }

  datetime& datetime::operator+=(int days)
  {
    m_date += days;

    return *this;
  }

  datetime& datetime::operator-=(int days)
  {
    m_date -= days;

    return *this;
  }

  int datetime::operator-(const datetime& that) const
  {
    std::tm tm1 = make_tm(*this);
    std::tm tm2 = make_tm(that);
    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    return static_cast<int>(std::difftime(time1, time2));
  }

  std::ostream& operator<<(std::ostream& os, const class datetime& datetime)
  {
    os << datetime.date() << 'T' << datetime.time() << 'Z';

    return os;
  }

  std::wostream& operator<<(std::wostream& os, const class datetime& datetime)
  {
    os << datetime.date() << L'T' << datetime.time() << L'Z';

    return os;
  }

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
}
