# Maintainer: Holo Team
# Contributor: Felix Yan <felixonmars@archlinux.org>
# Contributor: Antonio Rojas <arojas@archlinux.org>
# Contributor: Andrea Scarpino <andrea@archlinux.org>
# Contributor: Alexey D. <lq07829icatm at rambler.ru>

# Holo: Build with the GLIBC_LOCALE_PREGENERATED=ON option
# Holo: Backport patch to stop graphical-session.target (drop >= 6.5.2)

pkgbase=plasma-workspace
pkgname=(plasma-workspace plasma-x11-session)
pkgver=6.7.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=2.1
pkgdesc='KDE Plasma Workspace'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
depends=(accountsservice
         appstream-qt
         dbus
         fontconfig
         freetype2
         glibc
         icu
         kactivitymanagerd
         karchive
         kauth
         kbookmarks
         kcmutils
         kcolorscheme
         kcompletion
         kconfig
         kconfigwidgets
         kcoreaddons
         kcrash
         kde-cli-tools
         kdeclarative
         kded
         kdbusaddons
         kglobalaccel
         kguiaddons
         kholidays
         ki18n
         kiconthemes
         kidletime
         kio
         kio-extras
         kio-fuse
         kirigami
         kirigami-addons
         kitemmodels
         kjobwidgets
         knewstuff
         knighttime
         knotifications
         kpackage
         kparts
         kpipewire
         krunner
         kquickcharts
         kscreenlocker
         kservice
         kstatusnotifieritem
         ksvg
         ksystemstats
         ktexteditor
         ktextwidgets
         kuserfeedback
         kwallet
         kwayland
         kwidgetsaddons
         kwin
         kwindowsystem
         kxmlgui
         layer-shell-qt
         libcanberra
         libice
         libgcc
         libkexiv2
         libksysguard
         libplasma
         libqalculate
         libsm
         libstdc++
         libx11
         libxau
         libxcb
         libxcrypt
         libxcursor
         libxfixes
         libxft
         libxtst
         milou
         ocean-sound-theme
         plasma-activities
         plasma-activities-stats
         prison
         qt6-5compat
         qt6-base
         qt6-declarative
         qt6-location
         qt6-positioning
         qt6-svg
         qt6-tools # for qdbus
         qt6-virtualkeyboard
         sh
         solid
         systemd-libs
         wayland
         xcb-util
         xcb-util-cursor
         xcb-util-image
         xcb-util-wm
         xorg-xmessage
         xorg-xrdb
         xorg-xwayland
         zlib)
makedepends=(baloo
             extra-cmake-modules
             kdoctools
             networkmanager-qt
             plasma-wayland-protocols
             qcoro)
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        # Holo: To be documented
        0003-use-qtvirtualkeyboard.patch)
sha256sums=('438851708a70781ecf3afa0a08488fdc6768b6ed5abca5f202a87e395aa6376f'
            'SKIP'
            '59d41b5073a01a93416c0f0b68b90936261d49ff7f12c4526ce21550f538f98a')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  patch -d $pkgname-$pkgver -Np1 -i "$srcdir/0003-use-qtvirtualkeyboard.patch"
}

build() {

  # Holo: GLIBC_LOCALE_* settings are overriden due to Steam differences
  # with the read only disk.
  # See documentation with CMakeLists.txt of plasma-workspace for details

  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DGLIBC_LOCALE_PREGENERATED=ON \
    -DGLIBC_LOCALE_GEN=OFF \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package_plasma-workspace() {
  optdepends=('appmenu-gtk-module: global menu support for some GTK3 applications'
            'baloo: Baloo search runner'
            'discover: manage applications installation from the launcher'
            'kdepim-addons: displaying PIM events in the calendar'
            'kwayland-integration: Wayland integration for Qt5 applications'
            'kwin-x11: X session window manager'
            'networkmanager-qt: IP based geolocation'
            'plasma-workspace-wallpapers: additional wallpapers'
            'plasma5-integration: use Plasma settings in Qt5 applications'
            'xdg-desktop-portal-gtk: sync font settings to Flatpak apps')
  depends+=(plasma-integration) # Declare runtime dependency here to avoid dependency cycles at build time
  conflicts=(plasma-wayland-session)
  replaces=(plasma-wayland-session)

  DESTDIR="$pkgdir" cmake --install build

  rm -r "$pkgdir"/usr/share/xsessions/plasmax11.desktop
}


package_plasma-x11-session() {
  pkgdesc='Plasma X11 session'
  depends=(plasma-workspace kwin-x11)
  groups=()

  install -Dm644 build/login-sessions/plasmax11.desktop -t "$pkgdir"/usr/share/xsessions
}
