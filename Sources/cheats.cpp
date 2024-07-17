#include <cheats.hpp>
#include <CTRPluginFramework.hpp>
#include <vector>

namespace CTRPluginFramework
{
	u32 score = 0;

	void SMM3DS::ScoreMax(MenuEntry *entry)
	{
		Process::Write32(0x081C9B00, SMM3DS::maxscore);
	}

	void SMM3DS::InitScore(MenuEntry *entry)
	{
		std::vector<std::string> options(1);
        Keyboard k("Enter Score \nMax:" + std::to_string(0xFFFFFFFF) + "\nMin:" + std::to_string(0), options);
        
		//read current
		Process::Read32(0x081C9B00, score);
		
        k.Open(score, score);
		Process::Write32(0x081C9B00, score);
	}

	void SMM3DS::KeepScore(MenuEntry *entry)
	{
		Process::Write32(0x081C9B00, score);
	}

	void SMM3DS::Editor_ScoreMax(MenuEntry *entry)
	{
		Process::Write32(0x081C8CC0, SMM3DS::maxscore);
	}


	u16 time = 0;

	void SMM3DS::TimeMax(MenuEntry *entry)
	{
		Process::Write16(0x310366B6, SMM3DS::maxtime - 1);
	}

	void SMM3DS::InitTime(MenuEntry* entry)
	{
		std::vector<std::string> options(1);
        Keyboard k("Enter Time \nMax:" + std::to_string(0xFFFF) + "\nMin:" + std::to_string(0), options);
        
		//read current
		Process::Read16(0x310366B6, time);

		k.Open(time, time + 1);
		Process::Write16(0x310366B6, time - 1);
	}

	void SMM3DS::KeepTime(MenuEntry* entry)
	{
		Process::Write16(0x310366B6, time - 1);
	}


	u8 coin = 0;

	void SMM3DS::CoinMax(MenuEntry* entry)
	{
		Process::Write8(0x081C9AF8, SMM3DS::maxcoin);
	}

	void SMM3DS::SetAutoScroll(MenuEntry* entry)
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

		int result = k.Open();

		if (result != -1 && result != -2)
		{
			Process::Write8(0x304CB9BA, result); //MainWorld
			Process::Write8(0x304EABFE, result); //SubWorld
		}
	}

	void SMM3DS::AutoJump(MenuEntry *entry)
	{
		Process::Write32(0x317B9DEC, 0x317D7820);
	}

	
}
