# Maintainer: Antonio Rojas <arojas@archlinux.org>

pkgname=kscreenlocker
pkgver=6.7.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.1
pkgdesc='Library and components for secure lock screen architecture'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
depends=(glibc
         kcmutils
         kconfig
         kcoreaddons
         kcrash
         kdeclarative
         kglobalaccel
         ki18n
         kidletime
         kio
         kirigami
         knotifications
         kpackage
         ksvg
         kwindowsystem
         kxmlgui
         layer-shell-qt
         libkscreen
         libstdc++
         libx11
         libxcb
         libxi
         pam
         libplasma
         qt6-base
         qt6-declarative
         wayland
         xcb-util-keysyms)
makedepends=(extra-cmake-modules
             kdoctools)
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        kde.pam
        kde-fingerprint.pam 
        kde-smartcard.pam

        # Holo: To be documented
        0001-use-qtvirtualkeyboard.patch)
sha256sums=('76d4bbb1201102e1b5dd34142c55006bf27f3ced39fa64c97a7f44bb1e534dfe'
            'SKIP'
            'adba7bb7c27eb3a572e5e9d3cea0dbeebe59d3634472d1863d14fe892cb13b2b'
            '32734b4e1ec8b7f7e32b6cb2d68285c5c4f15f53736bba085096e76095181241'
            '5d9c31cbf66e8e455b9559c929f184efd598f714743d5a1e6ce20adb44dc4b2d'
            '54325720e785c7b94b0b576c4611e79bd49ddfb3dedd25214ecd010016dae2a0')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  patch -d $pkgname-$pkgver -Np1 -i "$srcdir/0001-use-qtvirtualkeyboard.patch"
}

build() {
  cmake -B build  -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=/usr/lib \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build

  install -Dm644 "$srcdir"/kde.pam "$pkgdir"/usr/lib/pam.d/kde
  install -Dm644 "$srcdir"/kde-fingerprint.pam "$pkgdir"/usr/lib/pam.d/kde-fingerprint
  install -Dm644 "$srcdir"/kde-smartcard.pam "$pkgdir"/usr/lib/pam.d/kde-smartcard
}
