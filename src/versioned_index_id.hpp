#pragma once

#include <cstddef>
#include <cstdint>

template <typename T = int32_t, std::size_t VERSION_BITS = 8, std::size_t INDEX_BITS = sizeof(T) * 8 - VERSION_BITS>
struct VersionedIndexId {
  union Union {
    T id;
    struct {
      T version : VERSION_BITS;
      T index : INDEX_BITS;
    };
  };

  static T create(T index) { return Union { .index = index }.id; }
  static T create(T index, T version) { return Union { .version = version, .index = index, }.id; }
  static T index(T id) { return Union { .id = id, }.index; }
  static T version(T id) { return Union { .id = id, }.version; }
  static T increase_version(T id) {
    Union u { .id = id};
    u.version = u.version + 1 & ((1 << VERSION_BITS) - 1);
    return u.id;
  }
};
