#pragma once

#define __UEFIPLUS64__ 1

#include <cstddef>
#include <cstdint>

#define I   /* input param */
#define O   /* output param */
#define OPT /* optional param */

#define BIT(n) (1ull << (n))
#define EFIAPI __attribute__((ms_abi))

#define EFIMAKEERR(a) (a | BIT(63))
#define EFI_ERROR(a) (a & BIT(63))

#define EFI_SUCCESS 0
#define EFI_LOAD_ERROR EFIMAKEERR(1)
#define EFI_INVALID_PARAMETER EFIMAKEERR(2)
#define EFI_UNSUPPORTED EFIMAKEERR(3)
#define EFI_BAD_BUFFER_SIZE EFIMAKEERR(4)
#define EFI_BUFFER_TOO_SMALL EFIMAKEERR(5)
#define EFI_NOT_READY EFIMAKEERR(6)
#define EFI_DEVICE_ERROR EFIMAKEERR(7)
#define EFI_WRITE_PROTECTED EFIMAKEERR(8)
#define EFI_OUT_OF_RESOURCES EFIMAKEERR(9)
#define EFI_VOLUME_CORRUPTED EFIMAKEERR(10)
#define EFI_VOLUME_FULL EFIMAKEERR(11)
#define EFI_NO_MEDIA EFIMAKEERR(12)
#define EFI_MEDIA_CHANGED EFIMAKEERR(13)
#define EFI_NOT_FOUND EFIMAKEERR(14)
#define EFI_ACCESS_DENIED EFIMAKEERR(15)
#define EFI_NO_RESPONSE EFIMAKEERR(16)
#define EFI_NO_MAPPING EFIMAKEERR(17)
#define EFI_TIMEOUT EFIMAKEERR(18)
#define EFI_NOT_STARTED EFIMAKEERR(19)
#define EFI_ALREADY_STARTED EFIMAKEERR(20)
#define EFI_ABORTED EFIMAKEERR(21)
#define EFI_ICMP_ERROR EFIMAKEERR(22)
#define EFI_TFTP_ERROR EFIMAKEERR(23)
#define EFI_PROTOCOL_ERROR EFIMAKEERR(24)
#define EFI_INCOMPATIBLE_VERSION EFIMAKEERR(25)
#define EFI_SECURITY_VIOLATION EFIMAKEERR(26)
#define EFI_CRC_ERROR EFIMAKEERR(27)
#define EFI_END_OF_MEDIA EFIMAKEERR(28)
#define EFI_END_OF_FILE EFIMAKEERR(31)
#define EFI_INVALID_LANGUAGE EFIMAKEERR(32)
#define EFI_COMPROMISED_DATA EFIMAKEERR(33)
#define EFI_IP_ADDRESS_CONFLICT EFIMAKEERR(34)
#define EFI_HTTP_ERROR EFIMAKEERR(35)

#define EFI_WARN_UNKOWN_GLYPH (1)
#define EFI_WARN_DELETE_FAILURE (2)
#define EFI_WARN_WRITE_FAILURE (3)
#define EFI_WARN_BUFFER_TOO_SMALL (4)
#define EFI_WARN_STALE_DATA (5)
#define EFI_WARN_FILE_SYSTEM (6)
#define EFI_WARN_RESET_REQUIRED (7)

// time

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

// memory attributes

#define EFI_MEMORY_UC BIT(0)
#define EFI_MEMORY_WC BIT(1)
#define EFI_MEMORY_WT BIT(2)
#define EFI_MEMORY_WB BIT(3)
#define EFI_MEMORY_UCE BIT(4)
#define EFI_MEMORY_WP BIT(12)
#define EFI_MEMORY_RP BIT(13)
#define EFI_MEMORY_XP BIT(14)
#define EFI_MEMORY_NV BIT(15)
#define EFI_MEMORY_MORE_RELIABLE BIT(16)
#define EFI_MEMORY_RO BIT(17)
#define EFI_MEMORY_SP BIT(18)
#define EFI_MEMORY_CPU_CRYPTO BIT(19)
#define EFI_MEMORY_RUNTIME BIT(63)

#define EFI_MEMORY_ISA_VALID 0x4000000000000000ULL
#define EFI_MEMORY_ISA_MASK 0x0FFFF00000000000ULL

#define EFI_CACHE_ATTRIBUTE_MASK                                               \
  (EFI_MEMORY_UC | EFI_MEMORY_WC | EFI_MEMORY_WT | EFI_MEMORY_WB |             \
   EFI_MEMORY_UCE | EFI_MEMORY_WP)
