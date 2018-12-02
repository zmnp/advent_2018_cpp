#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::string id;   // current id
  int counter2 = 0; // number of ids containing exactly two of any letter
  int counter3 = 0; // number of ids containing exactly three of any letter

  while (std::cin >> id) {
    std::unordered_map<char, int> letters_count;
    for (const char c : id) {
      ++letters_count[c];
    }

    int exactly_2_of_any_letter = 0;
    int exaclty_3_of_any_letter = 0;

    for (const auto &[letter, counter] : letters_count) {
      if (counter == 2)
        ++exactly_2_of_any_letter;
      if (counter == 3)
        ++exaclty_3_of_any_letter;
    }
    if (exactly_2_of_any_letter)
      ++counter2;
    if (exaclty_3_of_any_letter)
      ++counter3;
  }

  std::cout << (counter2 * counter3) << '\n';
  return 0;
}
