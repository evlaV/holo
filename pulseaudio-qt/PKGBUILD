# Maintainer:Antonio Rojas <arojas@archlinux.org>

pkgname=pulseaudio-qt
pkgver=1.6.1
pkgrel=2
pkgdesc='Qt bindings for libpulse'
arch=(x86_64)
url='https://community.kde.org/Frameworks'
license=(LGPL-2.1-only
         LGPL-3.0-only)
depends=(gcc-libs
         glibc
         libpulse
         qt6-base)
makedepends=(doxygen
             extra-cmake-modules
             qt6-doc
             qt6-tools)
source=(https://download.kde.org/stable/$pkgname/$pkgname-$pkgver.tar.xz{,.sig}
        0001-Expose-CEC-controls-and-properties.patch)
sha256sums=('f21bf30f2ff3e670d2046f966069dc23f5e653ff56bacdb8920c1374264cbc1e'
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
    -DBUILD_QCH=ON \
    -DBUILD_TESTING=OFF \
    -DQT_MAJOR_VERSION=6
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
