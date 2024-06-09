
#pragma once

#include <efi/efi.hpp>
#include <efi/memory.hpp>

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                   \
  {                                                                            \
    0x0964e5b22, 0x6459, 0x11d2, {                                             \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

#define EFI_FILE_INFO_GUID                                                     \
  {                                                                            \
    0x09576e92, 0x6d3f, 0x11d2, {                                              \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

namespace efi {

namespace File {

typedef struct {
  Event::Instance event;
  Status status;
  uint64_t bufferSize;
  void *buffer;
} IoToken;

typedef struct {
  uint64_t size;
  uint64_t fileSize;
  uint64_t physicalSize;
  Time::Time createTime;
  Time::Time lastAccessTime;
  Time::Time modificationTime;
  uint64_t attribute;
  char16_t fileName[];
} FileInfo;

typedef struct File {
  typedef Status(EFIAPI *Open)(
      struct File *instance,
      struct File **newHandle,
      const char16_t *fileName,
      uint64_t openMode,
      uint64_t attributes
  );

  typedef Status(EFIAPI *Close)(struct File *instance);

  typedef Status(EFIAPI *Remove)(struct File *instance);

  typedef Status(EFIAPI *Read)(
      struct File *instance,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *Write)(
      struct File *instance,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *SetPosition)(struct File *instance, uint64_t position);

  typedef Status(EFIAPI
                     *GetPosition)(struct File *instance, uint64_t *position);

  typedef Status(EFIAPI *GetInfo)(
      struct File *instance,
      Guid *informationType,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *SetInfo)(
      struct File *instance,
      Guid *informationType,
      uint64_t bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *Flush)(struct File *instance);

  typedef Status(EFIAPI *OpenEx)(
      struct File *instance,
      struct File **newHandle,
      const char16_t *fileName,
      uint64_t openMode,
      uint64_t attributes,
      IoToken *token
  );

  typedef Status(EFIAPI *FileOpEx)(struct File *instance, IoToken *token);

  uint64_t revision;
  Open _open;
  Close _close;
  Remove _remove;
  Read _read;
  Write _write;
  GetPosition _getPosition;
  SetPosition _setPosition;
  GetInfo _getInfo;
  SetInfo _setInfo;
  Flush _flush;
  OpenEx _openEx;    // Added for revision 2
  FileOpEx _readEx;  // Added for revision 2
  FileOpEx _writeEx; // Added for revision 2
  FileOpEx _flushEx; // Added for revision 2

  PoolObject<FileInfo> getInfo();

} File;

File *open(const char16_t *path, uint64_t openMode, uint64_t attributes);

} // namespace File

typedef struct SimpleFilesystem {
  typedef Status(EFIAPI *OpenVolume)(
      SimpleFilesystem *instance,
      File::File **root
  );

  uint64_t revision;
  OpenVolume openVolume;
} SimpleFilesystem;

} // namespace efi