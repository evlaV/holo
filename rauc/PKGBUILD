# Maintainer (Upstream): David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <ludovico.denittis@collabora.com>

pkgname=rauc
pkgver=1.12
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
  glib2-devel
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
source=(
  https://github.com/rauc/rauc/releases/download/v$pkgver/$pkgname-$pkgver.tar.xz{,.asc}
  $pkgname.tmpfiles
)
sha512sums=('c768cde19f0f75c0c9c373586bac0589d438f2ee4ab28fb24e492a6ae5f6672b1ff2daa1e4496ece45ba18499e2f177bf28902091122edacf556a6cde7be926f'
            'SKIP'
            '35173525a8529c4d5a227186db353107193bf8cdd3e8ab0cd94c418b34187be50fe379bcabf623bfddbf1916e8e7e965800a269e823f7ee9c26f44ac1f689c94')
b2sums=('8c2c0bcba1e2bc284695b6f5cf274667a51a64d97891f8cf10f142c558710ff4057235bb7c2d885a4a4a8c92d860b19b6d7bba1a938f496e2107bf2d339a9945'
        'SKIP'
        'e970b292f89cf4663b4ea318965444dc9bb47ef5f937143f180a372c5906f534e7c2f234dfa824b70434011069ea7758e4d6c8afd73dd5c4d92337da7e281eca')
validpgpkeys=("977843FD5C3EBF76BAD4008EA58CC53DBF05E090")  # Jan Lübbe <jlu@pengutronix.de>

build() {
  # Holo: disable streaming option until we switch to verity update bundle type
  #  https://gitlab.steamos.cloud/holo-team/tasks/-/issues/672
  arch-meson $pkgname-$pkgver build -Dstreaming=false
  meson compile -C build

}

check() {
  local meson_tests=($(meson test -C build --list))
  # disable broken tests
  local disabled_tests=()
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
  install -vDm 644 $pkgname.tmpfiles "$pkgdir/usr/lib/tmpfiles.d/$pkgname.conf"
}
