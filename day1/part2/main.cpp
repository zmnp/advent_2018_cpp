#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
  int64_t cfreq = 0;                     // current frequency
  int64_t freq_change;                   // frequency change
  std::unordered_set<int64_t> freq_seen; // frequencies seen so far
  std::vector<int64_t> freq_changes;     // all frequency changes

  while (std::cin >> freq_change) {
    freq_changes.push_back(freq_change);
  }

  bool found = false; // was dup frequency found?
  while (!found) {
    for (const int64_t fc : freq_changes) {
      cfreq += fc;
      if (freq_seen.count(cfreq)) {
        found = true;
        break;
      }
      freq_seen.insert(cfreq);
    }
  }
  if (found)
    std::cout << cfreq << '\n';
  return 0;
}
