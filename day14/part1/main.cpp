#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// constexpr int recipes_num = 704321;

int add_to_board(std::vector<int> &board, int n) {
  std::string result = std::to_string(n);
  for (char score : result) {
    board.push_back(score - '0');
  }
  return result.size();
}

void print_board(const std::vector<int> &board, std::size_t i1,
                 std::size_t i2) {
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
  std::vector<int> board;

  std::size_t recipes_num;
  std::cin >> recipes_num;

  board.reserve(recipes_num + 20);
  board.push_back(3);
  board.push_back(7);

  std::size_t i1 = 0, i2 = 1;
  std::size_t recipes = 2;
  // print_board(board, i1, i2);
  while (true) {
    recipes += add_to_board(board, board[i1] + board[i2]);
    std::size_t steps1 = (board[i1] + 1) % board.size();
    std::size_t steps2 = (board[i2] + 1) % board.size();
    i1 = (i1 + steps1) % board.size();
    i2 = (i2 + steps2) % board.size();
    // print_board(board, i1, i2);
    if (recipes >= recipes_num + 10) {
      std::size_t j = recipes_num;
      for (int i = 0; i < 10; ++i) {
        std::cout << board[j++];
      }
      std::cout << '\n';
      break;
    }
  }
  return 0;
}
