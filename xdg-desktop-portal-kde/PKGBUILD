# Maintainer: Antonio Rojas <arojas@archlinux.org>

pkgname=xdg-desktop-portal-kde
pkgver=6.4.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=2
pkgdesc='A backend implementation for xdg-desktop-portal using Qt/KF5'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
depends=(gcc-libs
         glibc
         kconfig
         kcoreaddons
         kcrash
         kglobalaccel
         kguiaddons
         kiconthemes
         ki18n
         kio
         kio-fuse
         kirigami
         kirigami-addons
         kitemviews
         knotifications
         kpipewire
         kservice
         kstatusnotifieritem
         kwayland
         kwindowsystem
         libxkbcommon
         plasma-workspace
         qt6-base
         qt6-declarative
         qt6-wayland
         wayland
         xdg-desktop-portal)
makedepends=(extra-cmake-modules
             plasma-wayland-protocols
             wayland-protocols)
provides=(xdg-desktop-portal-impl)
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        0001-Skip-authentication-checks-for-Steam-in-the-screenca.patch)
sha256sums=('3fec71e005abe83b3d593a74bc3304c178d605883fe3b77f915c64cf45c1fc27'
            'SKIP'
            '2b790883268a5c9b6b544b2d72987f46cde18770c53325f5980eaf786d88b7e6')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  patch -d xdg-desktop-portal-kde-6.4.3 -Np1 -i "$srcdir/0001-Skip-authentication-checks-for-Steam-in-the-screenca.patch"
}

build() {
  cmake -B build  -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
