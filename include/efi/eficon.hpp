#pragma once

#ifndef __UEFIPLUS64__
#error "do not include eficon.hpp directly, use efi.hpp instead"
#endif

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID                                   \
  {                                                                            \
    0x387477c2, 0x69c7, 0x11d2, {                                              \
      0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b                            \
    }                                                                          \
  }

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID                                    \
  {                                                                            \
    0x387477c1, 0x69c7, 0x11d2, {                                              \
      0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b                            \
    }                                                                          \
  }

#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN (EFI_BLUE | EFI_GREEN)
#define EFI_RED 0x04
#define EFI_MAGENTA (EFI_BLUE | EFI_RED)
#define EFI_BROWN (EFI_GREEN | EFI_RED)
#define EFI_LIGHTGRAY (EFI_BLUE | EFI_GREEN | EFI_RED)
#define EFI_BRIGHT 0x08
#define EFI_DARKGRAY (EFI_BRIGHT)
#define EFI_LIGHTBLUE (EFI_BLUE | EFI_BRIGHT)
#define EFI_LIGHTGREEN (EFI_GREEN | EFI_BRIGHT)
#define EFI_LIGHTCYAN (EFI_CYAN | EFI_BRIGHT)
#define EFI_LIGHTRED (EFI_RED | EFI_BRIGHT)
#define EFI_LIGHTMAGENTA (EFI_MAGENTA | EFI_BRIGHT)
#define EFI_YELLOW (EFI_BROWN | EFI_BRIGHT)
#define EFI_WHITE (EFI_BLUE | EFI_GREEN | EFI_RED | EFI_BRIGHT)

#define EFI_TEXT_ATTR(f, b) ((f) | ((b) << 4))

#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_GREEN)
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_BROWN (EFI_BACKGROUND_GREEN | EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_LIGHTGRAY                                               \
  (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_GREEN | EFI_BACKGROUND_RED)

#define BOXDRAW_HORIZONTAL 0x2500
#define BOXDRAW_VERTICAL 0x2502
#define BOXDRAW_DOWN_RIGHT 0x250c
#define BOXDRAW_DOWN_LEFT 0x2510
#define BOXDRAW_UP_RIGHT 0x2514
#define BOXDRAW_UP_LEFT 0x2518
#define BOXDRAW_VERTICAL_RIGHT 0x251c
#define BOXDRAW_VERTICAL_LEFT 0x2524
#define BOXDRAW_DOWN_HORIZONTAL 0x252c
#define BOXDRAW_UP_HORIZONTAL 0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL 0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL 0x2550
#define BOXDRAW_DOUBLE_VERTICAL 0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE 0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT 0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT 0x2554

#define BOXDRAW_DOWN_LEFT_DOUBLE 0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT 0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT 0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE 0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT 0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT 0x255a

#define BOXDRAW_UP_LEFT_DOUBLE 0x255b
#define BOXDRAW_UP_DOUBLE_LEFT 0x255c
#define BOXDRAW_DOUBLE_UP_LEFT 0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE 0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT 0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT 0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE 0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT 0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT 0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE 0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL 0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL 0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

#define BLOCKELEMENT_FULL_BLOCK 0x2588
#define BLOCKELEMENT_LIGHT_SHADE 0x2591

#define GEOMETRICSHAPE_UP_TRIANGLE 0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE 0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE 0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE 0x25c4

#define ARROW_UP 0x2191
#define ARROW_DOWN 0x2193

//

#define CHAR_NULL 0x00
#define CHAR_BACKSPACE 0x08
#define CHAR_TAB 0x09
#define CHAR_LINEFEED 0x0A
#define CHAR_CARRIAGE_RETURN 0x0D

#define SCAN_NULL 0x00
#define SCAN_UP 0x01
#define SCAN_DOWN 0x02
#define SCAN_RIGHT 0x03
#define SCAN_LEFT 0x04
#define SCAN_HOME 0x05
#define SCAN_END 0x06
#define SCAN_INSERT 0x07
#define SCAN_DELETE 0x08
#define SCAN_PAGE_UP 0x09
#define SCAN_PAGE_DOWN 0x0A
#define SCAN_F1 0x0B
#define SCAN_F2 0x0C
#define SCAN_F3 0x0D
#define SCAN_F4 0x0E
#define SCAN_F5 0x0F
#define SCAN_F6 0x10
#define SCAN_F7 0x11
#define SCAN_F8 0x12
#define SCAN_F9 0x13
#define SCAN_F10 0x14
#define SCAN_F11 0x15
#define SCAN_F12 0x16
#define SCAN_ESC 0x17

namespace efi {

template <typename T>
using TextReset = Status(EFIAPI *)(I T *instance, I bool extendedVerification);

typedef struct SimpleTextOutputProtocol {
  typedef struct {
    int32_t maxMode;

    int32_t mode;
    int32_t attribute;
    int32_t cursorColumn;
    int32_t cursorRow;
    bool cursorVisible;
  } OptputMode;

  typedef Status(EFIAPI *OutputString)(
      I struct SimpleTextOutputProtocol *instance,
      I const char16_t *string
  );
  typedef Status(EFIAPI *TestString)(
      I struct SimpleTextOutputProtocol *instance,
      I const char16_t *string
  );
  typedef Status(EFIAPI *QueryMode)(
      I struct SimpleTextOutputProtocol *instance,
      I uint64_t modeNumber,
      O uint64_t *columns,
      O uint64_t *rows
  );
  typedef Status(EFIAPI *SetMode)(
      I struct SimpleTextOutputProtocol *instance,
      I uint64_t modeNumber
  );
  typedef Status(EFIAPI *SetAttribute)(
      I struct SimpleTextOutputProtocol *instance,
      I uint64_t attribute
  );
  typedef Status(EFIAPI *ClearScreen)(
      I struct SimpleTextOutputProtocol *instance
  );
  typedef Status(EFIAPI *SetCursorPosition)(
      I struct SimpleTextOutputProtocol *instance,
      I uint64_t column,
      I uint64_t row
  );
  typedef Status(EFIAPI *EnableCursor)(
      I struct SimpleTextOutputProtocol *instance,
      I bool enable
  );

  TextReset<struct SimpleTextOutputProtocol> reset;

  OutputString outputString;
  TestString testString;

  QueryMode queryMode;
  SetMode setMode;
  SetAttribute setAttribute;

  ClearScreen clearScreen;
  SetCursorPosition setCursorPosition;
  EnableCursor enableCursor;

  OptputMode *currentMode;
} SimpleTextOutputProtocol;

typedef struct SimpleTextInputProtocol {
  typedef struct {
    uint16_t scanCode;
    char16_t unicodeChar;
  } InputKey;

  typedef Status(EFIAPI *InputReadKey)(
      I struct SimpleTextInputProtocol *instance,
      O InputKey *key
  );

  TextReset<struct SimpleTextInputProtocol> reset;
  InputReadKey readKeyStroke;
  Event::Instance waitForKey;
} SimpleTextInputProtocol;

} // namespace efi