#define EFI_MEMORY_ACCESS_MASK (EFI_MEMORY_RP | EFI_MEMORY_XP | EFI_MEMORY_RO)
#define EFI_MEMORY_ATTRIBUTE_MASK                                              \
  (EFI_MEMORY_ACCESS_MASK | EFI_MEMORY_SP | EFI_MEMORY_CPU_CRYPTO)

// events

#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

// task priority levels

#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

// capsule flags

#define CAPSULE_PERSIST_ACROSS_RESET BIT(16)
#define CAPSULE_POPULATE_SYSTEM_TABLE BIT(17)
#define CAPSULE_INITIATE_RESET BIT(18)

// variables

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI 0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION 0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED 0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED 0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED 0x0000000000000010
#define EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY 0x0000000000000040
#define EFI_OS_INDICATIONS_JSON_CONFIG_DATA_REFRESH 0x0000000000000080

namespace efi {

using Handle = void *;
using Status = uint64_t;

typedef struct Guid {
  uint32_t field1;
  uint16_t field2;
  uint16_t field3;
  uint8_t field4[8];

  bool operator==(Guid guid) {
    return __builtin_memcmp(this, &guid, sizeof(Guid)) == 0;
  }
} Guid;

namespace DevicePath {

typedef struct DevicePath {
  enum class NodeType : uint8_t {
    Undefined,
    Hardware,
    ACPI,
    Messaging,
    Media,
    BIOS,
    End = 0x7f
  } type;

  uint8_t subType;
  uint16_t length;
} DevicePath;

} // namespace DevicePath

namespace Memory {

enum class AllocationType : uint32_t {
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress
};

enum class Type : uint32_t {
  ReservedMemory,
  LoaderCode,
  LoaderData,
  BootServicesCode,
  BootServicesData,
  RuntimeServicesCode,
  RuntimeServicesData,
  ConventionalMemory,
  UnusableMemory,
  ACPIReclaimMemory,
  ACPIMemoryNVS,
  MemoryMappedIO,
  MemoryMappedIOPortSpace,
  PalCode,
  PersistentMemory
};

enum class PointerAttribute : uint32_t {
  None,
  Optional
};

typedef struct {
  Type type;
  uint32_t pad;
  uintptr_t physicalStart;
  uintptr_t virtualStart;
  uint64_t pageCount;
  uint64_t attribute;

  uint64_t reserved;
} Descriptor;

} // namespace Memory

namespace Event {

using TPL = uint64_t;
using Instance = void *;
using Callback = void(EFIAPI *)(I Instance event, I void *context);

enum class TimerDelayType : uint32_t {
  Cancel,
  Periodic,
  Relative
};

} // namespace Event

namespace Protocol {

enum class InterfaceType : uint32_t {
  Native
};

enum class SearchType : uint32_t {
  AllHandles,
  ByRegisterNotify,
  ByProtocol
};

typedef enum {
  ByHandleProtocol = BIT(0),
  GetProtocol = BIT(1),
  TestProtocol = BIT(2),
  ByChildContoller = BIT(3),
  ByDriver = BIT(4),
  Exclusive = BIT(5)
} OpenAttribute;

typedef struct {
  Handle agentHandle;
  Handle controllerHandle;
  uint32_t attributes;
  uint32_t openCount;
} ProtocolInformation;

} // namespace Protocol

namespace Time {

typedef struct {
  uint16_t year;  // 1998 - 20XX
  uint8_t month;  // 1 - 12
  uint8_t day;    // 1 - 31
  uint8_t hour;   // 0 - 23
  uint8_t minute; // 0 - 59
  uint8_t second; // 0 - 59
  uint8_t pad1;
  uint32_t nanosecond; // 0 - 999,999,999
  int16_t timeZone;    // -1440 to 1440 or 2047
  uint8_t daylight;
  uint8_t pad2;
} Time;

typedef struct {
  uint32_t resolution; // 1e-6 parts per million
  uint32_t accuracy;   // hertz
  bool setsToZero;     // Set clears sub-second time
} Capabilities;

} // namespace Time

namespace Capsule {

typedef struct {
  uint64_t length;
  union {
    uintptr_t dataBlock;
    uintptr_t continuationPointer;
  } unionBlock;
} BlockDescriptor;

typedef struct {
  Guid guid;
  uint32_t headerSize;
  uint32_t flags;
  uint32_t capsuleImageSize;
} Header;

} // namespace Capsule

enum class ResetType : uint32_t {
  Cold,
  Warm,
  Shutdown,
  PlatformSpecific
};

} // namespace efi

