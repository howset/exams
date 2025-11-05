#include "TargetGenerator.hpp"
#include "ATarget.hpp"

TargetGenerator::TargetGenerator()
{}

TargetGenerator::~TargetGenerator()
{
    tgtTypes.clear();
}

void TargetGenerator::learnTargetType(ATarget *target)
{
    if (target != nullptr)
    {
        std::map<std::string, ATarget *>::iterator it = tgtTypes.find(target->getType());

        if (it == tgtTypes.end())
            tgtTypes[target->getType()] = target;
    }
}

void TargetGenerator::forgetTargetType(const std::string &target)
{
    std::map<std::string, ATarget *>::iterator it = tgtTypes.find(target);

    if (it != tgtTypes.end())
        tgtTypes.erase(target);
}

ATarget *TargetGenerator::createTarget(const std::string &target)
{
    std::map<std::string, ATarget *>::iterator it = tgtTypes.find(target);

    if (it != tgtTypes.end())
        return (it->second->clone());
    return nullptr;
}
