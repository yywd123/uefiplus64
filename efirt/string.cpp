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

} // namespace efi::String