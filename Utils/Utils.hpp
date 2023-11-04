#pragma once
#include "../Global_Vars/Vars.hpp"
#define isValidPtr(p) ((uintptr_t)(p) <= 0x7FFFFFFFFFFF && (uintptr_t)(p) >= 0x1000) 
#define notValidPtr(p)	(!isValidPtr(p))

namespace Utils
{
	bool ValidPointer(uintptr_t address);
	DWORD GetProcId(const char* procName);
	uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName);
	uintptr_t PointerChain(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	void Patch(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Nop(BYTE* dst, unsigned int size, HANDLE hProcess);
	void Write(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Read(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
}