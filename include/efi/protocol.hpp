#pragma once

#include <efi/efi.hpp>

namespace efi::Protocol {

Status locateProtocol(Guid guid, void **instance);

Status locateHandleBuffer(
    Guid guid,
    Protocol::SearchType searchType,
    void *searchKey,
    uint64_t *handleCount,
    Handle **list
);

Status locateDevicePath(
    Guid guid,
    DevicePath::DevicePath **devicePath,
    Handle *handle
);

Status handleProtocol(Guid guid, void **instance, Handle handle);

Status openProtocol(
    Guid guid,
    void **instance,
    Handle handle,
    Handle agentHandle,
    Handle controllerHandle,
    uint32_t attributes
);

Status closeProtocol(
    Guid guid,
    Handle handle,
    Handle agentHandle,
    Handle controllerHandle
);

} // namespace efi::Protocol