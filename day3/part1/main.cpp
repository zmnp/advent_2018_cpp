#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::vector<char>> &m) {

  for (std::size_t y = 0; y < m.size(); ++y) {
    for (std::size_t x = 0; x < m[0].size(); ++x) {
      std::cout << m[y][x];
    }
    std::cout << std::endl;
  }
}

struct Claim {
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

  while (std::scanf("%*c%*d %*c %zu%*c%zu%*c %zu%*c%zu%*c", &left, &top, &width,
                    &height) != EOF) {
    max_width = std::max(max_width, left + width);
    max_height = std::max(max_height, top + height);
    claims.push_back(Claim{left, top, left + width - 1, top, left,
                           top + height - 1, left + width - 1,
                           top + height - 1});
  }

  std::vector<std::vector<char>> fabric(max_height + 2,
                                        std::vector<char>(max_width + 2, '.'));

  std::size_t result = 0;
  for (const Claim &c : claims) {
    for (std::size_t y = c.ytl; y <= c.ybl; ++y) {
      for (std::size_t x = c.xtl; x <= c.xtr; ++x) {
        if (fabric[y][x] == '#') {
          fabric[y][x] = 'x';
          ++result;
        } else if (fabric[y][x] == '.') {
          fabric[y][x] = '#';
        }
      }
    }
  }
  std::printf("%zu\n", result);
  return 0;
}
