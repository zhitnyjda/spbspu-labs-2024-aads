#include <iostream>
#include <string>
#include "tree.hpp"

int main() {
    using namespace zheleznyakov;
    using subtree_t = zheleznyakov::Tree<std::string, int>;

    subtree_t tree1;
    tree1["key5"] = 5;
    tree1["key2"] = 2;
    tree1["key4"] = 4;
    tree1["key7"] = 7;
    tree1["key6"] = 6;
    tree1["key1"] = 1;
    tree1["key3"] = 3;

    subtree_t tree2;
    tree2["key8"] = 8;
    tree2["key9"] = 9;
    tree2["key10"] = 10;
    tree2["key11"] = 11;
    tree2["key12"] = 12;
    tree2["key13"] = 13;
    tree2["key14"] = 14;

    zheleznyakov::Tree<std::string, subtree_t*> uptree;

    tree1.swap(tree2);

    uptree["mega1"] = &tree1;
    uptree["mega2"] = &tree2;

    uptree.erase("mega2");

    std::cout << tree2["key1"] << '\n';

    for (auto it = uptree.begin(); it != uptree.end(); ++it)
    {
      std::cout << "Key: " << it->first << "\nValues:\n";
      auto subtree = it->second;
      for (auto subit = subtree->begin(); subit != subtree->end(); ++subit)
      {
        std::cout << subit->first << ' ';
      }
      std::cout << '\n';
    }

    return 0;
}
