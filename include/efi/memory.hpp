#pragma once

#include <efi/efi.hpp>
#include <efi/rt.hpp>

namespace efi {

namespace Memory {

void *allocPool(Memory::Type type, size_t size);
void freePool(void *pool);

} // namespace Memory

template <typename T = void> class PoolObject {
  T *ptr;

public:
  PoolObject() = default;
  PoolObject(const PoolObject &ref) = delete;
  PoolObject(PoolObject &ref) {
    this->ptr = ref.ptr;
    ref.ptr = nullptr;
  };

  PoolObject(void *p) : ptr((T *)p){};
  ~PoolObject() {
    if (this->ptr) {
      Memory::freePool((void *)ptr);
    }
  };

  T *get() { return this->ptr; };
  T *&asRef() { return this->ptr; };

  T *operator->() { return this->ptr; };

  PoolObject &operator=(const PoolObject &) = delete;
};

namespace Memory {

template <typename T = void> constexpr PoolObject<T> alloc(size_t bytes) {
  return PoolObject<T>(allocPool(Memory::Type::LoaderData, bytes));
}

} // namespace Memory

} // namespace efi