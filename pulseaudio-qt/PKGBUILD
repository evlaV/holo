# Maintainer:Antonio Rojas <arojas@archlinux.org>

pkgname=pulseaudio-qt
pkgver=1.8.1
pkgrel=1.1
pkgdesc='Qt bindings for libpulse'
arch=(x86_64)
url='https://community.kde.org/Frameworks'
license=(LGPL-2.1-only
         LGPL-3.0-only)
depends=(glibc
         libpulse
         libstdc++
         qt6-base)
makedepends=(extra-cmake-modules)
source=(https://download.kde.org/stable/$pkgname/$pkgname-$pkgver.tar.xz{,.sig}
        # Holo: To be documented
        0001-Expose-CEC-controls-and-properties.patch)
sha256sums=('79619c55b94808aa7d307fb234ad39a1096d088f21f806be0e788be79a76b3c9'
            'SKIP'
            '77e632be5764bb12866eedffd6e8df281480e6e35b335829bbe646d863c4014b')
validpgpkeys=(2D1D5B0588357787DE9EE225EC94D18F7F05997E  # Jonathan Riddell <jr@jriddell.org>
              90A968ACA84537CC27B99EAF2C8DF587A6D4AAC1) # Nicolas Fella <nicolas.fella@kdab.com>

prepare() {
  cd $pkgname-$pkgver
  patch -Np1 -i ../0001-Expose-CEC-controls-and-properties.patch
}

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
