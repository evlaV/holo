# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Maintainer (Holo): David Redondo <kde@david-redondo.de>

pkgname=discover
pkgver=5.27.10.1
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.1 # Holo change to enable steamos backend.
pkgdesc='KDE and Plasma resources management GUI'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL)
depends=(knewstuff5 kidletime5 qt5-graphicaleffects appstream-qt5 archlinux-appstream-data
         kirigami2 discount kuserfeedback5 purpose5 qt5-webview)
makedepends=(extra-cmake-modules plasma-framework5 packagekit-qt5 flatpak fwupd)
optdepends=('packagekit-qt5: to manage packages from Arch Linux repositories (not recommended, use at your own risk)'
            'flatpak: Flatpak packages support'
            'fwupd: firmware update support')
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig})
sha256sums=('d856aeb1288b966955e04d5669cfc2b3fb659fdd3f07b869a41dc705a7f6d1ac'
            'SKIP')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_TESTING=OFF \
    -DBUILD_SteamOSBackend=ON
  cmake --build build
}

package() {
  depends+=(atomupd-daemon-git) # the steamos updater talks to it via dbus
  DESTDIR="$pkgdir" cmake --install build
}
