#include <iostream>
#include <string>
#include "tree.hpp"

int main() {
    using namespace zheleznyakov;
    using subtree_t = zheleznyakov::Tree<std::string, int>;

    subtree_t tree1;
    tree1.push("key5", 5);
    tree1.push("key2", 2);
    tree1.push("key4", 4);
    tree1.push("key7", 7);
    tree1.push("key6", 6);
    tree1.push("key1", 1);
    tree1.push("key3", 3);

    subtree_t tree2;
    tree2.push("key8", 8);
    tree2.push("key9", 9);
    tree2.push("key10", 10);
    tree2.push("key11", 11);
    tree2.push("key12", 12);
    tree2.push("key13", 13);
    tree2.push("key14", 14);

    zheleznyakov::Tree<std::string, subtree_t*> uptree;

    uptree.push("mega1", &tree1);
    uptree.push("mega2", &tree2);

    for (auto it = uptree.begin(); it != uptree.end(); ++it) {
      std::cout << "Key: " << it->first << "\nValues:\n";
      auto subtree = it->second;
      for (auto subit = subtree->begin(); subit != subtree->end(); ++subit) {
        std::cout << subit->first << ' ';
      }
      std::cout << '\n';
    }

    return 0;
}
