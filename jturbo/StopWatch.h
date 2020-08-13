#pragma once

#include <chrono>

namespace jturbo {

/// http://www.cplusplus.com/reference/chrono/
/// https://msdn.microsoft.com/ko-kr/library/hh874790.aspx
/// system_clock.
/// steady_clock = QueryPerformanceCounter.
/// high_resolution_clock = steady_clock.
#if (_MSC_VER >= 1900)
template <typename T = std::chrono::steady_clock>
#elif (_MSC_VER == 1800)
template <typename T = std::chrono::high_resolution_clock>
#else
#pragma message Not supported compiler.
#endif
class StopWatch
{
public:
  StopWatch()
  {
    m_start = T::now();
  }
  ~StopWatch()
  {
  }

  void Reset()
  {
    m_start = T::now();
  }

  /// 0.124.
  double GetSeconds() const
  {
    std::chrono::time_point<T> endTime = T::now();
    std::chrono::duration<double> durationSecond = endTime - m_start;
    return durationSecond.count();
  }
  /// 124, 10^-3.
  long long GetMilliseconds() const
  {
    auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(T::now() - m_start);
    return dur2.count();
  }
  /// 124015, 10^-6.
  long long GetMicroseconds() const
  {
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(T::now() - m_start);
    return dur2.count();
  }
  /// 124015700, , 10^-9.
  long long GetNanoseconds() const
  {
    auto dur2 = std::chrono::duration_cast<std::chrono::nanoseconds>(T::now() - m_start);
    return dur2.count();
  }

protected:
  std::chrono::time_point<T> m_start;
};

} // namespace jturbo