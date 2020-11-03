#pragma once
#include <cstdint>
#include <cstring>
namespace ColoringElements {
  namespace Utils{
    class BitArray {
     private:
      uint32_t _word;
     public:
      BitArray() : _word(1) { };

      inline void Clear() { _word = 1;}
      inline void setBit(const int n) { _word |= 1 << n; }

      int findFirstFalse() {
        auto complementaryWord = ~_word;
        return ffs(complementaryWord)-1;
      }
    };
  }
}
