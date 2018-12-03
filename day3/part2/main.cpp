#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Claim {
  int id;
  std::size_t xtl;
  std::size_t ytl;

  std::size_t xtr;
  std::size_t ytr;

  std::size_t xbl;
  std::size_t ybl;

  std::size_t xbr;
  std::size_t ybr;
};

int main() {
  std::vector<Claim> claims;
  std::size_t max_width = 0;
  std::size_t max_height = 0;

  std::string line;
  std::size_t left, top;
  std::size_t width, height;
  int id;

  while (std::scanf("%*c%d %*c %zu%*c%zu%*c %zu%*c%zu%*c", &id, &left, &top,
                    &width, &height) != EOF) {
    max_width = std::max(max_width, left + width);
    max_height = std::max(max_height, top + height);
    claims.push_back(Claim{id, left, top, left + width - 1, top, left,
                           top + height - 1, left + width - 1,
                           top + height - 1});
  }

  std::vector<std::vector<int>> fabric(max_height + 2,
                                       std::vector<int>(max_width + 2, 0));

  std::unordered_map<int, bool> id_overlap; // id -> is_overlapped

  for (const Claim &c : claims) {
    id_overlap[c.id] = false;
    for (std::size_t y = c.ytl; y <= c.ybl; ++y) {
      for (std::size_t x = c.xtl; x <= c.xtr; ++x) {
        if (fabric[y][x] == 0) { // empty space
          fabric[y][x] = c.id;
        } else if (fabric[y][x] != 0) {
          if (fabric[y][x] != -1) {
            id_overlap[fabric[y][x]] = true;
          }
          id_overlap[c.id] = true;
          fabric[y][x] = -1; // set intersection
        }
      }
    }
  }
  for (const auto &[id, overlap] : id_overlap) {
    if (!overlap) {
      std::cout << id << std::endl;
    }
  }
  return 0;
}
