#ifndef RANDOM_H
#define RANDOM_H

#include <random>
namespace Engine::Random {
inline std::random_device SEEDER;
inline std::mt19937 ENGINE{SEEDER()};

inline size_t Int(size_t min, size_t max) {
  std::uniform_int_distribution get{min, max};
  return get(ENGINE);
}
} // namespace Engine::Random
#endif
