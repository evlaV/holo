# Maintainer (upstream): Bruno Pagani <archange@archlinux.org>
# Maintainer (upstream): Filipe Laíns (FFY00) <lains@archlinux.org>
# Maintainer (upstream): Frederik Schwan <freswa at archlinux dot org>
# Contributor: Mirco Tischler <mt-ml at gmx dot de>

# Holo: Variant of fwupd disabling some less common plugins/features to save on disk space/dependencies
pkgname=fwupd-minimal
pkgver=2.0.9
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
  git
  bash-completion
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
  # Holo: Backports from next release
  json.patch
  onbattery.patch
)
sha512sums=('0a0e00f294b333d2695437ded1ebb4efc9c6c7b520d25097e54587657274ccecf20b0385257e50ff81865fc9639f8f8013f31fa9e23ffd8dc9f98eb4ad24501f'
            '637203080b55eda74a659f58c853a9a723a2dad5da70915b2b0e036c6145a649468ebec700cc83975d9cb5378b9dced8b3a3b26bdbcc75ddc774837355e75deb'
            '18a71f7cad6b188003341dff8bf42a2f2b90efddd49bbed82e824566a8b041f29454d79dc228823859937dadd58609a4ab2a93bcf7b8bcee906ea9116800a4eb'
            '22e78faf6eeaf81bf4d8469f56caf817dc0959407fd9996db4c3670bfd941532fee49d364889af58f04e06e3a978e36c76a667c9342d597e94e916acc197cba5')
b2sums=('00d0810260f4ac208d739dafde83f89d1aaf3d258d3c6cce61fea8608e98c481f4a89ef658bdea03feaa836a0109eb7ca41857d22ea6550c6ce74e8ed222d8bf'
        'e65ca7da22a20a40882cfc1fe4479643f9a38c90a4f2c3e71e6e5e3de1d6db212a0f17d600097619fe3cdb0a9b860422f8b0b9a9d45441518e51a7eb12a918bb'
        'c398d1d07441f8fbedc3f30557163edb37c8a70e6c96aaaff07bc097222d6d8dbcc327d8ef7ee591ea3bece45ad8e21903457f64a1032d1e788badfb054d4497'
        '87b8fce7bd32bb4050d98b1df28aa953eeddfa3af8091ac5de38752fa44a4dba2a34064ba7e0e4eebbd69cc69db9b380c16346530a033e297fcd17f72f2b5a49')
validpgpkeys=(163EB50119225DB3DF8F49EA17ACBA8DFA970E17) # Richard Hughes <richard@hughsie.com>

prepare() {
  # Holo: Backports from next release
  patch -d fwupd -Np1 -i ../json.patch
  patch -d fwupd -Np1 -i ../onbattery.patch
}

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
