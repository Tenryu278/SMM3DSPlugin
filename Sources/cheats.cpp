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
        Keyboard* k = new Keyboard(
                "Enter Score \nMax:" + std::to_string(0xFFFFFFFF) + "\nMin:" + std::to_string(0), options);
        
		//read current
		Process::Read32(0x081C9B00, score);
        k->Open(score, score);
		Process::Write32(0x081C9B00, score);
		delete k;
	}

	void SMM3DS::KeepScore(MenuEntry *entry)
	{
		Process::Write32(0x081C9B00, score);
	}

	void SMM3DS::Editor_ScoreMax(MenuEntry *entry)
	{
		Process::Write32(0x081C8CC0, SMM3DS::maxscore);
	}

	void SMM3DS::TimeMax(MenuEntry *entry)
	{
		Process::Write16(0x310366B6, SMM3DS::maxtime - 1);
	}

	void SMM3DS::AutoJump(MenuEntry *entry)
	{
		Process::Write32(0x317B9DEC, 0x317D7820);
	}


}
