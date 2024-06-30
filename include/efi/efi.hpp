#pragma once

#define __UEFIPLUS64__ 1

#include <cstddef>
#include <cstdint>
#include <sys/types.h>

#define IN       /* input param */
#define OUT      /* output param */
#define OPTIONAL /* optional param */

#define BIT(n) (1ull << (n))
#define EFIAPI __attribute__((ms_abi))

#define EFIMAKEERR(a) (a | BIT(63))
#define EFICUSTOMERR(a) (a | BIT(63) | BIT(62))
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

// custom error codes(not in uefi spec)

#define ERR_INVAILD_STATE EFICUSTOMERR(0)

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
  (EFI_MEMORY_UC | EFI_MEMORY_WC | EFI_MEMORY_WT | EFI_MEMORY_WB               \
   | EFI_MEMORY_UCE | EFI_MEMORY_WP)
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
using Callback = void(EFIAPI *)(IN Instance event, IN void *context);

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

template <typename T> class ListNode {
  T *_prev;
  T *_next;

public:
  class iterator {
    T *ptr;

  public:
    iterator(T *p) { this->ptr = p; }
    T *operator++() {
      this->ptr = (T *)((ListNode *)this->ptr)->_next;
      return this->ptr;
    }
    bool operator!=(iterator &it) { return this->ptr != it.ptr; }
    T operator*() { return *ptr; }
  };

  void init() {
    this->_prev = (T *)this;
    this->_next = (T *)this;
  }

  template <typename R = T> R *push_front(ListNode *entry) {
    entry->_next = (T *)this->_next;
    entry->_prev = (T *)this;
    entry->_next->_prev = (T *)entry;
    this->_next = (T *)entry;

    return (R *)this;
  }

  template <typename R = T> R *push_back(ListNode *entry) {
    entry->_next = (T *)this;
    entry->_prev = (T *)this->_prev;
    entry->_prev->_next = (T *)entry;
    this->_prev = (T *)entry;

    return (R *)this;
  }

  template <typename R = T> R *remove() {
    if (this->empty()) {
      return this;
    }

    this->_next->_prev = (T *)this->_prev;
    this->_prev->_next = (T *)this->_next;

    return (R *)this->_next;
  }

  template <typename R = T> constexpr R *prev() { return (R *)this->_prev; }

  template <typename R = T> constexpr R *next() { return (R *)this->_next; }

  iterator begin() { return (T *)this->_next; }

  iterator end() { return (T *)this; }

  bool empty() { return this->_next == this; }
};

} // namespace efi

#include <efi/protocol/console.hpp>

