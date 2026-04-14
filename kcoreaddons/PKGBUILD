# Maintainer: Felix Yan <felixonmars@archlinux.org>
# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: Andrea Scarpino <andrea@archlinux.org>

pkgname=kcoreaddons
pkgver=6.16.0
pkgrel=1.1
pkgdesc='Addons to QtCore'
arch=(x86_64)
url='https://community.kde.org/Frameworks'
license=(LGPL-2.0-only LGPL-3.0-only)
depends=(gcc-libs
         glibc
         qt6-base
         systemd-libs)
makedepends=(doxygen
             extra-cmake-modules
             pyside6
             python-build
             python-setuptools
             qt6-declarative
             qt6-tools)
optdepends=('pyside6: Python bindings'
            'qt6-declarative: QML bindings')
groups=(kf6)
source=(https://download.kde.org/stable/frameworks/${pkgver%.*}/$pkgname-$pkgver.tar.xz{,.sig}
        0001-Backport-Remove-control-characters-when-quoting-args.patch) # Can be removed in 6.26.0
sha256sums=('798a2744c296d13b216eadd7e5d801a6fd6956944a2147ab2830c399930ae2a0'
            'SKIP'
            '193b23b297f0cf4491319b0a04129f2bb10bfb6fc2a4b0194c999f774dcf23ca')
validpgpkeys=(53E6B47B45CEA3E0D5B7457758D0EE648A48B3BB  # David Faure <faure@kde.org>
              E0A3EB202F8E57528E13E72FD7574483BB57B18D  # Jonathan Esk-Riddell <jr@jriddell.org>
              90A968ACA84537CC27B99EAF2C8DF587A6D4AAC1) # Nicolas Fella <nicolas.fella@kde.org>

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