#include <efi/eficon.hpp>

namespace efi {

typedef struct {
  uint64_t signature;
  uint32_t revision;
  uint32_t headerSize;
  uint32_t crc32;
  uint32_t reserved;
} __Table;

typedef struct BootServices : public __Table {
  typedef Event::TPL(EFIAPI *RaiseTaskPriorityLevel)(I Event::TPL tpl);
  typedef void(EFIAPI *RestoreTaskPriorityLevel)(I Event::TPL tpl);

  typedef Status(EFIAPI *AllocatePages)(
      I Memory::AllocationType type,
      I Memory::Type memoryType,
      I uint64_t pageCount,
      I O void **memory
  );
  typedef Status(EFIAPI *FreePages)(I void *p, I uint64_t pageCount);
  typedef Status(EFIAPI *GetMemoryMap)(
      I O uint64_t *memoryMapSize,
      O Memory::Descriptor *memoryMap,
      O uint64_t *mapKey,
      O uint64_t *descriptorSize,
      O uint32_t *descriptorVersion
  );
  typedef Status(EFIAPI *AllocatePool)(
      I Memory::Type type,
      I size_t size,
      O void **buffer
  );
  typedef Status(EFIAPI *FreePool)(I void *p);

  typedef Status(EFIAPI *CreateEvent)(
      I uint32_t type,
      I Event::TPL tpl,
      I Event::Callback callback OPT,
      I void *context OPT,
      O Event::Instance *event
  );
  typedef Status(EFIAPI *CreateEventEx)(
      I uint32_t type,
      I Event::TPL notifyTpl,
      I Event::Callback callback OPT,
      I void *notifyContext OPT,
      I Guid eventGroup OPT,
      O Event::Instance *event
  );
  typedef Status(EFIAPI *SetTimer)(
      I Event::Instance event,
      I Event::TimerDelayType type,
      I uint64_t triggerTime
  );
  typedef Status(EFIAPI *SignalEvent)(I Event::Instance event);
  typedef Status(EFIAPI *WaitForEvent)(
      I uint64_t eventCount,
      I Event::Instance *eventList,
      O uint64_t *index
  );
  typedef Status(EFIAPI *CloseEvent)(I Event::Instance event);
  typedef Status(EFIAPI *CheckEvent)(I Event::Instance event);

  typedef Status(EFIAPI *
                     InstallProtocolInterface)(I O Handle *Handle, I Guid *protocolGuid, I Protocol::InterfaceType type, I void *interface);
  typedef Status(EFIAPI *ReinstallProtocolInterface)(
      I Handle handle,
      I Guid *protocolGuid,
      I void *oldInterface,
      I void *newInterface
  );
  typedef Status(EFIAPI *
                     UninstallProtocolInterface)(I Handle handle, I Guid *protocolGuid, I void *interface);
  typedef Status(EFIAPI *
                     HandleProtocol)(I Handle handle, I Guid *protocolGuid, O void **interface);
  typedef Status(EFIAPI *RegisterProtocolNotify)(
      I Guid *protocolGuid,
      I Event::Instance event,
      O void **registration
  );
  typedef Status(EFIAPI *LocateHandle)(
      I Protocol::SearchType searchType,
      I Guid *protocolGuid OPT,
      I void *searchKey OPT,
      I O uint64_t *handleCount,
      O Handle *handleList
  );
  typedef Status(EFIAPI *LocateDevicePath)(
      I Guid *protocolGuid,
      I O DevicePath::DevicePath **devicePath,
      O Handle *device
  );
  typedef Status(EFIAPI *InstallConfigurationTable)(
      I Guid *vendorGuid,
      I void *table
  );

  typedef Status(EFIAPI *LoadImage)(
      I bool bootPolicy,
      I Handle parentImageHandle,
      I DevicePath::DevicePath *imagePath OPT,
      I void *sourceBuffer OPT,
      I uint64_t sourceSize,
      O Handle *imageHandle
  );
  typedef Status(EFIAPI *StartImage)(
      I Handle imageHandle,
      O uint64_t *exitDataSize,
      O const char16_t **exitData
  );
  typedef Status(EFIAPI *Exit)(
      I Handle imageHandle,
      I Status status,
      I uint64_t exitDataSize,
      I const char16_t *exitData OPT
  );
  typedef Status(EFIAPI *ImageUnload)(I Handle imageHandle);
  typedef Status(EFIAPI *ExitBootServices)(
      I Handle imageHandle,
      I uint64_t mapKey
  );

  typedef Status(EFIAPI *GetNextMonotonicCount)(uint64_t *count);

  typedef Status(EFIAPI *Stall)(I uint64_t microseconds);
  typedef Status(EFIAPI *SetWatchdogTimer)(
      I uint64_t timeout,
      I uint64_t watchdogCode,
      I uint64_t dataSize,
      I const char16_t *watchdogData OPT
  );

  typedef Status(EFIAPI *ConnectController)(
      I Handle controllerHandle,
      I Handle *driverImageHandle OPT,
      I DevicePath::DevicePath *remainingDevicePath OPT,
      I bool recursive
  );
  typedef Status(EFIAPI *DisconnectController)(
      I Handle controllerHandle,
      I Handle driverImageHandle OPT,
      I Handle childHandle OPT
  );

  typedef Status(EFIAPI *OpenProtocol)(
      I Handle handle,
      I Guid *protocolGuid,
      O void **interface,
      I Handle agentHandle,
      I Handle controllerHandle,
      I uint32_t attributes
  );
  typedef Status(EFIAPI *CloseProtocol)(
      I Handle handle,
      I Guid *protocolGuid,
      I Handle agentHandle,
      I Handle controllerHandle
  );
  typedef Status(EFIAPI *OpenProtocolInfomation)(
      I Handle handle,
      I Guid *protocolGuid,
      O Protocol::ProtocolInformation **infomationList,
      O uint64_t *informationCount
  );
  typedef Status(EFIAPI *ProtocolsPerHandle)(
      I Handle handle,
      O Guid ***protocolList,
      O uint64_t *protocolCount
  );
  typedef Status(EFIAPI *LocateHandleBuffer)(
      I Protocol::SearchType searchType,
      I Guid *protocolGuid OPT,
      I void *searchKey OPT,
      O uint64_t *handleCount,
      O Handle **handleList
  );
  typedef Status(EFIAPI *
                     LocateProtocol)(I Guid *protocolGuid, I void *registration OPT, O void **interface);
  typedef Status(EFIAPI *InstallMultipleProtocolInterfaces)(
      I O Handle *handle,
      ...
  );
  typedef Status(EFIAPI *UninstallMultipleProtocolInterfaces)(
      I Handle handle,
      ...
  );

  typedef Status(EFIAPI *CalculateCrc32)(
      I void *data,
      I uint64_t dataSize,
      O uint32_t *crc32
  );

  typedef void(EFIAPI *Memcpy)(I void *dest, I void *src, I size_t size);
  typedef void(EFIAPI *Memset)(I void *buf, I size_t size, I uint8_t value);

  //	efi1.0+(revision>=0x00010000)

  RaiseTaskPriorityLevel raiseTaskPriorityLevel;
  RestoreTaskPriorityLevel restoreTaskPriorityLevel;

  AllocatePages allocatePages;
  FreePages freePages;
  GetMemoryMap getMemoryMap;
  AllocatePool allocatePool;
  FreePool freePool;

  CreateEvent createEvent;
  SetTimer setTimer;
  WaitForEvent waitForEvent;
  SignalEvent signalEvent;
  CloseEvent closeEvent;
  CheckEvent checkEvent;

  InstallProtocolInterface installProtocolInterface;
  ReinstallProtocolInterface reinstallProtocolInterface;
  UninstallProtocolInterface uninstallProtocolInterface;
  HandleProtocol handleProtocol;
  void *reserved;
  RegisterProtocolNotify registerProtocolNotify;
  LocateHandle locateHandle;
  LocateDevicePath locateDevicePath;
  InstallConfigurationTable installConfigurationTable;

  LoadImage loadImage;
  StartImage startImage;
  Exit exit;
  ImageUnload unloadImage;
  ExitBootServices exitBootServices;

  GetNextMonotonicCount getNextMonotonicCount;
  Stall stall;
  SetWatchdogTimer setWatchdogTimer;

  //	efi1.1+(revision>=0x00010010)

  ConnectController connectController;
  DisconnectController disconnectController;

  OpenProtocol openProtocol;
  CloseProtocol closeProtocol;
  OpenProtocolInfomation openProtocolInformation;

  ProtocolsPerHandle protocolsPerHandle;
  LocateHandleBuffer locateHandleBuffer;
  LocateProtocol locateProtocol;
  InstallMultipleProtocolInterfaces installMultipleProtocolInterfaces;
  UninstallMultipleProtocolInterfaces uninstallMultipleProtocolInterfaces;

  CalculateCrc32 calculateCrc32;

  Memcpy memcpy;
  Memset memset;

  //	uefi2.0+(revision>=0x00020000)

  CreateEventEx createEventEx;
} BootServices;

typedef struct RuntimeServices : public __Table {
  typedef Status(EFIAPI *GetTime)(
      O Time::Time *time,
      O Time::Capabilities *capabilities
  );
  typedef Status(EFIAPI *SetTime)(I Time::Time *time);
  typedef Status(EFIAPI *GetWakeupTime)(
      O bool *enabled,
      O bool *pending,
      O Time::Time *time
  );
  typedef Status(EFIAPI *SetWakeupTime)(I bool enable, I Time::Time *time OPT);

  typedef Status(EFIAPI *SetVirtualMemoryMap)(
      uint64_t memoryMapSize,
      uint64_t descriptorSize,
      uint32_t descriptorVersion,
      Memory::Descriptor *map
  );
  typedef Status(EFIAPI *ConvertRuntimePointer)(
      I Memory::PointerAttribute attribute,
      I O void **address
  );

  typedef Status(EFIAPI *GetVariable)(
      I const char16_t *variableName,
      I Guid *vendorGuid,
      O uint32_t *attributes OPT,
      I O uint64_t *dataSize,
      O void *data OPT
  );
  typedef Status(EFIAPI *GetNextVariableName)(
      I O uint64_t *variableNameSize,
      I O const char16_t *variableName,
      I O Guid *vendorGuid
  );
  typedef Status(EFIAPI *SetVariable)(
      I const char16_t *variableName,
      I Guid *vendorGuid,
      I uint32_t attributes,
      I uint64_t dataSize,
      I void *data
  );

  typedef Status(EFIAPI *UpdateCapsule)(
      I Capsule::Header **capsuleList,
      I uint64_t capsuleCount,
      I uintptr_t scatterGatherList OPT
  );
  typedef Status(EFIAPI *QueryCapsuleCapabilities)(
      I Capsule::Header **capsuleList,
      I uint64_t capsuleCount,
      O uint64_t *maximumCapsuleSize,
      O ResetType *requiredResetType
  );
  typedef Status(EFIAPI *QueryVariableInfo)(
      I uint32_t attributes,
      O uint64_t *maximumVariableStorageSize,
      O uint64_t *remainingVariableStorageSize,
      O uint64_t *maximumVariableSize
  );

  typedef Status(EFIAPI *GetNextHighMonotonicCount)(O uint32_t *count);
  typedef Status(EFIAPI *ResetSystem)(
      I ResetType type,
      I Status resetStatus,
      I uint64_t dataSize,
      I const char16_t *resetData OPT
  );

  GetTime getTime;
  SetTime setTime;
  GetWakeupTime getWakeupTime;
  SetWakeupTime setWakeupTime;

  SetVirtualMemoryMap setVirtualAddressMap;
  ConvertRuntimePointer convertPointer;

  GetVariable getVariable;
  GetNextVariableName getNextVariableName;
  SetVariable setVariable;

  GetNextHighMonotonicCount getNextHighMonotonicCount;
  ResetSystem resetSystem;

  //	uefi2.0+(revision>=0x00020000)

  UpdateCapsule updateCapsule;
  QueryCapsuleCapabilities queryCapsuleCapabilities;
  QueryVariableInfo queryVariableInfo;
} RuntimeServices;

typedef struct SystemTable : public __Table {
  const char16_t *firmwareVendor;
  uint32_t firmwareRevision;

  Handle stdinHandle;
  SimpleTextInputProtocol *stdin;

  Handle stdoutHandle;
  SimpleTextOutputProtocol *stdout;

  Handle stderrHandle;
  SimpleTextOutputProtocol *stderr;

  RuntimeServices *runtimeServices;
  BootServices *bootServices;

  typedef struct {
    uint64_t tableEntryCount;
    struct {
      Guid guid;
      void *table;
    } *tables;

    template <typename T> T *findTable(Guid guid) {
      for (uint64_t i = 0; i < tableEntryCount; ++i) {
        if (tables[i].guid == guid)
          return (T *)tables[i].table;
      }
      return nullptr;
    }

  } configurationTables;
} SystemTable;

} // namespace efi
