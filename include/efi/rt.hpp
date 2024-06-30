#pragma once

#include <efi/efi.hpp>

#include <cstdarg>

namespace efi {

Handle getImageHandle();
SystemTable *getSystemTable();

void print(const char16_t *msg);
void printf(const char16_t *fmt, ...);
void exit(Status status);

namespace Event {

class TPLGuard {
  TPL tpl;

public:
  TPLGuard(TPL newTPL);
  ~TPLGuard();
};

} // namespace Event

} // namespace efi