# Maintainer (Upstream): David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <ludovico.denittis@collabora.com>

pkgname=rauc
pkgver=1.14
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
checkdepends=(squashfs-tools python-dasbus)
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

  # Holo: Backport two upstream fixes for OpenSSL 3.5
  # Already merged upstream, should be included in the upcoming RAUC 1.15
  # Ref https://github.com/rauc/rauc/pull/1697
  src-context-fix-library-reinitialization.patch
  src-signature-fix-compatibility-with-OpenSSL-3.5-for.patch
)
sha512sums=('910c1379817d2f5980919c8ca4074a999732624e5a4eaf82aadeda1efa4671ce80ec86150f231d76a2137587f00f52e7a74e4da3a61ab2ab95b4dab2a5e79939'
            'SKIP'
            '35173525a8529c4d5a227186db353107193bf8cdd3e8ab0cd94c418b34187be50fe379bcabf623bfddbf1916e8e7e965800a269e823f7ee9c26f44ac1f689c94'
            '64cb4fdb69a4f8a82623edd6f5cb4267039174aa16fd587a5b363f647224973a7df627a24c9a6f54810c106308b06bf5d7d6da2f74f5add51625e6dab1a0badb'
            '01879868156b71a5355c1b316be9c5efe28264d1dfdfadb5f6c6be983060c9e7ec6f9cb67e2c502ce825837d44ef2bba7b87f4db861e05a35c484494bd45446f')
b2sums=('3698dea9c065806b18c00049aefd4b03a6407c929e381745291627b2d23101f48fe2d3842ba29e76929468f5290ad57aa82de0d59ffdbe5ae2e2b3e6cedb81a3'
        'SKIP'
        'e970b292f89cf4663b4ea318965444dc9bb47ef5f937143f180a372c5906f534e7c2f234dfa824b70434011069ea7758e4d6c8afd73dd5c4d92337da7e281eca'
        '7ea83550a4304ec5c1c03ebf3e376004f5df43f7124de6c9ffd430051189c44d64c2aa28a6d4ab3aa695c38290c815dbd3f75627846797235cfaa59d5674bb8d'
        'db6565312a00fdcafcb4cb524eac58d2c18aa54137a94d70c275a4f9789849558d350eaca79e3fd960c4f9701e1931c915cfe6752991234f3a9f63d36e7aa4a4')
validpgpkeys=("977843FD5C3EBF76BAD4008EA58CC53DBF05E090")  # Jan Lübbe <jlu@pengutronix.de>

prepare() {
  for patch in "${source[@]}"
  do
    case $patch in
      *.patch)
        echo "# Applying ${patch}"
        patch -d "${pkgname}"-${pkgver} -p1 -i "${srcdir}"/"${patch}"
        ;;
    esac
  done
}

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
