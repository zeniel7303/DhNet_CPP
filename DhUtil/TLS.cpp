#include "pch.h"
#include "TLS.h"

thread_local unsigned __int32 LThreadId = 0;

thread_local std::stack<int32> LLockStack;