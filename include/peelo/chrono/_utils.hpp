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

#include <ctime>
#include <stdexcept>
#if !defined(_WIN32) && !defined(__unix__)
#  include <thread>
#endif

#if defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

namespace peelo::chrono::utils
{
  /**
   * Thread safe (at least on most platforms) version of `std::localtime`.
   */
  inline std::tm localtime(const std::time_t& timestamp)
  {
#if !defined(_WIN32) && !defined(__unix__)
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    std::tm* pointer;
#else
    std::tm result {};
#endif

#if defined(_WIN32)
    if (::localtime_s(&result, &timestamp))
#elif defined(__unix__)
    if (!::localtime_r(&timestamp, &result))
#else
    if (!(pointer = std::localtime(&timestamp)))
#endif
    {
      throw std::runtime_error("localtime() failed");
    }

#if !defined(_WIN32) && !defined(__unix__)
    return *pointer;
#else
    return result;
#endif
  }
}
