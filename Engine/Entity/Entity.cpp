#include "Entity.hpp"

namespace SDK
{
	extern __inline int IsInGame()
	{
		Utils::Read((BYTE*)Offsets::inGameAddr, (BYTE*)&GameValues::iInGameValue, sizeof(GameValues::iInGameValue), Game::hProc);
		return GameValues::iInGameValue;
	}

	extern __inline bool WorldToScreen(vec3_t originPos, vec2_t& screenOut, int windowWidth, int windowHeight)
	{
		float Matrix[16] = 
		{ 0.f, 0.f , 0.f , 0.f, 
			0.f, 0.f, 0.f, 0.f, 
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f };

		DWORD viewMatrix = 0x36752A0;

		Utils::Read((BYTE*)Game::moduleBase + viewMatrix, (BYTE*)&Matrix, sizeof(Matrix), Game::hProc);

		vec4_t clipCoords;
		clipCoords.x = originPos.x * Matrix[0] + originPos.y * Matrix[1] + originPos.z * Matrix[2] + Matrix[3];
		clipCoords.y = originPos.x * Matrix[4] + originPos.y * Matrix[5] + originPos.z * Matrix[6] + Matrix[7];
		clipCoords.z = originPos.x * Matrix[8] + originPos.y * Matrix[9] + originPos.z * Matrix[10] + Matrix[11];
		clipCoords.w = originPos.x * Matrix[12] + originPos.y * Matrix[13] + originPos.z * Matrix[14] + Matrix[15];

		if (clipCoords.w < 0.1f)
			return false;

		vec3_t NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		screenOut.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		screenOut.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
		return true;
	}

	extern __inline float UnitsToMeter(float units)
	{
		return units * 0.0254;
	}
}