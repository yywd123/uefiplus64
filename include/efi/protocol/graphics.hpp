#pragma once

#include <efi/efi.hpp>

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID                                      \
  {                                                                            \
    0x9042a9de, 0x23dc, 0x4a38, {                                              \
      0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a                           \
    }                                                                          \
  }

namespace efi {

typedef struct GraphicsOutput {
  typedef struct {
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t reservedMask;
  } PixelBitmask;

  typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
  } BltPixel;

  enum class PixelFormat : uint32_t {
    RBGRColor, //  0x00bbggrr
    RRGBColor, //  0x00rrggbb
    PixelBitMask,
    PixelBltOnly
  };

  enum class BltOperation : uint32_t {
    FillVideo,
    VideoToBuffer,
    BufferToVideo,
    VideoToVideo
  };

  typedef struct {
    uint32_t version;
    uint32_t horizontalResolution;
    uint32_t verticalResolution;
    PixelFormat pixelFormat;
    PixelBitmask pixelInformation;
    uint32_t pixelsPerScanLine;
  } ModeInfo;

  typedef struct {
    uint32_t maxMode;
    uint32_t mode;
    ModeInfo *info;
    uint64_t sizeOfInfo;
    uintptr_t frameBufferBase;
    uint64_t frameBufferSize;
  } Mode;

  typedef Status(EFIAPI *QueryMode)(
      IN GraphicsOutput *instance,
      IN uint32_t modeNumber,
      OUT uint64_t *sizeOfInfo,
      OUT ModeInfo **info
  );

  typedef Status(EFIAPI *SetMode)(
      IN GraphicsOutput *instance,
      IN uint32_t modeNumber
  );

  typedef Status(EFIAPI *Blt)(
      IN GraphicsOutput *instance,
      IN OUT BltPixel *bltBuffer,
      IN BltOperation operation OPTIONAL,
      IN uint64_t sourceX,
      IN uint64_t sourceY,
      IN uint64_t destinationX,
      IN uint64_t destinationY,
      IN uint64_t width,
      IN uint64_t height,
      IN uint64_t delta OPTIONAL
  );

  QueryMode queryMode;
  SetMode setMode;
  Blt blt;
  Mode *mode;
} GraphicsOutput;

} // namespace efi