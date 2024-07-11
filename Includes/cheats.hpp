#ifndef CHEATS_HPP
#define CHEATS_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
	class SMM3DS
	{
	public:
		//Title ID(Japan)
		const static u64 idjp = 0x00040000001A0300;

		//visible max score
		const static u32 maxscore = 999999990;

		//visible max time
		const static u16 maxtime = 999;

		//Set and keep max score
		static void ScoreMax(CTRPluginFramework::MenuEntry *entry);

		//Set score on keyboard
		static void InitScore(CTRPluginFramework::MenuEntry *entry);

		static void KeepScore(CTRPluginFramework::MenuEntry *entry);

		//Set and keep max score on editor mode
		static void Editor_ScoreMax(CTRPluginFramework::MenuEntry *entry);	

		//Set and keep max time(999)
		static void TimeMax(CTRPluginFramework::MenuEntry *entry);

		//Mario always jumping while enable this code
		static void AutoJump(CTRPluginFramework::MenuEntry *entry);
	};
}
#endif
