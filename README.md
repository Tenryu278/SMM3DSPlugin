# Super Mario Maker for Nintendo 3DS (v1.05) Plugin

[![Makefile CI](https://github.com/Tenryu278/SMM3DSPlugin/actions/workflows/makefile.yml/badge.svg)](https://github.com/Tenryu278/SMM3DSPlugin/actions/workflows/makefile.yml)

This plugin supported only Super Mario Maker for Nintendo 3DS.

-----------------------------------------------

This plugin tested on:
```
Super Mario Maker for Nintendo 3DS v1.05 (Region: JPN)

New Nintendo 3DS
Lime3DS 2115 Windows MSVC
https://github.com/Lime3DS/Lime3DS/releases/tag/2115
```
It may doesn't working well on other console or emulator

# Installation
> You need a hacked 3ds console. See more [3ds Hacks Guide](https://3ds.hacks.guide/).

## For 3DS
1. Open your SD card and copy built 3gx file to `sd:/luma/Plugins/{TitleID}/`.

2. Boot 3ds after mount SD card.

3. Press `L+DPad-Down+Select` to Open Rosalina menu and enable PluginLoader.

4. Done! You successful to installing if display notification of **Plugin Ready!** when launched game.

## For [Citra](https://github.com/PabloMK7/citra)
1. Launch Citra

2. Select **Open Citra Folder** from File tab.

3. Copy built 3gx file to `sdmc/luma/Plugins/{TitleID}/`.

4. Open Citra Configuration and Check to **Enable 3GX plugin loader** from System tab.

### What is TitleID

A specific ID to identify the game. It's different by region.

The TitleID of SMM3DS is:

- JPN: `00040000001A0300`
- USA: `00040000001A0400`
- EUR: `00040000001A0500`

see more [3dsdb](https://3dsdb.com/)

# Build
1. Install devkitARM and [libctru](https://github.com/devkitPro/libctru) following [the devkitpro wiki](https://devkitpro.org/wiki/Getting_Started).

2. Install latest [3gxtool](https://gitlab.com/thepixellizeross/3gxtool) and [libctrpf](https://gitlab.com/thepixellizeross/ctrpluginframework) on your devkitpro directory.

3. Run `make` command on the repository.

# [ftpd.py](ftpd.py)
This file is use for install plugin to 3ds via [ftpd](https://github.com/mtheall/ftpd). 

To set IP address and Port number, create `IP_PORT.txt` on top directory and write them by 2 lines.

For Example:
```
192.168.1.15
5000
```

# Credits
- devkitARM by devkitpro
- [libctru](https://github.com/devkitPro/libctru) by devkitpro
- [libctrpf](https://gitlab.com/thepixellizeross/ctrpluginframework) by [The Pixellizer Group](https://gitlab.com/thepixellizeross)
- [3gxtool](https://gitlab.com/thepixellizeross/3gxtool) by [The Pixellizer Group](https://gitlab.com/thepixellizeross)

Source code is mirrored from [CTRPluginFramework-BlankTemplate](https://github.com/PabloMK7/CTRPluginFramework-BlankTemplate).


# License

This software is licensed under [MIT](LICENSE).
