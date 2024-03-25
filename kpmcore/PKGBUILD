# Maintainer: Antonio Rojas <arojas@archlinux.org>

pkgname=kpmcore
pkgver=23.04.2
pkgrel=2.1 # Holo: Don't write fstab entries with invalid mountpoints
pkgdesc='Library for managing partitions'
arch=(x86_64)
url='https://apps.kde.org/partitionmanager/'
license=(GPL2)
depends=(smartmontools kcoreaddons5 kwidgetsaddons5 ki18n5 polkit-qt5 qca-qt5)
makedepends=(extra-cmake-modules)
optdepends=('e2fsprogs: ext2/3/4 support'
	    'xfsprogs: XFS support'
	    'jfsutils: JFS support'
	    'reiserfsprogs: Reiser support'
	    'ntfs-3g: NTFS support'
            'dosfstools: FAT32 support'
            'fatresize: FAT resize support'
            'f2fs-tools: F2FS support'
            'exfat-utils: exFAT support'
            'exfatprogs: exFAT support (alternative to exfat-utils)'
            'nilfs-utils: nilfs support'
            'udftools: UDF support')
source=(https://download.kde.org/stable/release-service/$pkgver/src/$pkgname-$pkgver.tar.xz{,.sig}
        ignore-invalid-mountpoints.patch # Holo: Don't write fstab entries with invalid mountpoints. Fixed in KDE Gear 24.02
       )
sha256sums=('13db9c144042402cf8d9876f4424071e0abd46edc9ed3274197f3a1776038adc'
            'SKIP'
            'abcac2e37d4a39ce1d8fd78d1741181c837063aa2d70b9974cb5f919b943b29f' #ignore-invalid-mounts
            )
validpgpkeys=(CA262C6C83DE4D2FB28A332A3A6A4DB839EAA6D7  # Albert Astals Cid <aacid@kde.org>
              F23275E4BF10AFC1DF6914A6DBD2CE893E2D1C87  # Christoph Feck <cfeck@kde.org>
              D81C0CB38EB725EF6691C385BB463350D6EF31EF) # Heiko Becker <heiko.becker@kde.org>

prepare() {
  patch -d $pkgbase-$pkgver -p1 --input="${srcdir}/ignore-invalid-mountpoints.patch"
}

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}
