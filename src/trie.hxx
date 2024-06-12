#ifndef MY_TRIE_H
#define MY_TRIE_H

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>

namespace mystuff {

/**
 * @class RadixTree
 * @brief A compressed trie, basically. Utilizes an unordered map in each node
 * to store children.
 *
 */
class RadixTree {
public:
  RadixTree() : root(nullptr) {}
  /**
   * @brief Whether the current radix tree contains the word specified
   *
   * @param word
   * @return true if empty word or word is inside, false otherwise
   */
  bool contains(const std::string &word) { return contains_(&root, word); }

  /**
   * @brief Insert the specified word into the radix tree.
   *
   * @param word
   */
  void insert(const std::string &word) { insert_(&root, word); }

  /**
   * @brief Remove the specified word from the radix tree, if it is in the tree.
   *
   * @param word
   */
  void remove(const std::string &word) { remove_(&root, word); }

private:
  class Node {
  public:
    /**
     * @brief Whether this node has no outgoing edge
     *
     */
    bool is_leaf() { return edge_list.empty(); }

    /**
     * @brief Whether the unordered map contains the specified key
     *
     * @param k
     */
    bool contains_key(char k) { return edge_list.contains(k); }

    /**
     * @brief Inserts an edge with the specified word into this node's edge
     * list, if it doesn't already exists. If the string is empty, the key to
     * access the newly inserted edge is 0. Otherwise, it's the first character
     * of the string.
     *
     */
    void insert_edge(const std::string &word) {
      // empty word is an insert at position 0 of the hash map
      if (word.empty())
        edge_list.insert(std::pair<char, std::unique_ptr<Edge>>(
            static_cast<char>(0), std::make_unique<Edge>(this)));
      else
        edge_list.insert(std::pair<char, std::unique_ptr<Edge>>(
            word[0], std::make_unique<Edge>(word, this)));
    }
    struct Edge {
      Edge(const std::string label, Node *parent) {
        this->label = label;
        this->child = std::make_unique<Node>(this);
        this->parent = parent;
      }
      Edge(Node *parent) {
        this->label = "";
        this->child = std::make_unique<Node>(this);
        this->parent = parent;
      }
      std::string label;
      /**
       * @brief An unique pointer to the child node of the node containing this
       * edge
       */
      std::unique_ptr<Node> child;
      /**
       * @brief A non-owning pointer to the parent of the child node
       */
      Node *parent;
      /**
       * @brief Overloads the equivalent operator, so that every time one writes
       * edge1 == edge2, it's comparing each edge's string instead of its entire
       * memory block, which is never equal.
       *
       */
      bool operator==(const Edge &other) { return this->label == other.label; }
    };

    /**
     * @brief If a word exists, this contains a no-label edge with key 0. The
     * other words are stored in a pair of form [first character of word, the
     * edge whose label is the word].
     */
    std::unordered_map<char, std::unique_ptr<Edge>> edge_list;

    /**
     * @brief A non-owning pointer to the edge whose child is this node
     */
    Edge *incoming_edge;
    explicit Node(Node::Edge *incoming_edge) : incoming_edge(incoming_edge) {}
    ~Node() {}
  };
  Node root;

  /**
   * @brief Recursive call of the public method RadixTree::contains()
   *
   * @param curr_node The current node of the iteration. Will start with the
   * root node.
   * @param suffix The remaining part of the word passed in in the public
   * RadixTree::contains() method.
   */
  bool contains_(Node *curr_node, const std::string &suffix) {
    if (suffix.empty()) {
      // root node can have 0 strings, but all other nodes must be either
      // end-of-string (leaf) or has an edge with empty string
      if (curr_node == &root)
        return curr_node->contains_key(static_cast<char>(0));
      return curr_node->is_leaf() ||
             curr_node->contains_key(static_cast<char>(0));
    }
    // we don't have that word here.
    if (!curr_node->contains_key(suffix[0]))
      return false;

    Node::Edge *curr_edge = curr_node->edge_list[suffix[0]].get();
    std::string curr_label = curr_edge->label;
    std::size_t pos = 1;
    // compare the 2 strings.
    for (; pos < std::min(suffix.length(), curr_label.length()); pos++) {
      // differing string, hence the word isn't in here.
      if (suffix[pos] != curr_label[pos])
        return false;
    }
    // pos < suffix.length(). In which case, keep recursing.
    return contains_(curr_edge->child.get(), suffix.substr(pos));
  }

