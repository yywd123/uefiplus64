#include <efi/memory.hpp>
#include <efi/rt.hpp>

namespace efi::Memory {

void *allocPool(Memory::Type type, size_t size) {
  auto bs = getSystemTable()->bootServices;
  void *pool;

  bs->allocatePool(type, size, &pool);

  return pool;
}

void freePool(void *pool) { getSystemTable()->bootServices->freePool(pool); }

} // namespace efi::Memory