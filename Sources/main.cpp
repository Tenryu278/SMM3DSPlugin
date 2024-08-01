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
	void InitMenu(PluginMenu &menu, std::vector<MenuFolder*> &folders)
	{   
        if (folders.size() != 2)
            return;

        //Add folders
        for (size_t i = 0; i < folders.size(); i++)
        {
            if (folders[i] == nullptr)
                return;
            menu += folders[i];
        }
        
        /*[--play--]*/
        *folders[0] += new MenuEntry(
            "Set Score", 
            SMM3DS::KeepScore, 
            SMM3DS::InitScore,
            "Press keyboard to change score\nPress checkbox to keep score"
        );

        *folders[0] += new MenuEntry(
            "Set Time", 
            SMM3DS::KeepTime, 
            SMM3DS::InitTime, 
            "Press keyboard to change time\nPress checkbox to keep time"
        );

        *folders[0] += new MenuEntry(
            Color::Yellow << "Set Coin",
            SMM3DS::KeepCoin,
            SMM3DS::InitCoin,
            "Press keyboard to change coin\nPress checkbox to keep coin"
        );

        *folders[0] += new MenuEntry(
            "Set Auto Scroll",
            nullptr,
            SMM3DS::SetAutoScroll,
            "Set auto scroll.\nThis code is valid on both editor mode and play mode."
        );

        *folders[0] += new MenuEntry(
            "Enable Scrolling UP",
            SMM3DS::EnableScrollUp
        );

        *folders[0] += new MenuEntry(
            "Change Scene Skin",
            nullptr,
            SMM3DS::SetSceneSkin,
            "Change Scene skin"
        );

        *folders[0] += new MenuEntry(
            "AutoJump", 
            SMM3DS::AutoJump, 
            "Mario always jumping while enable this code"
        );

        /*[--editor--]*/
        *folders[1] += new MenuEntry(
            "MaxScore(Editor)", 
            SMM3DS::Editor_ScoreMax, 
            "Keep max score(" + std::to_string(SMM3DS::maxscore) + ") \nThis code can use only EditorMode."
        );
        
        /*root*/
        menu += new MenuEntry("Message", nullptr, [](MenuEntry *entry)->void {
            std::string tid;
            Process::GetTitleID(tid);
            MessageBox("", tid)();
        });

	}

    int main(void)
    {
        PluginMenu* menu = new PluginMenu(
            "SMM3DS v1.05",
             0, 1, 0,
             "A plugin for SMM3DS(version1.05)"
        );

        // Synchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        MenuFolder* play = new MenuFolder(
            "PlayingCodes", 
            "These code are valid on playing."
        );
        
        MenuFolder* editor = new MenuFolder(
            "EditorCodes", 
            "These code are valid on editor mode."
        );

        std::vector<MenuFolder*> folders = {play, editor};

        if (Process::GetTitleID() == SMM3DS::idjp)
        {
            // Init our menu entries & folders
            InitMenu(*menu, folders);
        }
        else
            OSD::Notify("This Plugin does not supported on this game.", Color::Red);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        //delete folder after lanched menu
        delete play;
        delete editor;

        // Exit plugin
        return (0);
    }
}
