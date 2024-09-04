/**
 * @file SMM3DSPlugin Cheats source file
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

#include <cheats.hpp>
#include <CTRPluginFramework.hpp>
#include <vector>

using namespace CTRPluginFramework;

namespace SMM3DS
{
	u32 score = 0;

	void InitScore(MenuEntry* entry)
	{
        Keyboard k("Enter Score \nMax:" + std::to_string(maxscore) + "\nMin:" + std::to_string(0));
		k.IsHexadecimal(false);
        
		//read current
		Process::Read32(0x081C9B00, score);
		
        int result = k.Open(score, score);

		if (result >= 0)
		{
			if (score > maxscore)
				score = maxscore;

			Process::Write32(0x081C9B00, score);
			entry->SetGameFunc(KeepScore);
		}
		else
		{
			entry->Disable();
			entry->SetGameFunc(nullptr);
		}
	}

	void KeepScore(MenuEntry*)
	{
		Process::Write32(0x081C9B00, score);
	}

	void Editor_ScoreMax(MenuEntry* entry)
	{
		Process::Write32(0x081C8CC0, maxscore);
	}


	u16 time = 0;

	void InitTime(MenuEntry* entry)
	{
        Keyboard k("Enter Time \nMax:" + std::to_string(maxtime) + "\nMin:" + std::to_string(0));
		k.IsHexadecimal(false);
        
		//read current
		Process::Read16(0x310366B6, time);

		int result = k.Open(time, time + 1);

		if (result >= 0)
		{
			if (time > maxtime)
				time = maxtime;

			Process::Write16(0x310366B6, time - 1);
			entry->SetGameFunc(KeepTime);
		}
		else
		{
			entry->Disable();
			entry->SetGameFunc(nullptr);
		}
	}

	void KeepTime(MenuEntry*)
	{
		Process::Write16(0x310366B6, time - 1);
	}


	u8 coin = 0;

	void InitCoin(MenuEntry* entry)
	{
		Keyboard k("Enter Coin\nMax:" + std::to_string(maxcoin) + "\nMin:" + std::to_string(0));
		k.IsHexadecimal(false);

		Process::Read8(0x081C9AF8, coin);

		int result = k.Open(coin, coin);
		if (result >= 0)
		{
			if (coin > maxcoin)
				coin = maxcoin;

			Process::Write8(0x081C9AF8, coin);
			entry->SetGameFunc(KeepScore);
		}
		else
		{
			entry->Disable();
			entry->SetGameFunc(nullptr);
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
		//TODO: Read current world status
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


	u8 sceneSkin_TiBGM;

	void SetSceneSkin_TiBGM(MenuEntry* entry)
	{
		u8 current, result;
		Process::Read8(0x305A1010, current);
		if (_SetSceneSkin(result, current))
		{
			sceneSkin_TiBGM = result;
			entry->SetGameFunc(KeepSceneSkin_TiBGM);
			entry->Enable();
		}
		else
		{
			entry->SetGameFunc(nullptr);
			entry->Disable();
		}
	}

	void KeepSceneSkin_TiBGM(MenuEntry*)
	{
		Process::Write8(0x305A1010, sceneSkin_TiBGM);
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
			entry->SetGameFunc(KeepFootSteps);
			entry->Enable();
		}
		else
		{
			entry->Disable();
			entry->SetGameFunc(nullptr);
		}
	}

	void KeepFootSteps(MenuEntry*)
	{
		Process::Write8(0x007ACF3C, footsteps);
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

	void InitLives(MenuEntry* entry)
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
			entry->SetGameFunc(KeepLives);
		}
		else
		{
			entry->Disable();
			entry->SetGameFunc(nullptr);
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
		 * Left input takes precedence
		 * 
		 * Default maximum is 3
		 */
		u32 kdown = Controller::GetKeysDown(true);
		if (kdown & Key::Left)
			Process::WriteFloat(0x317B88DC, -6);
		else if (kdown & Key::Right)
			Process::WriteFloat(0x317B88DC, 6);
		else if (!(kdown & (Key::Left|Key::Right)))
			Process::WriteFloat(0x317B88DC, 0);
	}


	u8 state = 0;

	void SetDamageToBecome(MenuEntry* entry)
	{
		u8 current = 0;
		Process::Read8(0x317B8C00, current);

		const std::vector<std::string> Mstatus = {
			"Small Mario",
			"Super Mario",
			"Fire Mario",
			"Weird Mario",
			"Propellor Mario",
			"Cape Mario",
			"Raccoon Mario",
			"Chara Mario",
			"Big Mario"
		};

		Keyboard k("Select Mario's status ...", Mstatus);
		if (current >= 0 && current <= Mstatus.size()-1)
			k.ChangeSelectedEntry(current);
		
		int result;
		if ((result = k.Open()) >= 0)
		{
			state = (u8)result;
			entry->SetGameFunc(KeepDamageToBecome); 
			entry->Enable();
		}
		else
			entry->Disable();
	}

	void KeepDamageToBecome(MenuEntry*)
	{
		Process::Write8(0x317B8C00, state);
	}


	void ItemCheatAuto(MenuEntry*)
	{
		u32 kdown = Controller::GetKeysDown(false);
		/*if (kdown & (Key::DPadDown|Key::DPadLeft|Key::DPadRight|Key::DPadUp))
			return;
		*/
		
		GameSkin curskin;
		PowerUp result;

		//Special PowerUps depend on game skin
		PowerUp RD, LD = Big, LU = Chara;

		if (!GetGameSkin(curskin))
			return;
		
		switch (curskin)
		{
		case SMB1:
			RD = PowerUp::Weird;

			if (kdown&Key::DPadUp && kdown&Key::L)
			{
				result = LU;
				goto WMstatus;
			}
			else if (kdown&Key::DPadDown && kdown&Key::L)
			{
				result = LD;
				goto WMstatus;
			}
			break;

		case SMB3:
			RD = PowerUp::Raccoon;
			break;

		case SMW:
			RD = PowerUp::Cape;
			break;

		case NSMBU:
			RD = PowerUp::Propellor;
			break;
		
		default:
			return;
		}
		
		if (kdown&Key::DPadDown && kdown&Key::R)
			result = RD;
		
		else if (kdown&Key::DPadUp && kdown&Key::R)
			result = PowerUp::Fire;
		
		else if (kdown&Key::DPadRight && kdown&Key::R)
			result = PowerUp::Super;

		else if (kdown&Key::DPadLeft && kdown&Key::R)
			result = PowerUp::Small;

		else
			return;
		
WMstatus:
		Process::Write8(0x317B8BE8, (u8)result); //status
		Process::Write8(0x317BBE88, (u8)result); //visibility
	}


	void ptr_JumpAuto(MenuEntry*)
	{
		Process::Write32(0x317B9DEC, 0x317D7820);
	}


	void ptr_CourchForce(MenuEntry*)
	{
		Process::Write32(0x317B9DF0, 0x317D78B0);
		Process::Write32(0x317B9DEC, 0x317D7890);
	}


	void ptr_JumpMD_Crouch(MenuEntry*)
	{
		Process::Write32(0x317B9DDC, 0x317D78A0);
	}


	void ptr_JumpDisable(MenuEntry*)
	{
		Process::Write32(0x317B9DDC, 0x317D7810);
	}


	void ptr_CrouchDisable(MenuEntry*)
	{
		Process::Write32(0x317B9DE0, 0x317D7810);
	}


	bool enableCrouch;

	void Toggle_Crouch(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_CrouchS, enableCrouch);
	}

	void Keep_CrouchS(MenuEntry*)
	{
		/**
		 * a byte of first is currnt game skin
		 * 9B:SMB1  A1:SMB3  A7:SMW  AD: NSMBU
		 * 
		 * a byte of last is status of this element
		 * C3:Disable  C7:Enable
		 */				
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableCrouch*0x04+0xC3);
		Process::Write16(0x30F917B0, write);
	}


	GameSkin jMovement;

	void Toggle_JMovement(MenuEntry* entry)
	{
		_Select_KeyBoard(
			entry, 
			Keep_JMovementS, 
			jMovement, 
			"Can Mario reverse on jumping\nSMM1: Disable"
			);
	}

	void Keep_JMovementS(MenuEntry*)
	{
		u16 write = ((u16)(0x9B+(6*jMovement))<<8)+((jMovement==GameSkin::SMB1)? 0xC3: 0xC7);
		Process::Write16(0x30F918D0, write);
	}


	bool enableWallKick;

	void Toggle_WallKick(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_WallKickS, enableWallKick);
	}

	void Keep_WallKickS(MenuEntry*)
	{
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableWallKick*0x04+0xC3);
		Process::Write16(0x30F919F0, write);
	}


	bool enableHipAttack;

	void Toggle_HipAttack(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_HipAttackS, enableHipAttack);
	}

	void Keep_HipAttackS(MenuEntry*)
	{
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableHipAttack*0x04+0xC3);
		Process::Write16(0x30F91B10, write);
	}


	GameSkin swimStyle;

	void Toggle_SwimStyle(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_SwimStyleS, swimStyle);
	}

	void Keep_SwimStyleS(MenuEntry*)
	{
		u16 write = ((u16)(0x9B+(6*swimStyle))<<8)+((swimStyle==GameSkin::NSMBU)? 0xC7: 0xC3);
		Process::Write16(0x30F91C30, write);
	}


	GameSkin starjump;

	void Toggle_StarJump(MenuEntry* entry)
	{
		_Select_KeyBoard(
			entry,
			Keep_StarJumpS, 
			starjump, 
			"Does Mario jump with rotation in star power\nNSMBU: Enable"
			);
	}

	void Keep_StarJumpS(MenuEntry*)
	{
		u16 write = ((u16)(0x9B+(6*starjump))<<8)+((starjump==GameSkin::NSMBU)? 0xC7: 0xC3);
		Process::Write16(0x30F91D50, write);
	}


	bool enableCarry;

	void Toggle_Carry(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_CarryS, enableCarry);
	}

	void Keep_CarryS(MenuEntry*)
	{
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableCarry*0x04+0xC3);
		Process::Write16(0x30F91E70, write);
	}


	bool enableThrowUp;

	void Toggle_ThrowUp(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_ThrowUpS, enableThrowUp);
	}

	void Keep_ThrowUpS(MenuEntry*)
	{
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableThrowUp*0x04+0xC3);
		Process::Write16(0x30F91F90, write);
	}


	bool enableLookUp;

	void Toggle_LookUp(MenuEntry* entry)
	{
		_Select_KeyBoard(entry, Keep_LookUpS, enableLookUp);
	}

	void Keep_LookUpS(MenuEntry*)
	{
		GameSkin curskin;
		if (!GetGameSkin(curskin))
			return;

		u16 write=((0x9B+(6*curskin))<<8)+((u16)enableLookUp*0x04+0xC3);
		Process::Write16(0x30F920B0, write);
	}


	GameSkin SpinJump;

	void Toggle_SpinJump(MenuEntry* entry)
	{
		_Select_KeyBoard(
			entry, 
			Keep_SpinJumpS, 
			SpinJump, 
			"SMM1/SMM3: Disable\nSMW: Can't Spin on air or wall\nNSMBU: Allow all"
			);
	}

	void Keep_SpinJumpS(MenuEntry*)
	{
		u16 write = ((u16)(0x9B+(6*SpinJump))<<8)+0xC3;

		Process::Write16(0x30F921D0, write+(0x04*(SpinJump==NSMBU))); //wu_spinjump is allows spin on air or wall
		Process::Write16(0x30F922F0, write+(0x04*(SpinJump==SMW))); //mw_spinjump
	}


	void CameraSyncMario(MenuEntry*)
	{
		float pos;
		Process::ReadFloat(0x317B87DC, pos); //Mario Y pos
		Process::WriteFloat(0x31490398, pos); //Camera Y pos
	}

	void Editor_SaveTime(MenuEntry*)
	{
		u16 start, result;
		Process::Read16(0x304CB9B8, start);
		Keyboard k("Enter time you want to ...");
		k.IsHexadecimal(false);
		if (k.Open(result, start)==0)
		{
			Process::Write16(0x304CB9B8, result);
		}
	}

	void Editor_Parts_NoLimit(MenuEntry*)
	{
		 /* enemy/item/block/arrow/checkpoint/keycoin/platform/door/bowser */
		u32 offs = 0x305ABA58;
		for (u32 i = 0; i < 9*4; i+=4)
		{
			Process::Write32(offs+i, 0); //main world
			Process::Write32(offs+i+0xA7C, 0); //sub world
		}
	}


	bool GetGameSkin(GameSkin &result)
	{
		u8 tmp;
		if (!Process::Read8(0x305A0FFC, tmp))
			return false;
		if (result>=0 && result <= GameSkin::NSMBU)
			result = (GameSkin)tmp;
		else
			return false;
		return true;
	}


	void _Select_KeyBoard(MenuEntry* entry, void(*Gamefunc)(MenuEntry*), GameSkin &data, const std::string &desc)
	{
		if (!entry)
			return;
		
		Keyboard k(desc, (std::vector<std::string>){"SMM1", "SMM3", "SMW", "NSMBU"});
		if (desc.empty())
			k.DisplayTopScreen=false;
		int result;
		if ((result=k.Open())>=0 && result <= GameSkin::NSMBU)
		{
			data = (GameSkin)result;
			entry->SetGameFunc(Gamefunc);
			entry->Enable();
		}
		else
		{
			entry->SetGameFunc(nullptr);
			entry->Disable();
		}
	}

	void _Select_KeyBoard(MenuEntry* entry, void(*Gamefunc)(MenuEntry*), bool &data, const std::string &desc)
	{
		Keyboard k(desc, (std::vector<std::string>){"Eanble", "Disable"});
		if (desc.empty())
			k.DisplayTopScreen=false;
		int result;
		if ((result=k.Open())>=0)
		{
			data = result^1;
			entry->SetGameFunc(Gamefunc);
			entry->Enable();
		}
		else
		{
			entry->SetGameFunc(nullptr);
			entry->Disable();
		}
	}


	bool _SetSceneSkin(u8 &result, u8 current)
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