  /**
   * @brief Recursive call of the public method RadixTree::insert()
   *
   * @param curr_node The current node of the iteration. Will start with the
   * root node.
   * @param suffix The remaining part of the word passed in in the public
   * RadixTree::insert() method.
   */
  void insert_(Node *curr_node, const std::string &suffix) {
    // technically this never happens, but I'm scared still :(
    if (curr_node == nullptr)
      return;
    // we're there
    if (suffix.empty()) {
      // a leaf node already signals it's the end of word. But a leaf-node root
      // just means there's no word.
      if (curr_node->is_leaf() && curr_node != &root)
        return;
      curr_node->insert_edge("");
      return;
    }

    // insert key without splitting edge
    if (!curr_node->contains_key(suffix[0])) {
      curr_node->insert_edge(suffix);
      return;
    }

    // check if the entirety of the label matches the prefix of suffix.
    Node::Edge *curr_edge = curr_node->edge_list[suffix[0]].get();
    std::string edge_label = curr_edge->label;
    std::size_t pos = 1;

    for (; pos < std::min(edge_label.length(), suffix.length()); pos++) {
      // the label doesn't match
      if (suffix[pos] != edge_label[pos])
        break;
    }
    // We don't need to insert into a leaf due to a leaf already representing
    // that string.
    if (pos == suffix.length() && !curr_edge->child->is_leaf()) {
      curr_edge->child->insert_edge("");
      return;
    }

    // pos < suffix.length()
    // meaning we have to split an edge
    else if (curr_edge->child->is_leaf()) {
      std::string common_prefix = suffix.substr(0, pos);
      std::string new_suffix = suffix.substr(pos);
      std::string old_suffix = edge_label.substr(pos);

      curr_edge->label = common_prefix;
      curr_edge->child->insert_edge(old_suffix);
      curr_edge->child->insert_edge(new_suffix);

      return;
    }

    // !curr_edge->child->is_leaf(), meaning we can traverse further down.
    insert_(curr_edge->child.get(), suffix.substr(pos));
  }

  /**
   * @brief Helper method to merge 2 edges coming in and out of a node after
   * removing its child, if there's only 1 outgoing edge.
   *
   * @param parent
   */
  void merge_parent_and_child_(Node *parent) {
    if (parent == nullptr)
      return;
    // only merge if exactly 1 child and parent isn't root
    if (parent->edge_list.size() != 1 || parent != &root)
      return;
    // the only child of parent
    Node::Edge *child_edge = parent->edge_list.begin()->second.get();
    std::string child_edge_label = child_edge->label;
    Node::Edge *parent_edge = parent->incoming_edge;

    parent_edge->label += child_edge_label;
    parent->edge_list.erase(child_edge_label[0]);
  }

  /**
   * @brief Recursive call for the method RadixTree::remove().
   *
   * @param curr_node The current node of the iteration. Will start with the
   * root node.
   * @param suffix The remaining part of the word passed in in the public
   * RadixTree::remove() method.
   */
  void remove_(Node *curr_node, const std::string &suffix) {
    // never happen, but I'm scared still
    if (curr_node == nullptr)
      return;
    // maybe we got to the word we need to remove
    if (curr_node->is_leaf()) {
      // not the word
      if (!suffix.empty())
        return;
      // root node. Simply remove that word, no need to merge with any parent
      // node, since there's none.
      if (curr_node == &root) {
        curr_node->edge_list.erase(static_cast<char>(0));
        return;
      }
      // non-root.
      // Always has a parent
      Node *parent = curr_node->incoming_edge->parent;
      std::string incoming_label = curr_node->incoming_edge->label;
      // remove curr_node and incoming edge
      if (incoming_label.empty())
        parent->edge_list.erase(static_cast<char>(0));
      else
        parent->edge_list.erase(incoming_label[0]);

      // maybe its parent now only has 1 child.
      merge_parent_and_child_(parent);
      return;
    }

    // we're not there yet
    // there isn't the word
    if (!curr_node->contains_key(suffix[0]))
      return;

    // compare string
    std::string child_edge_label = curr_node->edge_list[suffix[0]]->label;
    std::size_t pos = 0;
    for (; pos < std::min(child_edge_label.length(), suffix.length()); pos++) {
      // not the word we're looking for
      if (child_edge_label[pos] != suffix[pos])
        return;
    }

    // if we reach here, the word may be there, but we don't know unless we go
    // further down. recursive call
    remove_(curr_node->edge_list[suffix[0]]->child.get(), suffix.substr(pos));
  }
};

} // namespace mystuff

#endif // !MY_TRIE_H