namespace efi {

typedef struct {
  uint64_t signature;
  uint32_t revision;
  uint32_t headerSize;
  uint32_t crc32;
  uint32_t reserved;
} __Table;

typedef struct BootServices : public __Table {
  typedef Event::TPL(EFIAPI *RaiseTaskPriorityLevel)(IN Event::TPL tpl);
  typedef void(EFIAPI *RestoreTaskPriorityLevel)(IN Event::TPL tpl);

  typedef Status(EFIAPI *AllocatePages)(
      IN Memory::AllocationType type,
      IN Memory::Type memoryType,
      IN uint64_t pageCount,
      IN OUT void **memory
  );
  typedef Status(EFIAPI *FreePages)(IN void *p, IN uint64_t pageCount);
  typedef Status(EFIAPI *GetMemoryMap)(
      IN OUT uint64_t *memoryMapSize,
      OUT Memory::Descriptor *memoryMap,
      OUT uint64_t *mapKey,
      OUT uint64_t *descriptorSize,
      OUT uint32_t *descriptorVersion
  );
  typedef Status(EFIAPI *AllocatePool)(
      IN Memory::Type type,
      IN size_t size,
      OUT void **buffer
  );
  typedef Status(EFIAPI *FreePool)(IN void *p);

  typedef Status(EFIAPI *CreateEvent)(
      IN uint32_t type,
      IN Event::TPL tpl,
      IN Event::Callback callback OPTIONAL,
      IN void *context OPTIONAL,
      OUT Event::Instance *event
  );
  typedef Status(EFIAPI *CreateEventEx)(
      IN uint32_t type,
      IN Event::TPL notifyTpl,
      IN Event::Callback callback OPTIONAL,
      IN void *notifyContext OPTIONAL,
      IN Guid eventGroup OPTIONAL,
      OUT Event::Instance *event
  );
  typedef Status(EFIAPI *SetTimer)(
      IN Event::Instance event,
      IN Event::TimerDelayType type,
      IN uint64_t triggerTime
  );
  typedef Status(EFIAPI *SignalEvent)(IN Event::Instance event);
  typedef Status(EFIAPI *WaitForEvent)(
      IN uint64_t eventCount,
      IN Event::Instance *eventList,
      OUT uint64_t *index
  );
  typedef Status(EFIAPI *CloseEvent)(IN Event::Instance event);
  typedef Status(EFIAPI *CheckEvent)(IN Event::Instance event);

  typedef Status(EFIAPI *
                     InstallProtocolInterface)(IN OUT Handle *Handle, IN Guid *protocolGuid, IN Protocol::InterfaceType type, IN void *interface);
  typedef Status(EFIAPI *ReinstallProtocolInterface)(
      IN Handle handle,
      IN Guid *protocolGuid,
      IN void *oldInterface,
      IN void *newInterface
  );
  typedef Status(EFIAPI *
                     UninstallProtocolInterface)(IN Handle handle, IN Guid *protocolGuid, IN void *interface);
  typedef Status(EFIAPI *
                     HandleProtocol)(IN Handle handle, IN Guid *protocolGuid, OUT void **interface);
  typedef Status(EFIAPI *RegisterProtocolNotify)(
      IN Guid *protocolGuid,
      IN Event::Instance event,
      OUT void **registration
  );
  typedef Status(EFIAPI *LocateHandle)(
      IN Protocol::SearchType searchType,
      IN Guid *protocolGuid OPTIONAL,
      IN void *searchKey OPTIONAL,
      IN OUT uint64_t *handleCount,
      OUT Handle *handleList
  );
  typedef Status(EFIAPI *LocateDevicePath)(
      IN Guid *protocolGuid,
      IN OUT DevicePath **devicePath,
      OUT Handle *device
  );
  typedef Status(EFIAPI *InstallConfigurationTable)(
      IN Guid *vendorGuid,
      IN void *table
  );

  typedef Status(EFIAPI *LoadImage)(
      IN bool bootPolicy,
      IN Handle parentImageHandle,
      IN DevicePath *imagePath OPTIONAL,
      IN void *sourceBuffer OPTIONAL,
      IN uint64_t sourceSize,
      OUT Handle *imageHandle
  );
  typedef Status(EFIAPI *StartImage)(
      IN Handle imageHandle,
      OUT uint64_t *exitDataSize,
      OUT const char16_t **exitData
  );
  typedef Status(EFIAPI *Exit)(
      IN Handle imageHandle,
      IN Status status,
      IN uint64_t exitDataSize,
      IN const char16_t *exitData OPTIONAL
  );
  typedef Status(EFIAPI *ImageUnload)(IN Handle imageHandle);
  typedef Status(EFIAPI *ExitBootServices)(
      IN Handle imageHandle,
      IN uint64_t mapKey
  );

  typedef Status(EFIAPI *GetNextMonotonicCount)(uint64_t *count);

  typedef Status(EFIAPI *Stall)(IN uint64_t microseconds);
  typedef Status(EFIAPI *SetWatchdogTimer)(
      IN uint64_t timeout,
      IN uint64_t watchdogCode,
      IN uint64_t dataSize,
      IN const char16_t *watchdogData OPTIONAL
  );

  typedef Status(EFIAPI *ConnectController)(
      IN Handle controllerHandle,
      IN Handle *driverImageHandle OPTIONAL,
      IN DevicePath *remainingDevicePath OPTIONAL,
      IN bool recursive
  );
  typedef Status(EFIAPI *DisconnectController)(
      IN Handle controllerHandle,
      IN Handle driverImageHandle OPTIONAL,
      IN Handle childHandle OPTIONAL
  );

  typedef Status(EFIAPI *OpenProtocol)(
      IN Handle handle,
      IN Guid *protocolGuid,
      OUT void **interface,
      IN Handle agentHandle,
      IN Handle controllerHandle,
      IN uint32_t attributes
  );
  typedef Status(EFIAPI *CloseProtocol)(
      IN Handle handle,
      IN Guid *protocolGuid,
      IN Handle agentHandle,
      IN Handle controllerHandle
  );
  typedef Status(EFIAPI *OpenProtocolInfomation)(
      IN Handle handle,
      IN Guid *protocolGuid,
      OUT Protocol::ProtocolInformation **infomationList,
      OUT uint64_t *informationCount
  );
  typedef Status(EFIAPI *ProtocolsPerHandle)(
      IN Handle handle,
      OUT Guid ***protocolList,
      OUT uint64_t *protocolCount
  );
  typedef Status(EFIAPI *LocateHandleBuffer)(
      IN Protocol::SearchType searchType,
      IN Guid *protocolGuid OPTIONAL,
      IN void *searchKey OPTIONAL,
      OUT uint64_t *handleCount,
      OUT Handle **handleList
  );
  typedef Status(EFIAPI *
                     LocateProtocol)(IN Guid *protocolGuid, IN void *registration OPTIONAL, OUT void **interface);
  typedef Status(EFIAPI *InstallMultipleProtocolInterfaces)(
      IN OUT Handle *handle,
      ...
  );
  typedef Status(EFIAPI *UninstallMultipleProtocolInterfaces)(
      IN Handle handle,
      ...
  );

  typedef Status(EFIAPI *CalculateCrc32)(
      IN void *data,
      IN uint64_t dataSize,
      OUT uint32_t *crc32
  );

  typedef void(EFIAPI *Memcpy)(IN void *dest, IN void *src, IN size_t size);
  typedef void(EFIAPI *Memset)(IN void *buf, IN size_t size, IN uint8_t value);

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
      OUT Time::Time *time,
      OUT Time::Capabilities *capabilities
  );
  typedef Status(EFIAPI *SetTime)(IN Time::Time *time);
  typedef Status(EFIAPI *GetWakeupTime)(
      OUT bool *enabled,
      OUT bool *pending,
      OUT Time::Time *time
  );
  typedef Status(EFIAPI *SetWakeupTime)(
      IN bool enable,
      IN Time::Time *time OPTIONAL
  );

