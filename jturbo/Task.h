#pragma once

#include <memory>

namespace jturbo {

class Task
{
public:
	Task() {}
	virtual ~Task() {}
	virtual void Run() = 0;
};

} // namespace jturbo