#include <cheats.hpp>
#include <CTRPluginFramework.hpp>
#include <vector>

using namespace CTRPluginFramework;

namespace SMM3DS
{
	u32 score = 0;

	void InitScore(MenuEntry*)
	{
        Keyboard k("Enter Score \nMax:" + std::to_string(maxscore) + "\nMin:" + std::to_string(0), {""});
        
		//read current
		Process::Read32(0x081C9B00, score);
		
        int result = k.Open(score, score);

		if (result >= 0)
		{
			if (score > maxscore)
				score = maxscore;

			Process::Write32(0x081C9B00, score);
		}
	}

	void KeepScore(MenuEntry*)
	{
		Process::Write32(0x081C9B00, score);
	}

	void Editor_ScoreMax(MenuEntry*)
	{
		Process::Write32(0x081C8CC0, maxscore);
	}


	u16 time = 0;

	void InitTime(MenuEntry*)
	{
        Keyboard k("Enter Time \nMax:" + std::to_string(maxtime) + "\nMin:" + std::to_string(0), {""});
        
		//read current
		Process::Read16(0x310366B6, time);

		int result = k.Open(time, time + 1);

		if (result >= 0)
		{
			if (time > maxtime)
				time = maxtime;

			Process::Write16(0x310366B6, time - 1);
		}
	}

	void KeepTime(MenuEntry*)
	{
		Process::Write16(0x310366B6, time - 1);
	}


	u8 coin = 0;

	void InitCoin(MenuEntry*)
	{
		Keyboard k("Enter Coin\nMax:" + std::to_string(maxcoin) + "\nMin:" + std::to_string(0), {""});

		Process::Read8(0x081C9AF8, coin);

		int result = k.Open(coin, coin);
		if (result >= 0)
		{
			if (coin > maxcoin)
				coin = maxcoin;

			Process::Write8(0x081C9AF8, coin);
		}
	}

	void KeepCoin(MenuEntry*)
	{
		Process::Write8(0x081C9AF8, coin);
	}

	void SetAutoScroll(MenuEntry*)
	{
		const std::vector<std::string> speed = {
			"None",
			Color::Green << "Slow",
			Color::Magenta << "Nomal",
			Color::Yellow << "Fast",
		};

		u8 current;
		/*Read MainWorld*/
		Process::Read8(0x304CB9BA, current);

		Keyboard k("Select scroll speed to set ... \nCurrent:" + speed[current], speed);
		if (current >= 0 && current <= speed.size()-1)
			k.ChangeSelectedEntry(current);
		
		int result = k.Open();

		if (result >= 0)
		{
			Process::Write8(0x304CB9BA, result); //MainWorld
			Process::Write8(0x304EABFE, result); //SubWorld
		}
	}

	void EnableScrollUp(MenuEntry*)
	{
		Process::Write8(0x304CB9BB, 0); //Mainworld
		Process::Write8(0x304EABFF, 0); //SubWorld
	}

	void SetSceneSkin(MenuEntry*)
	{
		u8 current;
		u8 result;
		Process::Read8(0x305A1000, current);

		if (_SetSceneSkin(result, current))
		{
			Process::Write8(0x305A1000, result); //Current
			Process::Write8(0x305AC504, result); //MainWorld
			Process::Write8(0x305AC508, result); //SubWorld
		}
		
	}

	u8 footsteps;

	void SetFootSteps(MenuEntry* entry)
	{
		u8 current;
		u8 result;
		if (entry->IsActivated())
			current = footsteps;
		else
			Process::Read8(0x007ACF3C, current);

		if (_SetSceneSkin(result, current))
		{
			footsteps = result;
		}
	}

	void KeepFootSteps(MenuEntry*)
	{
		if (footsteps >= 0 && footsteps <= 5)
		{
			Process::Write8(0x007ACF3C, footsteps);
		}
	}


	void Invincible(MenuEntry*)
	{
		/**
		 * This value is Mario's invincible time
		 * should be 3 or more because the process will delay when closing menu
		 */
		Process::Write8(0x317B9F00, 0xC);
	}


	void StarPower(MenuEntry*)
	{
		Process::Write16(0x317B9F28, 0xFF);
	}


	s8 lives = 0;

	void InitLives(MenuEntry*)
	{
		u8 current = 0;
		Process::Read8(0x081C9B04, current);
		if (current <= 128)
			current++;

		char msg[64] = {};
		sprintf(msg, "Enter lives \nMax:%d \nMin:%d \nCurrent:%d", 128, INT8_MIN, (s8)current);
		
		Keyboard k(msg);
		k.IsHexadecimal(false);

		if (k.Open(current, current) == 0)
		{
			if (current <= 128)
				current--;
			
			lives = (s8)current;
			Process::Write8(0x081C9B04, (u8)lives);
		}
	}

	void KeepLives(MenuEntry*)
	{
		Process::Write8(0x081C9B04, (u8)lives);
	}

	void DisableHelper(MenuEntry*)
	{
		Process::Write8(0x305A1268, 0);
	}


	void Faster(MenuEntry*)
	{
		/**
		 * Default maximum is 3
		 */
		u32 kdown = Controller::GetKeysDown(true);
		if (kdown & Key::Left)
			Process::WriteFloat(0x317B88DC, -6);
		if (kdown & Key::Right)
			Process::WriteFloat(0x317B88DC, 6);
	}


	void AutoJump(MenuEntry*)
	{
		Process::Write32(0x317B9DEC, 0x317D7820);
	}

	bool _SetSceneSkin(u8 &result, const u8 &current)
	{
		const std::vector<std::string> SceneSkins = {
			Color::Green << "Ground",
			Color::Gray << "UnderGround",
			Color::Red << "Castle",
			Color::Cyan << "AirShip",
			Color::Blue << "UnderWater",
			Color::White << "Mansion"
		};

		Keyboard k("Select Scene Skin to set... \nCurrent:" + SceneSkins[current], SceneSkins);
		if (current >= 0 && current <= SceneSkins.size()-1)
			k.ChangeSelectedEntry(current);
		
		result = k.Open();
		if ((s8)result < 0)
			return false;
		
		return true;
	}
	
}
