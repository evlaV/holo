# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Maintainer (Holo): David Redondo <kde@david-redondo.de>

pkgname=discover
pkgver=5.27.8
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.2 # Holo change to enable steamos backend.
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
        fix-too-many-open-files.patch # Holo: prevent fd exhaustion when updating many Flatpak refs
        reduce-review-cache-buffer.patch # Holo: load/quit application pages faster (fixed in V5.27.9)
        )
sha256sums=('f1c5fcbbae52bdcba4745c154ef2a900fb7eafbe88d2d769837bb38ad9020fd3'
            'SKIP'
            'ed711f62cc63dce1d1f43d0dbd6759d090395202cbe379b0950f75b4df7748d5'
            '11386812149c6633388c599f17b5069b49fefd86a833aaa2d98d0b97414f91d0')
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
  patch -d $pkgbase-$pkgver -p1 --input="${srcdir}/fix-too-many-open-files.patch"
  patch -d $pkgbase-$pkgver -p1 --input="${srcdir}/reduce-review-cache-buffer.patch"
}

package() {
  depends+=(atomupd-daemon-git) # the steamos updater talks to it via dbus
  DESTDIR="$pkgdir" cmake --install build
}
