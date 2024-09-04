#include <3ds.h>
#include <csvc.h>
#include <CTRPluginFramework.hpp> //include all headers of libctrpf
#include <vector>
#include <cheats.hpp>

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }	
	
    // Init our menu entries & folders
	void InitMenu(PluginMenu &menu)
	{   
        MenuFolder* playing = new MenuFolder(
            "PlayingCodes", 
            "These code are valid on playing mode."
        );
        
        MenuFolder* editor = new MenuFolder(
            "EditorCodes", 
            "These code are valid on editor mode."
        );

        menu += playing;
        menu += editor;
        
        /*[--play--]*/
        *playing += new MenuEntry(
            "Set Score", 
            nullptr, 
            SMM3DS::InitScore,
            "Press keyboard to change score\nPress checkbox to keep score"
        );

        *playing += new MenuEntry(
            "Set Time", 
            nullptr, 
            SMM3DS::InitTime, 
            "Press keyboard to change time\nPress checkbox to keep time"
        );

        *playing += new MenuEntry(
            Color::Yellow << "Set Coin",
            nullptr,
            SMM3DS::InitCoin,
            "Press keyboard to change coin\nPress checkbox to keep coin"
        );

        *playing += new MenuEntry(
            "Set Auto Scroll",
            nullptr,
            SMM3DS::SetAutoScroll,
            "Set auto scroll.\nThis code is valid on both editor mode and play mode."
        );

        *playing += new MenuEntry(
            "Enable Scrolling UP",
            SMM3DS::EnableScrollUp
        );

        *playing += new MenuEntry(
            "Change Scene Skin",
            nullptr,
            SMM3DS::SetSceneSkin,
            "Change Scene skin"
        );

        *playing += new MenuEntry(
            "Change Scene Skin(Tile and BGM only)",
            nullptr,
            SMM3DS::SetSceneSkin_TiBGM,
            Color::Blue<<"Note: Process will be slow while enable this cheat"
        );

        *playing += new MenuEntry(
            "Change footsteps",
            nullptr,
            SMM3DS::SetFootSteps,
            "Change footstep sounds\nPress checkbox to keep\nThis code is valid on both editor mode and play mode."
        );

        *playing += new MenuEntry(
            "Invincible",
            SMM3DS::Invincible
        );

        *playing += new MenuEntry(
            "Always Star Power",
            SMM3DS::StarPower,
            "This doesn't working for graphics"
        );

        *playing += new MenuEntry(
            "Set Mario's lives",
            nullptr,
            SMM3DS::InitLives,
            "Press keyboard to change lives\nPress checkbox to keep lives\n"+
            (Color::Blue<<"Note: If you lives is below 0, you'll be GameOver when quit cource")
        );

        *playing += new MenuEntry(
            "Disable Helper mode",
            SMM3DS::DisableHelper,
            "Disable helper mode on Super Mario Challenge \nMistakes count will always be 0"
        );

        *playing += new MenuEntry(
            "Faster",
            SMM3DS::Faster,
            "If C-pad(or D-pad) is not pressed, you'll stop immediately"
        );

        *playing += new MenuEntry(
            "Damage to become ...",
            nullptr,
            SMM3DS::SetDamageToBecome,
            Color::Blue<<"Note: This doesn't work for small Mario"
        );

        *playing += new MenuEntry(
            "ItemCheat",
            SMM3DS::ItemCheatAuto,
            (std::string)"---Usage---\n"+
FONT_DL+FONT_R+": Small Mario\n"+
FONT_DR+FONT_R+": Super Mario\n"+
FONT_DU+FONT_R+": Fire Mario\n"+
FONT_DD+FONT_R+": Weird/Raccoon/Cape/Propellor Mario\n(Depends on Game skin)\n\n"+

"--SMB1 only--\n"+
FONT_DD+FONT_L+": Big Mario\n"+
FONT_DU+FONT_L+": Chara Mario\n"+
(Color::Blue<<"Note: This is incomplete so it may doesn't working well")
        );

        *playing += new MenuEntry(
            "AutoJump", 
            SMM3DS::ptr_JumpAuto, 
            "Mario always jumping while enable this code"
        );

        *playing += new MenuEntry(
            "ForceCrouch",
            SMM3DS::ptr_CourchForce,
            "Mario always crouching while enable this code"
        );

        *playing += new MenuEntry(
            "MidAir Crouch Jump",
            SMM3DS::ptr_JumpMD_Crouch,
            "You can jump in mid air but any jumps will be with crouching while enable this code\nRecommend to use with Sync camera"
        );

        *playing += new MenuEntry(
            "Disable Jump",
            SMM3DS::ptr_JumpDisable,
            "Disable Jump while enable this code"
        );

        *playing += new MenuEntry(
            "Disable Crouching",
            SMM3DS::ptr_CrouchDisable,
            "Disable Crouching while enable this code"
        );

        *playing += new MenuEntry(
            "Toggle Crouch",
            nullptr,
            SMM3DS::Toggle_Crouch
        );

        *playing += new MenuEntry(
            "Set Movement of Jump",
            nullptr,
            SMM3DS::Toggle_JMovement
        );

        *playing += new MenuEntry(
            "Toggle WallKick",
            nullptr,
            SMM3DS::Toggle_WallKick
        );

        *playing += new MenuEntry(
            "Toggle HipAttack",
            nullptr,
            SMM3DS::Toggle_HipAttack
        );

        *playing += new MenuEntry(
            "Set SwimStyle",
            nullptr,
            SMM3DS::Toggle_SwimStyle
        );

        *playing += new MenuEntry(
            "Set StarJump",
            nullptr,
            SMM3DS::Toggle_StarJump
        );

        *playing += new MenuEntry(
            "Toggle Carry",
            nullptr,
            SMM3DS::Toggle_Carry
        );

        *playing += new MenuEntry(
            "Toggle ThrowUp",
            nullptr,
            SMM3DS::Toggle_ThrowUp
        );

        *playing += new MenuEntry(
            "Toggle LookUp",
            nullptr,
            SMM3DS::Toggle_LookUp
        );

        *playing += new MenuEntry(
            "Set SpinJump",
            nullptr,
            SMM3DS::Toggle_SpinJump
        );

        *playing += new MenuEntry(
            "Sync Camera",
            SMM3DS::CameraSyncMario,
            "Moving camera in sync with Mario's Y position while enable this code"
        );


        /*[--editor--]*/
        *editor += new MenuEntry(
            "MaxScore(Editor)", 
            SMM3DS::Editor_ScoreMax, 
            "Keep max score(" + std::to_string(SMM3DS::maxscore) + ") \nThis code can use only EditorMode."
        );

        *editor += new MenuEntry(
            "Change time(Savable)",
            nullptr,
            SMM3DS::Editor_SaveTime,
            "It will works when started course after enable this cheat"
        );
        
        /*root*/

	}

    int main(void)
    {
        PluginMenu* menu = new PluginMenu(
            "SMM3DS v1.05",
             0, 1, 0, 
R"(Super Mario Maker for Nintendo 3DS (v1.05) Plugin

This software is licensed under MIT
This has no warranty or liability
https://github.com/Tenryu278/SMM3DSPlugin/blob/master/LICENSE

Github repository:
https://github.com/Tenryu278/SMM3DSPlugin

Full credits is here:
https://github.com/Tenryu278/SMM3DSPlugin?tab=readme-ov-file#credits

Copyright (c) 2024 Tenryu278)"
        );

        // Synchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        if (SMM3DS::IsSMM3DS(Process::GetTitleID()))
        {
            // Init our menu entries & folders
            InitMenu(*menu);
        }
        else
            OSD::Notify("This Plugin does not supported on this game.", Color::Red);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        // Exit plugin
        return (0);
    }
}
