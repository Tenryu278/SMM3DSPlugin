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

	enum TitleID : u64
	{
		/**
		 * SMM3DS::TitleID from https://3dsdb.com/
		 */
		JPN = 0x00040000001A0300,
		USA = 0x00040000001A0400,
		EUR = 0x00040000001A0500
	};

	/// @brief Check current game is SMM3DS
	/// @param tid Title ID 
	/// @return 
	inline bool IsSMM3DS(u64 tid)
	{
		return (tid==TitleID::JPN||tid==TitleID::USA||tid==TitleID::EUR);
	}

	/// @brief Read the current game skin. This is incomplete
	/// @param result Reference to GameSkin object
	/// @return True if success, false otherwise
	inline bool GetGameSkin(GameSkin &result)
	{
		u8 tmp;
		if (!CTRPluginFramework::Process::Read8(0x305A0FFC, tmp))
			return false;
		if (result>=0 && result <= GameSkin::NSMBU)
			result = (GameSkin)tmp;
		else
			return false;
		return true;
	}


	//visible max score
	constexpr u32 maxscore = 999999990;

	//visible max time
	constexpr u16 maxtime = 999;

	//visible max coin
	constexpr u8 maxcoin = 99;


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


	/// @brief 
	/// @param  
	void MidAirCrouch(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_Crouch(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_CrouchS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_JMovement(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_JMovementS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_WallKick(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_WallKickS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_HipAttack(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_HipAttackS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_SwimStyle(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_SwimStyleS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_StarJump(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_StarJumpS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_Carry(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_CarryS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_ThrowUp(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_ThrowUpS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_LookUp(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_LookUpS(CTRPluginFramework::MenuEntry*);


	/// @brief 
	/// @param  
	void Toggle_SpinJump(CTRPluginFramework::MenuEntry*);

	/// @brief 
	/// @param  
	void Keep_SpinJumpS(CTRPluginFramework::MenuEntry*);
	

	/// @brief Select Scene Skin on keyboard
	/// @param result Reurns selected. 
	///	If not selected, returns -1 (cancel) or -2 (cancel bacause sleeping).
	/// @param current Current Scene Skin. Defalt is Ground.
	/// @return True is success, False is none
	bool _SetSceneSkin(u8 &result, u8 current = 0);
}
#endif
