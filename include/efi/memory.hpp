#pragma once

#include <efi/efi.hpp>
#include <efi/rt.hpp>

namespace efi {

namespace Memory {

void *allocPool(Memory::Type type, size_t size);
void *sizedReallocPool(Memory::Type type, void *p, size_t oldsz, size_t newsz);
void freePool(void *pool);

} // namespace Memory

template <typename T = void> class PoolObject {
  T *ptr;

public:
  PoolObject() = default;
  PoolObject(const PoolObject &ref) = delete;

  PoolObject(void *p) : ptr((T *)p) {
#if DEBUG_MEM_LEAKCHECK == 1
    printf(u"leakcheck: init %p\r\n", this->ptr);
#endif
  }

  ~PoolObject() {
    if (this->ptr) {
#if DEBUG_MEM_LEAKCHECK == 1
      printf(u"leakcheck: free %p\r\n", this->ptr);
#endif
      Memory::freePool((void *)ptr);
    }
  };

  template <typename R = T> R *get() { return (R *)this->ptr; };
  T *&asRef() { return this->ptr; };

  template <typename R = T> R *operator->() { return (R *)this->ptr; };

  /*
    调用这个函数意味着指针已经不再需要泄漏保护
    应由使用者来手动控制释放内存区域的时机
  */
  template <typename R = T> R *unwrap() {
#if DEBUG_MEM_LEAKCHECK == 1
    printf(u"leakcheck: unwrap %p\r\n", this->ptr);
#endif

    T *p = this->ptr;
    this->ptr = nullptr;

    return (R *)p;
  }

  PoolObject &operator=(const PoolObject &) = delete;
  operator bool() { return !!this->ptr; }
};

namespace Memory {

template <typename T = void> constexpr PoolObject<T> alloc(size_t bytes) {
  return PoolObject<T>(allocPool(Memory::Type::LoaderData, bytes));
}

} // namespace Memory

} // namespace efi

void memcpy(void *dest, void *src, size_t size);
void memmove(void *dest, void *src, size_t size);

void memset(void *buf, int c, size_t size);