#include <cstdint>
#include <iostream>

int main() {
  int64_t result = 0; // resulting frequency

  int64_t freq_change; // frequency change
  while (std::cin >> freq_change) {
    result += freq_change;
  }
  std::cout << result << '\n';
  return 0;
}
