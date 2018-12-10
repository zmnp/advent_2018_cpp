#include <cstdint>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Node_info {
  std::vector<std::size_t> child_nodes; // ids of child nodes
  std::vector<int> metadata_entries;    // metadata entries of a node
  std::int64_t value;                   // value of a node
};

/* traverse_tree: traverses tree, generates ids for each node,
 * saves information of each node in nodes variable as ID -> Node_info.
 * id - id of the current node, 0 - root node,
 * indx - index of the current node in tree array, 0 - root node
 * returns index of the next node in the tree array
 */
int traverse_tree(const std::vector<int> &tree,
                  std::unordered_map<int, Node_info> &nodes, int id,
                  std::size_t indx) {
  int static next_id = 0;             // id of the next node
  std::size_t nodes_q = tree[indx];   // quantity of child nodes
  std::size_t mde_q = tree[indx + 1]; // quantity of metadata entries

  if (nodes_q == 0) { // no child nodes, this is a leaf
    std::size_t i = indx + 2;
    // read metadata entries and save it for the current node
    // which is identified by id
    for (std::size_t m = 0; m < mde_q; ++m) {
      nodes[id].metadata_entries.push_back(tree[i]);
      ++i;
    }
    nodes[id].value = -1; // we will calculate value of this node later

    return i; // i points to begining of next node
  }

  // find each child node of the tree[indx] node
  indx += 2;
  for (std::size_t n = 0; n < nodes_q; ++n) {
    int new_node_id = ++next_id; // generate next id for new node
    nodes[id].child_nodes.push_back(new_node_id);
    nodes[id].value = -1; // we will calculate value of this node later
    indx = traverse_tree(tree, nodes, new_node_id, indx);
  }
  // read metadata entries for the current node which is tree[indx]
  std::size_t i = indx;
  for (std::size_t m = 0; m < mde_q; ++m) {
    nodes[id].metadata_entries.push_back(tree[i]);
    nodes[id].value = -1;
    ++i;
  }
  return i; // i points to begining of next node
}
/* calc_root_value: calculates and returns value of the root of tree which
 * is presented as nodes value: ID -> Node_info. First you need to call
 * traverse_tree function to get nodes data structure.
 * id - current node id
 */
std::int64_t calc_root_value(std::unordered_map<int, Node_info> &nodes,
                             int id) {
  if (nodes[id].value != -1) // if node's id is calculated, return it
    return nodes[id].value;

  if (nodes[id].child_nodes.empty()) {
    // if a node has no child nodes,
    // its value is the sum of its metadata entries.
    std::int64_t sum = 0;
    for (int mde : nodes[id].metadata_entries) {
      sum += mde;
    }
    nodes[id].value = sum; // save value of the current node
    return sum;            // and return it
  }

  /* if a node does have child nodes, the metadata entries become indexes
   * which refer to those child nodes. A metadata entry of 1 refers to
   * the first child node, 2 to the second, 3 to the third, and so on.
   * The value of this node is the sum of the values of the child nodes
   * referenced by the metadata entries. If a referenced child node does not
   * exist, that reference is skipped. A child node can be referenced multiple
   * time and counts each time it is referenced. A metadata entry of 0 does not
   * refer to any child node.
   */
  std::int64_t sum = 0;
  for (int index : nodes[id].metadata_entries) {
    --index; // counting from 0, not from 1
    if (index >= 0 && index < (int)nodes[id].child_nodes.size()) {
      sum += calc_root_value(nodes, nodes[id].child_nodes[index]);
    }
  }
  nodes[id].value = sum;
  return sum;
}

int main() {
  std::vector<int> tree;

  int node;
  while (std::cin >> node) {
    tree.push_back(node);
  }

  std::unordered_map<int, Node_info> nodes;
  // generate nodes structure first: convert tree which is array to nodes data
  // structure which is presented as map (Node_ID -> Node_info)
  traverse_tree(tree, nodes, 0, 0);

  // then calculate root value
  std::cout << calc_root_value(nodes, 0) << '\n';
  return 0;
}
