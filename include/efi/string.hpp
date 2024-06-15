#pragma once

#include <efi/memory.hpp>

#include <cstdarg>

namespace efi::String {

size_t format_length(const char16_t *fmt, va_list ap);
PoolObject<const char16_t> format(const char16_t *fmt, ...);

} // namespace efi::String