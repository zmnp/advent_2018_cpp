#include <cstddef>
#include <iostream>
#include <vector>
#include <cstdint>

/* calc_sum: calculates sum of metadata entries of the tree and saves it in sum variable,
 * indx - index of the current node, 0 - root node
 * returns index of the next node in the tree array
 */
std::size_t calc_sum(const std::vector<int> &tree, std::size_t indx,
                     std::int64_t &sum) {
  std::size_t nodes_q = tree[indx];   // quantity of child nodes
  std::size_t mde_q = tree[indx + 1]; // quantity of metadata entries

  if (nodes_q == 0) { // no child nodes, this is a leaf
    std::size_t i = indx + 2;
    // read metadata entries and calculate sum
    for (std::size_t m = 0; m < mde_q; ++m) {
      sum += tree[i];
      ++i;
    }
    return i; // i points to begining of next node
  }
  // find each child node of the tree[indx] node
  indx += 2;
  for (std::size_t n = 0; n < nodes_q; ++n) {
    indx = calc_sum(tree, indx, sum);
  }
  // read metadata entries and calculate sum
  std::size_t i = indx;
  for (std::size_t m = 0; m < mde_q; ++m) {
    sum += tree[i];
    ++i;
  }
  return i; // i points to begining of next node
}

int main() {
  std::vector<int> tree;

  int node;
  while (std::cin >> node) {
    tree.push_back(node);
  }

  std::int64_t sum = 0; // sum of metadata entries
  // indx = 0 is a root of a tree
  calc_sum(tree, 0, sum);
  std::cout << sum << '\n';
  return 0;
}
