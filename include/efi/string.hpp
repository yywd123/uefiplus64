#pragma once

#include <efi/memory.hpp>

#include <cstdarg>

namespace efi::String {

size_t format_length(const char16_t *fmt, va_list ap);
PoolObject<const char16_t> format(const char16_t *fmt, ...);

bool startsWith(const char16_t *str, const char16_t *prefix);
bool endsWith(const char16_t *str, const char16_t *suffix);

} // namespace efi::String

int wstrcmp(const char16_t *s1, const char16_t *s2);
int wstrncmp(const char16_t *s1, const char16_t *s2, size_t n);

size_t wstrlen(const char16_t *s);

efi::PoolObject<char16_t> wstrdup(const char16_t *s);