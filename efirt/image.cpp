#include <efi/image.hpp>
#include <efi/protocol.hpp>
#include <efi/rt.hpp>

namespace efi::Image {

Handle load(void *image, size_t size) {
  auto bs = getSystemTable()->bootServices;
  Handle handle;

  bs->loadImage(false, getImageHandle(), nullptr, image, size, &handle);

  return handle;
}

Handle load(DevicePath *imagePath) {
  auto bs = getSystemTable()->bootServices;
  Handle handle;

  bs->loadImage(false, getImageHandle(), imagePath, nullptr, 0, &handle);

  return handle;
}

ExitInfo start(Handle imageHandle) {
  auto bs = getSystemTable()->bootServices;
  ExitInfo info;

  info.status = bs->startImage(imageHandle, &info.length, &info.info);

  return info;
}

Status unload(Handle imageHandle) {
  auto bs = getSystemTable()->bootServices;

  return bs->unloadImage(imageHandle);
}

LoadedImage *getLoadedImageProtocol(Handle imageHandle) {
  LoadedImage *protocol;

  Protocol::openProtocol(
      EFI_LOADED_IMAGE_PROTOCOL_GUID,
      (void **)&protocol,
      imageHandle,
      getImageHandle(),
      nullptr,
      Protocol::GetProtocol
  );

  return protocol;
}

} // namespace efi::Image