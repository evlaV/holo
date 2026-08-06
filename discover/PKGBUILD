# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Maintainer (Holo): David Redondo <kde@david-redondo.de>

pkgname=discover
pkgver=6.7.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.1 # Holo: Enable Holo backend
pkgdesc='KDE and Plasma resources management GUI'
arch=(x86_64)
url='https://apps.kde.org/discover/'
license=(LGPL-2.0-or-later)
depends=(appstream-qt
         archlinux-appstream-data
         atomupd-daemon  # Holo: the steamos updater talks to it via dbus
         attica
         discount
         glib2
         glibc
         kcmutils
         kconfig
         kcoreaddons
         kcrash
         kdbusaddons
         ki18n
         kiconthemes
         kidletime
         kio
         kirigami
         kirigami-addons
         kjobwidgets
         knewstuff
         knotifications
         kservice
         kstatusnotifieritem
         kuserfeedback
         kwidgetsaddons
         kwindowsystem
         libgcc
         libstdc++
         purpose
         qcoro
         qqc2-desktop-style
         qt6-base
         qt6-declarative
         qt6-webview)
makedepends=(extra-cmake-modules
             flatpak
             fwupd
             packagekit-qt6)
optdepends=('flatpak: Flatpak packages support'
            'fwupd: firmware update support'
            'packagekit-qt6: to manage packages from Arch Linux repositories (not recommended, use at your own risk)')
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig})
sha256sums=('f28c47569ddffd95c1095ea6c73cfe01a6943bbb3be5d8158d5431c443439f1c'
            'SKIP')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

build() {
  # Holo: HoloBackend should be enabled. It's disabled by default.
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_HoloBackend=ON \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  depends+=(atomupd-daemon) 
  DESTDIR="$pkgdir" cmake --install build
}
