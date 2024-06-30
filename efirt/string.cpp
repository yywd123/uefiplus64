#include <efi/memory.hpp>
#include <efi/string.hpp>

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 1

#define __attribute__(v, ...)
#define NANOPRINTF_IMPLEMENTATION 1
#include "nanoprintf.inl"
#undef __attribute__

using namespace efi;

namespace efi::String {

size_t format_length(const char16_t *fmt, va_list ap) {
  static size_t size = 0;

  npf_vpprintf([](int, void *) { ++size; }, nullptr, fmt, ap);

  return size;
}

PoolObject<const char16_t> format(const char16_t *fmt, ...) {
  va_list ap0, ap1;
  va_start(ap0, fmt);
  va_copy(ap1, ap0);

  auto length = format_length(fmt, ap1);
  auto buf = (char16_t *)
      Memory::allocPool(Memory::Type::LoaderData, length * sizeof(char16_t));

  npf_vsnprintf(buf, length, fmt, ap0);

  va_end(ap0);
  va_end(ap1);

  return buf;
}

bool startsWith(const char16_t *str, const char16_t *prefix) {
  while (*prefix) {
    if (*str == *prefix) {
      ++str;
      ++prefix;
    } else {
      break;
    }
  }

  return *prefix == 0;
}

bool endsWith(const char16_t *str, const char16_t *suffix) {
  auto len1 = wstrlen(str);
  auto len2 = wstrlen(suffix);

  return wstrncmp(str + len1 - len2, suffix, len2) == 0;
}

} // namespace efi::String

int wstrcmp(const char16_t *s1, const char16_t *s2) {
  uint8_t c1, c2;

  while (1) {
    c1 = *s1++;
    c2 = *s2++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (!c1)
      break;
  }

  return 0;
}

int wstrncmp(const char16_t *s1, const char16_t *s2, size_t n) {
  uint8_t c1, c2;

  while (n) {
    c1 = *s1++;
    c2 = *s2++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (!c1)
      break;
    n--;
  }

  return 0;
}

size_t wstrlen(const char16_t *s) {
  size_t i;
  for (i = 0; s[i] != 0; ++i)
    ;
  return i;
}

PoolObject<char16_t> wstrdup(const char16_t *s) {
  auto len = wstrlen(s);
  auto sz = (len + 1) * sizeof(char16_t);
  auto buf = (char16_t *)Memory::allocPool(Memory::Type::LoaderData, sz);

  memcpy(buf, (void *)s, sz);
  buf[len] = 0;

  return buf;
}