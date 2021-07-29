#pragma once
#include <cstdint>
#include <libloaderapi.h>



class Memory {
public:
	static constexpr auto MAKE_RVA = [](std::uintptr_t address) -> std::uintptr_t
	{
		return reinterpret_cast<std::uintptr_t>(GetModuleHandleA("GameAssembly")) + address;
	};

	template<typename T, typename... TypeArgs>
	static constexpr T FUNCTION_CAST(std::uintptr_t Offset, TypeArgs&... type_args) {
		return reinterpret_cast<T(*)(TypeArgs...)>(Offset)(std::forward<TypeArgs>(type_args)...);
	};
};