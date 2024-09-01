/**
 * @file SMM3DSPlugin Cheats header file
 * 
 * This software is licensed under MIT
 * This has no warranty or liability
 * https://github.com/Tenryu278/SMM3DSPlugin/blob/master/LICENSE
 * 
 * Github repository:
 * https://github.com/Tenryu278/SMM3DSPlugin
 * 
 * Full credits is here:
 * https://github.com/Tenryu278/SMM3DSPlugin?tab=readme-ov-file#credits
 * 
 * Copyright (c) 2024 Tenryu278
 */


#ifndef CHEATS_HPP
#define CHEATS_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace SMM3DS
{
	enum PowerUp
	{
		Small,
		Super,
		Fire,
		Weird,
		Propellor,
		Cape,
		Raccoon,
		Chara,
		Big
	};

	enum GameSkin
	{
		SMB1,
		SMB3,
		SMW,
		NSMBU
	};

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
	void InitScore(CTRPluginFramework::MenuEntry*);

	void KeepScore(CTRPluginFramework::MenuEntry*);


	/// @brief Set and keep max score on editor mode
	/// @param 
	void Editor_ScoreMax(CTRPluginFramework::MenuEntry*);


	/// @brief Set time on keyboard
	/// @param 
	void InitTime(CTRPluginFramework::MenuEntry*);

	void KeepTime(CTRPluginFramework::MenuEntry*);


	/// @brief Set Coin on keyboard
	/// @param 
	void InitCoin(CTRPluginFramework::MenuEntry*);

	void KeepCoin(CTRPluginFramework::MenuEntry*);


	/// @brief Set Auto Scroll.
	///	This code is valid on both editor mode and play mode.
	/// @param 
	void SetAutoScroll(CTRPluginFramework::MenuEntry*);


	/// @brief Enable Scrolling Up
	/// @param 
	void EnableScrollUp(CTRPluginFramework::MenuEntry*);


	/// @brief Set Scene Skin
	/// @param  
	void SetSceneSkin(CTRPluginFramework::MenuEntry*);


	/// @brief Set FootSteps
	/// @param  
	void SetFootSteps(CTRPluginFramework::MenuEntry*);

	/// @brief Keep FootSteps
	/// @param  
	void KeepFootSteps(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Invincible(CTRPluginFramework::MenuEntry*);


	/// @brief Always Star Power
	/// @note This doesn't working for graphics
	/// @param  
	void StarPower(CTRPluginFramework::MenuEntry*);


	/// @brief Set Mario's lives on Keyboard. Use Super mario challenge
	/// @param  
	void InitLives(CTRPluginFramework::MenuEntry*);

	/// @brief Keep Mario's lives
	/// @param  
	void KeepLives(CTRPluginFramework::MenuEntry*);


	/// @brief Disable helper mode on Super Mario Challenge (Mistakes count will always be 0)
	/// @param  
	void DisableHelper(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Faster(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void SetDamageToBecome(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void KeepDamageToBecome(CTRPluginFramework::MenuEntry*);


	/**
	 * @brief 
	 * DL+R: Small Mario
	 * 
	 * DR+R: Super Mario
	 * 
	 * DU+R: Fire Mario
	 * 
	 * DD+R: Weird/Raccoon/Cape/Propellor Mario
	 *
	 * 
	 * --SMB3 only--
	 * 
	 * DD+L: Big Mario
	 * 
	 * DU+L: Chara Mario
	 * @param
	 * @note This is incomplete so it may doesn't working well
	 */
	void ItemCheatAuto(CTRPluginFramework::MenuEntry*);


	/// @brief Mario always jumping while enable this code
	/// @param  
	void AutoJump(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void ForceCrouch(CTRPluginFramework::MenuEntry*);


	/// @brief Select Scene Skin on keyboard
	/// @param result Reurns selected. 
	///	If not selected, returns -1 (cancel) or -2 (cancel bacause sleeping).
	/// @param current Current Scene Skin. Defalt is Ground.
	/// @return True is success, False is none
	bool _SetSceneSkin(u8 &result, const u8 &current = 0);
}
#endif
