# Maintainer: Bruno Pagani <archange@archlinux.org>
# Maintainer: Filipe Laíns (FFY00) <lains@archlinux.org>
# Maintainer: Frederik Schwan <freswa at archlinux dot org>
# Contributor: Mirco Tischler <mt-ml at gmx dot de>

pkgname=fwupd-minimal
pkgver=2.0.3
pkgrel=2
pkgdesc="Simple daemon to allow session software to update firmware"
arch=(x86_64)
url='https://github.com/fwupd/fwupd'
license=(LGPL-2.1-or-later)
depends=(
  bash
  bluez
  curl
  fwupd-efi
  gcc-libs
  glib2
  glibc
  gnutls
  hicolor-icon-theme
  json-glib
  libarchive
  libcbor
  libdrm
  libjcat
  libxmlb
  polkit
  'python>=3.13'
  'python<3.14'
  shared-mime-info
  sqlite
  systemd-libs
  xz
  zlib
)
makedepends=(
  bash-completion
  gnu-efi-libs
  libdrm
  meson
  noto-fonts
  noto-fonts-cjk
  python-cairo
  python-dbus
  python-gobject
  python-jinja
  python-pillow
  vala
  valgrind
)
source=(
  "https://github.com/fwupd/fwupd/releases/download/${pkgver}/fwupd-${pkgver}.tar.xz"{,.asc}
  fwupd.sysusers
  0001-amd-gpu-Split-up-the-VBIOS-P-N-for-the-version.patch
  0001-Fix-an-issue-where-UEFI-capsule-reboot_cleanup-wasn-.patch
)
sha512sums=('68321ecf655f12352fd12182e000d9295c3421015ae13012c37bd5e711a0e240a331a6ae5d17a42c2608be79f005e121470c77c28b5fae61fe3383c7579e2bfd'
            'SKIP'
            '637203080b55eda74a659f58c853a9a723a2dad5da70915b2b0e036c6145a649468ebec700cc83975d9cb5378b9dced8b3a3b26bdbcc75ddc774837355e75deb'
            'e76ddc952818dfe6ea3494f559e811272f08ef2fc55b069a43f54f7742fd715204e40cc2dbdfc0772096aa44bff2379488569c8e4c5f3e4c8870c71e16ff4bd5'
            '5c7a5c6728bfac370b92a6711b6bc0a4afa5f90b61f97a04aea7b6a4ab4e34504aecab7b5475065206370eb08806d658aced0f9b5a07c90b07010ad831bcda22')
b2sums=('82e5170c8f3771685f3c3bed9f02c934104f9953d6dc4eb00290f3a283305a30ae9cebab165c88725a016e86f5610d9699c5f86cc5acf7a32cc4454d82df7c84'
        'SKIP'
        'e65ca7da22a20a40882cfc1fe4479643f9a38c90a4f2c3e71e6e5e3de1d6db212a0f17d600097619fe3cdb0a9b860422f8b0b9a9d45441518e51a7eb12a918bb'
        '16f238962fb98d007b5f15c4c91be0356499c3fb42c780c361471ad9d84844ba9aa3c1577c3e56216ade2c9ab375664cad1f0f9e936f165a9838659c73729065'
        '3c76859707b7d29676b8eb00b84e75dec19bb8b256fc7b7ec21b8c5a9c801cfce0eb3aac9d8d77f818f0b334edb594559d23abbdc9434a836179f826e7cbd7a9')
validpgpkeys=(163EB50119225DB3DF8F49EA17ACBA8DFA970E17) # Richard Hughes <richard@hughsie.com>

prepare() {
  patch -d fwupd-${pkgver} -Np1 -i ../0001-amd-gpu-Split-up-the-VBIOS-P-N-for-the-version.patch
  patch -d fwupd-${pkgver} -Np1 -i ../0001-Fix-an-issue-where-UEFI-capsule-reboot_cleanup-wasn-.patch
}

build() {
  local meson_options=(
    -D docs=disabled
    -D efi_binary=false
    -D launchd=disabled
    -D supported_build=enabled
    -D systemd_unit_user=fwupd
    -D hsi=disabled
    -D introspection=disabled
    -D umockdev_tests=disabled
    -D plugin_redfish=disabled
    -D plugin_tpm=disabled
    -D plugin_flashrom=disabled
    -D plugin_logitech_bulkcontroller=disabled
    -D passim=disabled
    -D plugin_cpu=disabled
    -D plugin_modem_manager=disabled
    -D plugin_scsi=disabled
    -D plugin_bcm57xx=disabled
    -D plugin_redfish=disabled
    -D plugin_powerd=disabled
    -D fish_completion=false
  )

  arch-meson fwupd-${pkgver} build "${meson_options[@]}"
  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

_pick() {
  local p="$1" f d; shift
  for f; do
    d="$srcdir/$p/${f#$pkgdir/}"
    mkdir -p "$(dirname "$d")"
    mv "$f" "$d"
    rmdir -p --ignore-fail-on-non-empty "$(dirname "$f")"
  done
}

package() {
  depends+=(
    libarchive.so
    libcbor.so
    libcurl.so
    libgudev-1.0.so
    libjson-glib-1.0.so
  )
  optdepends=(
    'python-dbus: Firmware packaging tools'
    'python-gobject: Firmware packaging tools'
    'udisks2: UEFI firmware upgrade support'
  )
  provides=(libfwupd.so)
  backup=(
    'etc/fwupd/fwupd.conf'
    'etc/fwupd/remotes.d/lvfs-testing.conf'
    'etc/fwupd/remotes.d/lvfs.conf'
    'etc/fwupd/remotes.d/vendor-directory.conf'
  )

  meson install -C build --destdir "${pkgdir}"
  # Add fwupd user https://bugs.archlinux.org/task/79653
  install -D -m644 fwupd.sysusers "${pkgdir}"/usr/lib/sysusers.d/fwupd.conf
  # Remove the tests
  rm -r "${pkgdir}"/usr/{lib,share}/installed-tests/
  # Conflicts with the dbxtool package
  mv "${pkgdir}"/usr/bin/{,fwupd-}dbxtool
  mv "${pkgdir}"/usr/share/man/man1/{,fwupd-}dbxtool.1

}
