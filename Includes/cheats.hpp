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

		//visible max coin
		const static u8 maxcoin = 99;


		/// @brief Set and keep max score
		/// @param entry 
		static void ScoreMax(CTRPluginFramework::MenuEntry *entry);


		/// @brief Set score on keyboard
		/// @param entry 
		static void InitScore(CTRPluginFramework::MenuEntry *entry);


		static void KeepScore(CTRPluginFramework::MenuEntry *entry);


		/// @brief Set and keep max score on editor mode
		/// @param entry 
		static void Editor_ScoreMax(CTRPluginFramework::MenuEntry *entry);	


		/// @brief Set and keep max time(999)
		/// @param entry 
		static void TimeMax(CTRPluginFramework::MenuEntry *entry);


		/// @brief Set time on keyboard
		/// @param entry 
		static void InitTime(CTRPluginFramework::MenuEntry* entry);


		static void KeepTime(CTRPluginFramework::MenuEntry* entry);

		/// @brief Set and keep max coin
		/// @param entry 
		static void CoinMax(CTRPluginFramework::MenuEntry* entry);

		/// @brief Set Auto Scroll.
		///	This code is valid on both editor mode and play mode.
		/// @param entry 
		static void SetAutoScroll(CTRPluginFramework::MenuEntry* entry);


		/// @brief Mario always jumping while enable this code
		/// @param entry 
		static void AutoJump(CTRPluginFramework::MenuEntry *entry);
	};
}
#endif
