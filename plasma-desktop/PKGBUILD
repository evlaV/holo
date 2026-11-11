# Maintainer: Felix Yan <felixonmars@archlinux.org>
# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: Andrea Scarpino <andrea@archlinux.org>

pkgname=plasma-desktop
pkgver=6.8.2
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=2
pkgdesc='KDE Plasma Desktop'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
depends=(attica
         baloo
         emoji-font # for clock and language KCMs
         glibc
         kbookmarks
         kcmutils
         kcodecs
         kcompletion
         kconfig
         kconfigwidgets
         kcoreaddons
         kcrash
         kdbusaddons
         kdeclarative
         kglobalaccel
         kguiaddons
         ki18n
         kiconthemes
         kio
         kirigami
         kirigami-addons
         kitemmodels
         kjobwidgets
         kmenuedit
         knewstuff
         knotifications
         knotifyconfig
         kpackage
         kpipewire
         krunner
         kscreenlocker
         kservice
         ksvg
         kwidgetsaddons
         kwindowsystem
         kxmlgui
         libcanberra
         libksysguard
         libstdc++
         libwacom
         libx11
         libxcb
         libxkbcommon
         libxkbfile
         libplasma
         plasma-activities
         plasma-activities-stats
         plasma-workspace
         plasma5support
         polkit-kde-agent
         powerdevil
         qt6-5compat
         qt6-base
         qt6-declarative
         sdl2
         solid
         sonnet
         systemd-libs
         systemsettings
         wayland
         xcb-util-keysyms
         xdg-user-dirs)
optdepends=('bluedevil: Bluetooth applet'
            'glib2: kimpanel IBUS support'
            'ibus: kimpanel IBUS support'
            'kaccounts-integration: OpenDesktop integration plugin'
            'kscreen: screen management'
            'libaccounts-qt: OpenDesktop integration plugin'
            'packagekit-qt6: to install new krunner plugins'
            'plasma-nm: Network manager applet'
            'plasma-pa: Audio volume applet'
            'scim: kimpanel SCIM support')
makedepends=(extra-cmake-modules
             intltool
             kaccounts-integration
             kdoctools
             libibus
             packagekit-qt6
             scim
             wayland-protocols)
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
         0001-Revert-lockscreen-drop-vkb-wrapper-use-KWinVirtualKe.patch # Holo specific. The Steam keyboard is an X11 client and cannot show on the lock screen. This patch enables an alternative in-process keyboard on the lock screen.
         0002-Revert-sddm-theme-drop-vkb-wrapper-use-KWinVirtualKe.patch # Holo specific. As above, but for SDDM
         0003-Fix-SDDM-wallpaper.patch # Drop in 6.9
)
sha256sums=('fff6177d217e60ab747cb34e35ef249afab41c72bbd5ea61d3471ef88864bd80'
             'SKIP'
             'cc863db7cdd458805c34a6240566e3e11823aeb9a2e7a8d324f48d81d367787f'
             '5a0d49c033d00bcfe8654739b507981c574b2ca3adeacfca292ff30d93e9db6d'
             '8b625d1750fba7b489d134f48078ac878bf7b403e98bd4573349dbd02e5c34f3')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
               '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  patch -Np1 -d $pkgname-$pkgver -i ../0001-Revert-lockscreen-drop-vkb-wrapper-use-KWinVirtualKe.patch
  patch -Np1 -d $pkgname-$pkgver -i ../0002-Revert-sddm-theme-drop-vkb-wrapper-use-KWinVirtualKe.patch
  patch -Np1 -d $pkgname-$pkgver -i ../0003-Fix-SDDM-wallpaper.patch
}

build() {
  cmake -B build  -S $pkgname-$pkgver \
    -DKDE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