  typedef Status(EFIAPI *SetVirtualMemoryMap)(
      uint64_t memoryMapSize,
      uint64_t descriptorSize,
      uint32_t descriptorVersion,
      Memory::Descriptor *map
  );
  typedef Status(EFIAPI *ConvertRuntimePointer)(
      IN Memory::PointerAttribute attribute,
      IN OUT void **address
  );

  typedef Status(EFIAPI *GetVariable)(
      IN const char16_t *variableName,
      IN Guid *vendorGuid,
      OUT uint32_t *attributes OPTIONAL,
      IN OUT uint64_t *dataSize,
      OUT void *data OPTIONAL
  );
  typedef Status(EFIAPI *GetNextVariableName)(
      IN OUT uint64_t *variableNameSize,
      IN OUT const char16_t *variableName,
      IN OUT Guid *vendorGuid
  );
  typedef Status(EFIAPI *SetVariable)(
      IN const char16_t *variableName,
      IN Guid *vendorGuid,
      IN uint32_t attributes,
      IN uint64_t dataSize,
      IN void *data
  );

  typedef Status(EFIAPI *UpdateCapsule)(
      IN Capsule::Header **capsuleList,
      IN uint64_t capsuleCount,
      IN uintptr_t scatterGatherList OPTIONAL
  );
  typedef Status(EFIAPI *QueryCapsuleCapabilities)(
      IN Capsule::Header **capsuleList,
      IN uint64_t capsuleCount,
      OUT uint64_t *maximumCapsuleSize,
      OUT ResetType *requiredResetType
  );
  typedef Status(EFIAPI *QueryVariableInfo)(
      IN uint32_t attributes,
      OUT uint64_t *maximumVariableStorageSize,
      OUT uint64_t *remainingVariableStorageSize,
      OUT uint64_t *maximumVariableSize
  );

  typedef Status(EFIAPI *GetNextHighMonotonicCount)(OUT uint32_t *count);
  typedef Status(EFIAPI *ResetSystem)(
      IN ResetType type,
      IN Status resetStatus,
      IN uint64_t dataSize,
      IN const char16_t *resetData OPTIONAL
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
