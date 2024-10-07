#include "Node.h"
#include "Mat.h"
#include <iostream>
#include <memory>
#include <unordered_set>

Node::Node(std::shared_ptr<Mat> paramData, std::unordered_set<std::shared_ptr<Node>> previous)
{
    this->data = paramData;
    this->grad = paramData->mapFunction([=](int i, int j, float value){ return 0; });
    this->previous = previous;
}

Node::Node(std::shared_ptr<Mat> paramData) : Node(paramData, std::unordered_set<std::shared_ptr<Node>>()) 
{

}



std::shared_ptr<Node> operator+(std::shared_ptr<Node> nodeA, std::shared_ptr<Node> nodeB)
{

    Mat resultMat = *(nodeA->data.get()) + *(nodeB->data.get());
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat),
        std::unordered_set<std::shared_ptr<Node>>({
            nodeA,
            nodeB
        }));

    std::weak_ptr<Node> weakA(nodeA);
    std::weak_ptr<Node> weakB(nodeB);
    std::weak_ptr<Node> weakOut(out);
    
    out->backward = [weakA, weakB, weakOut]()
    {
        std::shared_ptr<Node> nA = weakA.lock();
        if(!nA)
            throw std::runtime_error("Can't get lock to pointer of A in addition operator!");

        std::shared_ptr<Node> nB = weakB.lock();
        if(!nB)
            throw std::runtime_error("Can't get lock to pointer of B in addition operator!");

        std::shared_ptr<Node> nOut = weakOut.lock();
        if(!nOut)
            throw std::runtime_error("Can't get lock to pointer of Out in addition operator!");

        *(nB->grad.get()) += *(nOut->grad.get());
        *(nA->grad.get()) += *(nOut->grad.get());
    };
    return out;
}

std::shared_ptr<Node> operator-(std::shared_ptr<Node> nodeA, std::shared_ptr<Node> nodeB)
{
    Mat resultMat = *(nodeA->data.get()) - *(nodeB->data.get());
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat), 
        std::unordered_set<std::shared_ptr<Node>>({
            nodeA,
            nodeB
        }));

    std::weak_ptr<Node> weakA(nodeA);
    std::weak_ptr<Node> weakB(nodeB);
    std::weak_ptr<Node> weakOut(out);
    
    out->backward = [weakA, weakB, weakOut]()
    {
        std::shared_ptr<Node> nA = weakA.lock();
        if(!nA)
            throw std::runtime_error("Can't get lock to pointer of A in subtraction operator!");

        std::shared_ptr<Node> nB = weakB.lock();
        if(!nB)
            throw std::runtime_error("Can't get lock to pointer of B in subtraction operator!");

        std::shared_ptr<Node> nOut = weakOut.lock();
        if(!nOut)
            throw std::runtime_error("Can't get lock to pointer of Out in subtraction operator!");

        std::shared_ptr<Mat> aGrad = std::make_shared<Mat>(*(nOut->grad.get()));
        std::shared_ptr<Mat> bGrad = nOut->grad->mapFunction([=](int i, int j, float value) {
            return -1 * value;
        });

        nB->grad = bGrad;
        nA->grad = aGrad;
    };
    return out;
}

std::shared_ptr<Node> operator*(std::shared_ptr<Node> nodeA, std::shared_ptr<Node> nodeB)
{
    Mat resultMat = *(nodeA->data.get()) * (*(nodeB->data.get()));
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat),
        std::unordered_set<std::shared_ptr<Node>>({
            nodeA,
            nodeB
        }));

    std::weak_ptr<Node> weakA(nodeA);
    std::weak_ptr<Node> weakB(nodeB);
    std::weak_ptr<Node> weakOut(out);
    
    out->backward = [weakA, weakB, weakOut]()
    {
        std::shared_ptr<Node> nA = weakA.lock();
        if(!nA)
            throw std::runtime_error("Can't get lock to pointer of A in multiplication operator!");

        std::shared_ptr<Node> nB = weakB.lock();
        if(!nB)
            throw std::runtime_error("Can't get lock to pointer of B in multiplication operator!");

        std::shared_ptr<Node> nOut = weakOut.lock();
        if(!nOut)
            throw std::runtime_error("Can't get lock to pointer of Out in multiplication operator!");

        *(nA->grad.get()) += (*(nOut->grad) * (nB->data->T()));
        *(nB->grad.get()) += (nA->data->T() * *(nOut->grad));
    };
    return out;
}

std::shared_ptr<Node> operator/(std::shared_ptr<Node> node, float value)
{
    std::shared_ptr<Mat> resultMat = node->data / value;

    std::shared_ptr<Node> out = std::make_shared<Node>(resultMat, 
        std::unordered_set<std::shared_ptr<Node>>({
            node
        }));

    std::weak_ptr<Node> weakNode(node);
    std::weak_ptr<Node> weakOut(out);

    out->backward = [weakNode, weakOut, value]() {
        std::shared_ptr<Node> node = weakNode.lock();
        if(!node)
            throw std::runtime_error("Can't get lock to pointer of node in division operator!");

        std::shared_ptr<Node> nOut = weakOut.lock();
        if(!nOut)
            throw std::runtime_error("Can't get lock to pointer of Out in division operator!");

        *(node->grad.get()) += *((nOut->grad / value).get());
    };

    return out;
}

std::shared_ptr<Node> sum(std::shared_ptr<Node> nodeA)
{
    float totalSum = 0.0;

    nodeA->data->forEach([&totalSum](int i, int j, float value){ totalSum += value; });

    svf sumValue = {{totalSum}};

    std::shared_ptr<Node> out = std::make_shared<Node>(
        std::make_shared<Mat>(sumValue), 
        std::unordered_set<std::shared_ptr<Node>>({nodeA})
    );

    std::weak_ptr<Node> weakA(nodeA);
    std::weak_ptr<Node> weakOut(out);

    out->backward = [weakA, weakOut]()
    {
        std::shared_ptr<Node> nA = weakA.lock();
        if(!nA)
            throw std::runtime_error("Can't get lock to pointer of A in sum operator!");

        std::shared_ptr<Node> nOut = weakOut.lock();
        if(!nOut)
            throw std::runtime_error("Can't get lock to pointer of out in sum operator!");

        float gradientToPropagate = nOut->grad->at(0, 0);
        *(nA->grad.get()) += gradientToPropagate;
    };
    return out;
}