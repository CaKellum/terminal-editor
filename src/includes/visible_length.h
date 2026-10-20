#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

// MARK: Byte classification
// A byte is invisible iff its table entry has no PRINTABLE bit.
enum ByteClass : std::uint8_t {
  PRINTABLE = 1 << 0, // 0x20-0x7E and UTF-8 lead bytes (0xC0+)
  CSI_PARAM = 1 << 1, // 0x30-0x3F (digits, ';')
  CSI_INTER = 1 << 2, // 0x20-0x2F
  CSI_FINAL = 1 << 3, // 0x40-0x7E
};

constexpr std::array<std::uint8_t, 256> makeByteTable() {
  std::array<std::uint8_t, 256> table{};
  for (int b = 0; b < 256; b++) {
    std::uint8_t flags = 0;
    if (b >= 0x20 && b <= 0x7E) {
      flags |= PRINTABLE;
    }
    // UTF-8 lead bytes count as one visible char; continuation
    // bytes (0x80-0xBF) get no PRINTABLE bit and stay invisible.
    if (b >= 0xC0) {
      flags |= PRINTABLE;
    }
    if (b >= 0x30 && b <= 0x3F) {
      flags |= CSI_PARAM;
    }
    if (b >= 0x20 && b <= 0x2F) {
      flags |= CSI_INTER;
    }
    if (b >= 0x40 && b <= 0x7E) {
      flags |= CSI_FINAL;
    }
    table[b] = flags;
  }
  return table;
}

inline constexpr std::array<std::uint8_t, 256> byteTable = makeByteTable();

// MARK: ANSI sequence parsing
// States: Text -> Esc -> Csi -> Text
//                  \-> Osc -> OscEsc (OSC ends on BEL or ST = ESC \)
enum class AnsiState { Text, Esc, Csi, Osc, OscEsc };

constexpr std::uint8_t ESC = 0x1B;
constexpr std::uint8_t BEL = 0x07;

inline bool isInvisible(unsigned char b) { return !(byteTable[b] & PRINTABLE); }

// CSI final bytes that move the cursor horizontally (CUF/CUB/CHA),
// matching the column functions in asciiconsts.h.
inline bool isColumnMoveFinal(unsigned char b) {
  return b == 'C' || b == 'D' || b == 'G';
}

inline std::size_t visibleLength(const std::string &s) {
  std::size_t visible = 0;
  AnsiState state = AnsiState::Text;
  std::size_t csiParam = 0;
  bool hasParam = false, paramDone = false;
  for (unsigned char b : s) {
    std::uint8_t cls = byteTable[b];
    switch (state) {
    case AnsiState::Text:
      if (b == ESC) {
        state = AnsiState::Esc;
      } else if (cls & PRINTABLE) {
        visible++;
      }
      break;
    case AnsiState::Esc:
      if (b == '[') {
        state = AnsiState::Csi;
        csiParam = 0;
        hasParam = false;
        paramDone = false;
      } else if (b == ']') {
        state = AnsiState::Osc;
      } else if (cls & CSI_INTER) {
        // intermediate byte, stay in Esc
      } else {
        state = AnsiState::Text; // final byte consumed
      }
      break;
    case AnsiState::Csi:
      if (cls & CSI_FINAL) {
        if (isColumnMoveFinal(b)) {
          // A column movement advances the cursor, so its distance
          // occupies visible columns instead of invisible bytes.
          visible += hasParam ? csiParam : 1;
        }
        state = AnsiState::Text;
      } else if (!paramDone) {
        if (b >= '0' && b <= '9') {
          csiParam = csiParam * 10 + (b - '0');
          hasParam = true;
        } else if (b == ';') {
          paramDone = true; // only the first parameter matters
        }
      }
      break;
    case AnsiState::Osc:
      if (b == BEL) {
        state = AnsiState::Text;
      } else if (b == ESC) {
        state = AnsiState::OscEsc;
      }
      break;
    case AnsiState::OscEsc:
      if (b == '\\') {
        state = AnsiState::Text; // ST completed
      } else if (b != ESC) {
        state = AnsiState::Osc; // false alarm, still in OSC
      }
      break;
    }
  }
  return visible;
}

// Count of bytes that don't render as their own character:
// control bytes, escape sequence bytes, and UTF-8 continuations.
// Column movements (CSI n C/D/G) are excluded: their distance
// counts as visible columns in visibleLength.
inline std::size_t invisibleCount(const std::string &s) {
  return s.size() - visibleLength(s);
}
