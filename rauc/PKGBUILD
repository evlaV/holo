# Maintainer (Upstream): David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <ludovico.denittis@collabora.com>

pkgname=rauc
pkgver=1.11.1
pkgrel=1.1
pkgdesc="Safe and secure software updates for embedded Linux"
arch=(x86_64)
url="https://rauc.io"
license=(LGPL-2.1-or-later)
depends=(
  gcc-libs
  glibc
  libnl
  openssl
  sh
)
makedepends=(
  curl
  dbus
  glib2
  json-glib
  meson
  python
  systemd
  util-linux
)
checkdepends=(squashfs-tools)
optdepends=(
  'casync: for casync conversion support'
  'cryptsetup: for disk encryption support'
  'dosfstools: for creating and checking FAT filesystems'
  'e2fsprogs: for creating and checking ext2/3/4 filesystems'
  'efibootmgr: for interacting with EFI boot manager'
  'grub: for GRUB support'
  'mtd-utils: for interacting with MTD devices'
  'squashfs-tools: for creating and inspecting bundles'
  'uboot-tools: for u-boot support'
)
source=(https://github.com/rauc/rauc/releases/download/v$pkgver/$pkgname-$pkgver.tar.xz{,.asc})
sha512sums=('09f6e7218f884404b56d9d69a028e6098ab2c3d44033d107dcfeffa3ed26ccbd7fff0c27ba1b7c9a74c635b7483f2db1253da148a695bd7db75a2a674438e0f3'
            'SKIP')
b2sums=('ba1aa015be1b28f50014ccd43154b296170faa680f97e27e14a98d6af58f0b0151cef33f4fb4f13bfd304a278edbcd7d9cc9134612ae7a14de04c3a169ab9e00'
        'SKIP')
validpgpkeys=("977843FD5C3EBF76BAD4008EA58CC53DBF05E090")  # Jan Lübbe <jlu@pengutronix.de>

build() {
  # Holo: disable streaming option until we switch to verity update bundle type
  #  https://gitlab.steamos.cloud/holo-team/tasks/-/issues/672
  arch-meson $pkgname-$pkgver build -Dstreaming=false
  meson compile -C build

}

check() {
  local meson_tests=($(meson test -C build --list))
  # disable broken tests: https://github.com/rauc/rauc/issues/1311
  local disabled_tests=(service)
  for target in "${disabled_tests[@]}"; do
    for i in "${!meson_tests[@]}"; do
      if [[ ${meson_tests[i]} = $target ]]; then
        unset 'meson_tests[i]'
      fi
    done
  done

  meson test -C build "${meson_tests[@]}"
}

package() {
  depends+=(
    curl libcurl.so
    glib2 lib{gobject,gio,glib}-2.0.so
    json-glib libjson-glib-1.0.so
    util-linux-libs libfdisk.so
  )

  meson install -C build --destdir "$pkgdir"
  install -vdm 755 "$pkgdir/etc/$pkgname/"
  install -vDm 644 $pkgname-$pkgver/contrib/{grub.conf,uboot.sh} -t "$pkgdir/usr/share/doc/$pkgname/"
}
