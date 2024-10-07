#include "LayerUtils.h"
#include "Node.h"
#include <iostream>
#include <memory>


void LayerUtils::buildTopoGraph(std::shared_ptr<Node> root)
{
    if(this->visited.contains(root))
        return;

    // Don't call backward for leaf nodes
    if(root->previous.empty())
        return;

    for(std::shared_ptr<Node> child : root->previous)
    {
        buildTopoGraph(child);
    }
    
    this->visited.insert(root);
    this->orderedNodes.push_back(root);
}

void LayerUtils::backward(std::shared_ptr<Node> root)
{
    this->visited = std::unordered_set<std::shared_ptr<Node>>();
    this->orderedNodes = std::vector<std::shared_ptr<Node>>();
    root->grad->assignValue(1.0);
    this->buildTopoGraph(root);

    std::reverse(this->orderedNodes.begin(), this->orderedNodes.end());
    for(std::shared_ptr<Node> nodePtr : this->orderedNodes) {
        nodePtr->backward();
    }
}
