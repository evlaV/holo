# Maintainer: Felix Yan <felixonmars@archlinux.org>
# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: Andrea Scarpino <andrea@archlinux.org>

pkgname=kwindowsystem
pkgver=6.16.0
pkgrel=1.1
pkgdesc='Access to the windowing system'
arch=(x86_64)
url='https://community.kde.org/Frameworks'
license=(LGPL-2.0-only LGPL-3.0-only)
depends=(gcc-libs
         glibc
         libx11
         libxcb
         libxfixes
         qt6-base
         qt6-wayland
         wayland
         xcb-util-keysyms)
makedepends=(doxygen
             extra-cmake-modules
             plasma-wayland-protocols
             qt6-declarative
             qt6-tools
             wayland-protocols)
optdepends=('qt6-declarative: QML bindings')
groups=(kf6)
source=(https://download.kde.org/stable/frameworks/${pkgver%.*}/$pkgname-$pkgver.tar.xz{,.sig}
        0001-avoid-destroying-proxy-objects.patch) # Drop after 6.24.0
sha256sums=('dc3b5ac5e5eaea5b76af8e85f065ddbce91ff7e3fcc13c6d600ad53bb53b1b31'
            'SKIP'
            'b86b9c602b7da092852279a741e198b591b8a4f302c214cad217ccb457b3852f'
            )
validpgpkeys=(53E6B47B45CEA3E0D5B7457758D0EE648A48B3BB # David Faure <faure@kde.org>
              E0A3EB202F8E57528E13E72FD7574483BB57B18D # Jonathan Esk-Riddell <jr@jriddell.org>
              90A968ACA84537CC27B99EAF2C8DF587A6D4AAC1 # Nicolas Fella <nicolas.fella@kde.org>
              1FA881591C26B276D7A5518EEAAF29B42A678C20 # Marco Martin <notmart@gmail.com>
              )

prepare() {
  patch -d "${pkgname}-${pkgver}" -p1 < "0001-avoid-destroying-proxy-objects.patch"
}

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
