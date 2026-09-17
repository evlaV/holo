# Maintainer: Holo team
# Contributor: Antonio Rojas <arojas@archlinux.org>

pkgname=krdp
pkgver=6.7.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=2
pkgdesc='Library and examples for creating an RDP server'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
depends=(freerdp
         glibc
         kcmutils
         kconfig
         kcoreaddons
         kcrash
         kguiaddons
         ki18n
         kirigami-addons
         kpipewire
         kstatusnotifieritem
         libstdc++
         libxkbcommon
         pam
         qt6-base
         qtkeychain-qt6
         systemd-libs
         wayland)
makedepends=(extra-cmake-modules
             plasma-wayland-protocols)
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        0001-Revert-Set-NoNewPrivileges-on-the-krdpserver-systemd.patch # Drop in 6.7.4 onwards
        )
sha256sums=('4d8019b00b20e91e84f34da0d53cbcc2b1ae5a57a1f437a426c6735fcfa414d0'
            'SKIP'
            '929889d92c37d3e6875c85dc134048c7029569fd66229abcecb8d71088a0669b')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  patch -d $pkgname-$pkgver -Np1 -i "$srcdir/0001-Revert-Set-NoNewPrivileges-on-the-krdpserver-systemd.patch"
}


build() {
  cmake -B build  -S $pkgname-$pkgver \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
