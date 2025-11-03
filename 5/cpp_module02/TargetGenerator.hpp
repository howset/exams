#pragma once

#include <iostream>
#include <map>
class ATarget;

class TargetGenerator
{
	private:
		std::map<std::string, ATarget *> tgtTypes;
	public:
		TargetGenerator();
		~TargetGenerator();

		void learnTargetType(ATarget *);
		void forgetTargetType(const std::string &);
		ATarget *createTarget(const std::string &);
};
