#pragma once

#if defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define FORCE_INLINE inline __forceinline
#endif
