#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string id;               // current id
  std::vector<std::string> ids; // all ids

  while (std::cin >> id) {
    ids.push_back(id);
  }

  bool found = false;
  for (std::size_t i = 0; i < ids.size(); ++i) {
    for (std::size_t j = i + 1; j < ids.size(); ++j) {
      // does two ids differ by exactly one character at the
      // same location?
      int differences = 0;
      for (std::size_t k = 0; k < ids[0].size(); ++k) {
        if (ids[i][k] != ids[j][k])
          ++differences;
      }
      if (differences == 1) {
        found = true;
        std::string result;
        for (std::size_t k = 0; k < ids[0].size(); ++k) {
          if (ids[i][k] == ids[j][k])
            result += ids[i][k];
        }
        std::cout << result << '\n';
        break;
      }
    }
    if (found)
      break;
  }
  return 0;
}
