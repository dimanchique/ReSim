#pragma once

#if defined(_MSC_VER)
#   define INLINE __inline
#else
#   define INLINE __inline__
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#   define FORCE_INLINE inline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#   define FORCE_INLINE inline __attribute__((always_inline))
#else
#   define FORCE_INLINE INLINE
#endif

#if defined(_MSC_VER)
#   define __FUNC__ __FUNCTION__
#elif defined(__GNUC__) || defined(__clang__)
#   define __FUNC__ __func__
#else
#   define __FUNC__ "N/A"
#endif
