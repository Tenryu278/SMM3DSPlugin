# Super Mario Maker for Nintendo 3DS (v1.0.5) Plugin

[![Makefile CI](https://github.com/Tenryu278/SMM3DSPlugin/actions/workflows/makefile.yml/badge.svg)](https://github.com/Tenryu278/SMM3DSPlugin/actions/workflows/makefile.yml)

This plugin only runs on Super Mario Maker for Nintendo 3DS.

-----------------------------------------------

# Installation
> You need a hacked 3ds console. See more [3ds Hacks Guide](https://3ds.hacks.guide/).

## For 3DS
Open your SD card and copy built 3gx file to `sdmc/luma/Plugins/{TitleID}`.

## For [Citra](https://github.com/PabloMK7/citra)
Launch to click **Open Citra Folder** from File tab and copy built 3gx file to `sdmc/luma/Plugins/{TitleID}`.

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

Source codes were clone from [CTRPluginFramework-BlankTemplate](https://github.com/PabloMK7/CTRPluginFramework-BlankTemplate).


# License

This software is licensed under [MIT](LICENSE).
