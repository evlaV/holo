# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Maintainer (Holo): David Redondo <kde@david-redondo.de>

pkgname=discover
pkgver=5.27.5
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.1 # Holo: enable SteamOS updater and include fix to it
pkgdesc='KDE and Plasma resources management GUI'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL)
depends=(knewstuff kidletime qt5-graphicaleffects appstream-qt archlinux-appstream-data
         kirigami2 discount kuserfeedback purpose qt5-webview)
makedepends=(extra-cmake-modules plasma-framework packagekit-qt5 flatpak fwupd)
optdepends=('packagekit-qt5: to manage packages from Arch Linux repositories (not recommended, use at your own risk)'
            'flatpak: Flatpak packages support'
            'fwupd: firmware update support')
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        0001-Fix-SteamOS-dbus-path.patch)
sha256sums=('785f788a16e065d28f6422274e2d5a7bcbe63b0f5814206c50c401a3003ab31b'
            'SKIP'
            'edc0efef57b6d89773af60fc030c15980c151aa027a41fbe1dd26a3c820cc9fc')
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

prepare() {
  patch -d $pkgbase-$pkgver -p1 --input="${srcdir}/0001-Fix-SteamOS-dbus-path.patch"
}

package() {
  depends+=(atomupd-daemon-git) # the steamos updater talks to it via dbus
  DESTDIR="$pkgdir" cmake --install build
}
