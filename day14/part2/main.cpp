#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

std::size_t add_to_board(std::string &board, int n) {
  std::string result = std::to_string(n);
  board.append(result);
  return result.size();
}

void print_board(const std::string &board, std::size_t i1, std::size_t i2) {
  for (std::size_t i = 0; i < board.size(); ++i) {
    if (i == i1) {
      std::cout << "(" << board[i] << ") ";
    } else if (i == i2) {
      std::cout << "[" << board[i] << "] ";
    } else {
      std::cout << board[i] << " ";
    }
  }
  std::cout << '\n';
}

int main() {
  std::string pattern;
  std::cin >> pattern;

  std::string board = "37";
  std::size_t i1 = 0, i2 = 1;
  // print_board(board, i1, i2);

  std::size_t from = 0;
  bool found = false;
  std::size_t indx;

  while (!found) {
    add_to_board(board, (board[i1] - '0') + (board[i2] - '0'));
    int steps1 = ((board[i1] - '0') + 1) % board.size();
    int steps2 = ((board[i2] - '0') + 1) % board.size();
    i1 = (i1 + steps1) % board.size();
    i2 = (i2 + steps2) % board.size();

    if ((board.size() - from) >= pattern.size()) {
      indx = board.find(pattern, from);
      if (indx != std::string::npos) {
        found = true;
      } else {
        std::size_t i = from + 1;
        for (; i < board.size(); ++i) {
          if (board[i] == pattern[0]) {
            break;
          }
        }
        from = i;
      }
    }
    // print_board(board, i1, i2);
  }
  if (found) {
    std::cout << indx << '\n';
  }
  return 0;
}
