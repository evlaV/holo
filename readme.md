# SteamOS Holo Repository

This is an automatically updated mirror of the SteamOS Holo repository built from the SteamOS source packages found [here](https://steamdeck-packages.steamos.cloud/archlinux-mirror/sources). For more information, see the tool that generates this mirror, [evlav](https://github.com/evlav/evlav).

Currently, the only difference between this repository and the official sources is that the `PKGBUILD` URLs that direct to private Valve repositories have been replaced with repositories in this mirror.

> [!WARNING]
> This mirror is automatically generated from scratch and updated automatically. **It may have its history regenerated at any time.**

## Building Packages
To build packages in this repository, clone it and run `makepkg` in the directory of the package you want to build.

```bash
git clone https://github.com/evlaV/holo.git

cd holo/<package>
makepkg -si
```