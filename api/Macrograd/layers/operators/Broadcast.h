#ifndef BROADCAST_H
#define BROADCAST_H
#include "Operator.h"
#include "Node.h"


namespace Broadcast
{
    class Add
    {
        public:
            static std::shared_ptr<Node> calculate(std::shared_ptr<Node> operandA, std::shared_ptr<Node> operandB);

        private:
            static std::function<void(void)> getBackward(std::shared_ptr<Node> operandA, std::shared_ptr<Node> operandB, std::shared_ptr<Node> out);
    };
}

#endif
