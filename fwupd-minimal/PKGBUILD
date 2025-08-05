# Maintainer:  Holo Team
# Contributor: Bruno Pagani <archange@archlinux.org>
# Contributor: Filipe Laíns (FFY00) <lains@archlinux.org>
# Contributor: Frederik Schwan <freswa at archlinux dot org>
# Contributor: Mirco Tischler <mt-ml at gmx dot de>

# Holo: Variant of fwupd disabling some less common plugins/features to save on disk space/dependencies
pkgname=fwupd-minimal
pkgver=2.0.13
pkgrel=1
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
  git
  gnu-efi-libs
  libdrm
  meson
  noto-fonts
  noto-fonts-cjk
  protobuf-c
  python-cairo
  python-dbus
  python-gobject
  python-jinja
  python-pillow
  vala
  valgrind
)
source=(
  "git+https://github.com/fwupd/fwupd.git#tag=${pkgver}?signed"
  fwupd.sysusers
  fwupd.conf
)
sha512sums=('bdd23d62b13fff3e7383a3f33b8ce926bb1f9b60f4aceffe0957c19f1b6db2daf14329cd0d78c5d495bbd5413ca5abafa1abac5ca7d51db3cf02cc614f4e9d0d'
            'f9a99c60786a2b98e0de439a9288af61b2c0716f8339a4c93e2df7108d2a7f9ef8128967dcaa1e12022ffa647945bf5eb3749e38cac83e00a28cbc5b015fbee9'
            '8ebedc0437788337e8433cd67c9868fce1cdc01383a37092bfb83b6deac28ff5c79e0987390c3960b3a44b2acef2216b7489325741c4210a715f34d7bd9c8da1')
b2sums=('bb672f69c1e22450e7beecfa0fb645c6501c0a42293d591518cfce86db82baece70d68344d22c8b148bc8fb7562b14f743d126d5cee79eb94177a3f93c4a8ca0'
        'c294c6dd324c0ad0d752affdc459d427d34f4bf865def099ac0e25db6b5dfbfcf645ca325e4e7732d1256e75c624ff27094d5c814726909c7e348128a9dd93f9'
        'd0154258fa07cfef0ae8c79f90cb6e79a962aa8293b5c107e5fc129f303ad72aa656d49321192c2341149b9d35f84e75144bda0c88aa33343e005c5a4bfbd1f7')
validpgpkeys=(163EB50119225DB3DF8F49EA17ACBA8DFA970E17) # Richard Hughes <richard@hughsie.com>

build() {
  # Holo: Disable some less-common plugins/features for size/dependencies
  local meson_options=(
    -D docs=disabled
    -D efi_binary=false
    -D supported_build=enabled
    -D systemd_unit_user=fwupd
    -D hsi=disabled
    -D introspection=disabled
    -D umockdev_tests=disabled
    -D plugin_flashrom=disabled
    -D passim=disabled
    -D plugin_modem_manager=disabled
    -D fish_completion=false
  )

  arch-meson fwupd build "${meson_options[@]}"
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
  # Don't allow enumeration of any device that might detach a kernel driver
  cp fwupd.conf "${pkgdir}"/etc/fwupd/fwupd.conf

}
