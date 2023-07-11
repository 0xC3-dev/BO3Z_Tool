#pragma once
#include "Entity/Entity_t.h"

namespace Engine
{
	void IsInGame();
	void Player1Features();
	void Player2Features();
	void Player3Features();
	void Player4Features();
	void ExtraGoodieFeatures();
	void DisableAllFeatures();

	namespace ESP
	{
		void FeatureLoop();
	}

	namespace Aimbot
	{
		void DoAimbot();
	}
}