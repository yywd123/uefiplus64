#pragma once

#include <efi/efi.hpp>

namespace efi {

Handle getImageHandle();
SystemTable *getSystemTable();

void print(const char16_t *msg);
void exit(Status status);

} // namespace efi