# Maintainer: Antonio Rojas <arojas@archlinux.org>

pkgname=kscreenlocker
pkgver=6.4.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=2
pkgdesc='Library and components for secure lock screen architecture'
arch=(x86_64)
url='https://kde.org/plasma-desktop/'
license=(LGPL-2.0-or-later)
backup=(etc/pam.d/kde
        etc/pam.d/kde-fingerprint
        etc/pam.d/kde-smartcard)
depends=(gcc-libs
         glibc
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
             kcmutils
             kdoctools)
optdepends=('kcmutils: configuration module')
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        kde.pam
        kde-fingerprint.pam 
        kde-smartcard.pam
        0001-use-qtvirtualkeyboard.patch)
sha256sums=('3441174426fd18524ca59fa2246f9ee99c31dec0fd89eaa79705e6a32d1dcac3'
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
  patch -d kscreenlocker-6.4.3 -Np1 -i "$srcdir/0001-use-qtvirtualkeyboard.patch"
}

build() {
  cmake -B build  -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=/usr/lib \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build

  install -Dm644 "$srcdir"/kde.pam "$pkgdir"/etc/pam.d/kde
  install -Dm644 "$srcdir"/kde-fingerprint.pam "$pkgdir"/etc/pam.d/kde-fingerprint
  install -Dm644 "$srcdir"/kde-smartcard.pam "$pkgdir"/etc/pam.d/kde-smartcard
}
