# Maintainer: Bruno Pagani <archange@archlinux.org>
# Maintainer: Filipe Laíns (FFY00) <lains@archlinux.org>
# Maintainer: Frederik Schwan <freswa at archlinux dot org>
# Contributor: Mirco Tischler <mt-ml at gmx dot de>

pkgname=fwupd-minimal
pkgver=1.9.19
pkgrel=5
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
  libgudev
  libgusb
  libjcat
  libxmlb
  polkit
  'python>=3.11'
  'python<3.12'
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
checkdepends=(umockdev)
source=(
  "https://github.com/fwupd/fwupd/releases/download/${pkgver}/fwupd-${pkgver}.tar.xz"{,.asc}
  amd-gpu.patch
  source-version.patch
  fwupd.sysusers
)
sha512sums=('e20f16aa2cf528ecc6262a5c343287aef64fb37667f8d3972daa70f96364041daa0b23149acbd20cbeff059f6428c6c2a317973bc1dd40a39e239350b0eb011e'
            'SKIP'
            'b4e4f8c49990721027e0c3ee30a04711b6f9ffa99a2f808fe830f39d5de785869dc4592dc70ccae14e028aeb5335395d413fba0e60ae9b2e31a9089339585022'
            '6460b8893b22069c64bc2dc44fcc0cf7161ebe2a82687b695e3284fce56da5f8c932c46521e5114d9226b8145059580cd4a9df233059f2f23310c042cdd4b07f'
            '637203080b55eda74a659f58c853a9a723a2dad5da70915b2b0e036c6145a649468ebec700cc83975d9cb5378b9dced8b3a3b26bdbcc75ddc774837355e75deb')
b2sums=('7e092c0ba2b094fb2041121b7b04b5a5914e85f05213cca4eafeb1826a8291bf733d1b7f8738d35b4a336a0d2d1c0d42582d21831873fae8c7884dbf5d592ee4'
        'SKIP'
        '1d1b416ae2860cbee54125afcfbf194db48f58bc50c946083f630287f9edda92340255713d77c66776ceffc27c1b960be164f9744bc1fd097e0cd8e575a7c079'
        'e8d80f12d379dc2d31b107c2bd7de0da28bb6da10cd85db4d85ecbe6d39d0cf875a1802b6184abd9fdbd90432783c72b11621594f00bca26b9ff050d5fa8a5b6'
        'e65ca7da22a20a40882cfc1fe4479643f9a38c90a4f2c3e71e6e5e3de1d6db212a0f17d600097619fe3cdb0a9b860422f8b0b9a9d45441518e51a7eb12a918bb')
validpgpkeys=(163EB50119225DB3DF8F49EA17ACBA8DFA970E17) # Richard Hughes <richard@hughsie.com>

prepare() {
  patch -d fwupd-${pkgver} -Np1 -i ../amd-gpu.patch
  patch -d fwupd-${pkgver} -Np1 -i ../source-version.patch
}

build() {
  local meson_options=(
    -D docs=disabled
    -D efi_binary=false
    -D launchd=disabled
    -D supported_build=enabled
    -D systemd_unit_user=fwupd
    -D hsi=disabled
    -D introspection=false
    -D plugin_redfish=false
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
