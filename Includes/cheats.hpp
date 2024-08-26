#ifndef CHEATS_HPP
#define CHEATS_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
	enum class DialogResult
	{
		Cancel = -1,
		SleepCancel = -2
	};

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


		/// @brief Set score on keyboard
		/// @param 
		static void InitScore(CTRPluginFramework::MenuEntry*);

		static void KeepScore(CTRPluginFramework::MenuEntry*);


		/// @brief Set and keep max score on editor mode
		/// @param 
		static void Editor_ScoreMax(CTRPluginFramework::MenuEntry*);


		/// @brief Set time on keyboard
		/// @param 
		static void InitTime(CTRPluginFramework::MenuEntry*);

		static void KeepTime(CTRPluginFramework::MenuEntry*);


		/// @brief Set Coin on keyboard
		/// @param 
		static void InitCoin(CTRPluginFramework::MenuEntry*);

		static void KeepCoin(CTRPluginFramework::MenuEntry*);


		/// @brief Set Auto Scroll.
		///	This code is valid on both editor mode and play mode.
		/// @param 
		static void SetAutoScroll(CTRPluginFramework::MenuEntry*);


		/// @brief Enable Scrolling Up
		/// @param 
		static void EnableScrollUp(CTRPluginFramework::MenuEntry*);


		/// @brief Set Scene Skin
		/// @param  
		static void SetSceneSkin(CTRPluginFramework::MenuEntry*);


		/// @brief Set FootSteps
		/// @param  
		static void SetFootSteps(CTRPluginFramework::MenuEntry*);

		/// @brief Keep FootSteps
		/// @param  
		static void KeepFootSteps(CTRPluginFramework::MenuEntry*);


		/// @brief Set Mario's lives on Keyboard. Use Super mario challenge
		/// @param  
		static void InitLives(CTRPluginFramework::MenuEntry*);


		/// @brief Disable helper mode on Super Mario Challenge (Mistakes count will always be 0)
		/// @param  
		static void DisableHelper(CTRPluginFramework::MenuEntry*);


		/// @brief Keep Mario's lives
		/// @param  
		static void KeepLives(CTRPluginFramework::MenuEntry*);


		/// @brief Mario always jumping while enable this code
		/// @param  
		static void AutoJump(CTRPluginFramework::MenuEntry*);

	private:
		/// @brief Select Scene Skin on keyboard
		/// @param result Reurns selected. 
		///	If not selected, returns -1 (cancel) or -2 (cancel bacause sleeping).
		/// @param current Current Scene Skin. Defalt is Ground.
		/// @return True is success, False is none
		static bool _SetSceneSkin(u8 &result, const u8 &current = 0);
	};
}
#endif
