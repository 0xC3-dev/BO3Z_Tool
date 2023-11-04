#pragma once

namespace Notify
{
	// Display a popup messagebox.
	void Popup(const char* text, const char* textTitle, UINT uType)
	{
		MessageBoxA(NULL, (LPCSTR)text, (LPCSTR)textTitle, uType);
	}
}