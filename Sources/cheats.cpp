#include <cheats.hpp>
#include <CTRPluginFramework.hpp>
#include <vector>

namespace CTRPluginFramework
{
	u32 score = 0;

	void SMM3DS::InitScore(MenuEntry *entry)
	{
        Keyboard k("Enter Score \nMax:" + std::to_string(SMM3DS::maxscore) + "\nMin:" + std::to_string(0), {""});
        
		//read current
		Process::Read32(0x081C9B00, score);
		
        int result = k.Open(score, score);

		if (result != (int)DialogResult::Cancel && result != (int)DialogResult::SleepCancel)
		{
			if (score > SMM3DS::maxscore)
				score = SMM3DS::maxscore;

			Process::Write32(0x081C9B00, score);
		}
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

	void SMM3DS::InitTime(MenuEntry* entry)
	{
        Keyboard k("Enter Time \nMax:" + std::to_string(SMM3DS::maxtime) + "\nMin:" + std::to_string(0), {""});
        
		//read current
		Process::Read16(0x310366B6, time);

		int result = k.Open(time, time + 1);

		if (result != (int)DialogResult::Cancel && result != (int)DialogResult::SleepCancel)
		{
			if (time > SMM3DS::maxtime)
				time = SMM3DS::maxtime;

			Process::Write16(0x310366B6, time - 1);
		}
	}

	void SMM3DS::KeepTime(MenuEntry* entry)
	{
		Process::Write16(0x310366B6, time - 1);
	}


	u8 coin = 0;

	void SMM3DS::InitCoin(MenuEntry* entry)
	{
		Keyboard k("Enter Coin\nMax:" + std::to_string(SMM3DS::maxcoin) + "\nMin:" + std::to_string(0), {""});

		Process::Read8(0x081C9AF8, coin);

		int result = k.Open(coin, coin);
		if (result != (int)DialogResult::Cancel && result != (int)DialogResult::SleepCancel)
		{
			if (coin > SMM3DS::maxcoin)
				coin = SMM3DS::maxcoin;

			Process::Write8(0x081C9AF8, coin);
		}
	}

	void SMM3DS::KeepCoin(MenuEntry *entry)
	{
		Process::Write8(0x081C9AF8, coin);
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

		if (result != (int)DialogResult::Cancel && result != (int)DialogResult::SleepCancel)
		{
			Process::Write8(0x304CB9BA, result); //MainWorld
			Process::Write8(0x304EABFE, result); //SubWorld
		}
	}

	void SMM3DS::EnableScrollUp(MenuEntry* entry)
	{
		Process::Write8(0x304CB9BB, 0); //Mainworld
		Process::Write8(0x304EABFF, 0); //SubWorld
	}

	void SMM3DS::AutoJump(MenuEntry *entry)
	{
		Process::Write32(0x317B9DEC, 0x317D7820);
	}

	
}
