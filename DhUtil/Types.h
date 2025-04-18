#pragma once

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#define size16(val)	static_cast<__int16>(sizeof(val)):
#define size32(val)	static_cast<__int32>(sizeof(val)):
#define len16(arr)	static_cast<__int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)	static_cast<__int32>(sizeof(arr)/sizeof(arr[0]))

#define USING_SHARED_PTR(name)	using name##Ref = std::shared_ptr<class name>;
USING_SHARED_PTR(Job);
USING_SHARED_PTR(JobQueue);