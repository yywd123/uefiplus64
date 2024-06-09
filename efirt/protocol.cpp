#include <efi/protocol.hpp>
#include <efi/rt.hpp>

namespace efi::Protocol {

Status locateProtocol(Guid guid, void **instance) {
  auto bs = getSystemTable()->bootServices;

  return bs->locateProtocol(&guid, nullptr, instance);
}

Status locateHandleBuffer(
    Guid guid,
    Protocol::SearchType searchType,
    void *searchKey,
    uint64_t *handleCount,
    Handle **list
) {
  auto bs = getSystemTable()->bootServices;

  return bs
      ->locateHandleBuffer(searchType, &guid, searchKey, handleCount, list);
}

Status locateDevicePath(
    Guid guid,
    DevicePath::DevicePath **devicePath,
    Handle *handle
) {
  auto bs = getSystemTable()->bootServices;

  return bs->locateDevicePath(&guid, devicePath, handle);
}

Status handleProtocol(Guid guid, void **instance, Handle handle) {
  auto bs = getSystemTable()->bootServices;

  return bs->handleProtocol(handle, &guid, instance);
}

Status openProtocol(
    Guid guid,
    void **instance,
    Handle handle,
    Handle agentHandle,
    Handle controllerHandle,
    uint32_t attributes
) {
  auto bs = getSystemTable()->bootServices;

  return bs->openProtocol(
      handle,
      &guid,
      instance,
      agentHandle,
      controllerHandle,
      attributes
  );
}

Status closeProtocol(
    Guid guid,
    Handle handle,
    Handle agentHandle,
    Handle controllerHandle
) {
  auto bs = getSystemTable()->bootServices;

  return bs->closeProtocol(handle, &guid, agentHandle, controllerHandle);
}

} // namespace efi::Protocol