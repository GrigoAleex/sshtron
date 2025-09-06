#pragma once

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>

  static inline void sleep_seconds(unsigned int s) { Sleep(s * 1000u); }
  static inline void sleep_microseconds(unsigned int us) { Sleep((us + 999) / 1000); }

#else
  #include <unistd.h>
  static inline void sleep_seconds(unsigned int s) { sleep(s); }
  static inline void sleep_microseconds(unsigned int us) { usleep(us); }
#endif
