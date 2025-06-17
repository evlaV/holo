# Maintainer (upstream): Bruno Pagani <archange@archlinux.org>
# Maintainer (upstream): Filipe Laíns (FFY00) <lains@archlinux.org>
# Maintainer (upstream): Frederik Schwan <freswa at archlinux dot org>
# Contributor: Mirco Tischler <mt-ml at gmx dot de>

# Holo: Variant of fwupd disabling some less common plugins/features to save on disk space/dependencies
pkgname=fwupd-minimal
pkgver=2.0.11
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
  fwupd.conf
  # Holo: Backports from next release
  legion-hidraw.patch
  asus-hidraw.patch
  immutable-enumeration.patch
)
sha512sums=('b45510721d2c59f0834c425affe1bddb9610503320d1a20e0fafe3f8452b50fc9e405de5642f5d52cfcdc918515443a4c92754979f34fafd9454a34cf9f721cd'
            '637203080b55eda74a659f58c853a9a723a2dad5da70915b2b0e036c6145a649468ebec700cc83975d9cb5378b9dced8b3a3b26bdbcc75ddc774837355e75deb'
            '8ebedc0437788337e8433cd67c9868fce1cdc01383a37092bfb83b6deac28ff5c79e0987390c3960b3a44b2acef2216b7489325741c4210a715f34d7bd9c8da1'
            '14aeea88e35b07d16ddc10f679a15d5f0b2f721e4eace65c80bcb21ef3b88a1e63ff0a3e832b7eab5a01aef87239cf3c8849096fb5d1705e09959eff1efaaa09'
            'b80570d36aa2d6744e558522e05182addfa6151d5d185f93604bb1fcaf52a8613e82e1b7756b7d334131f1e57c74089862129edb20b43fddd73b31142a3ab5a9'
            'ea039f479799c7b8d7ea4928352a3fcfa1a0847d21a590b6824bf25fdd640a8e3ee91752ac4a4ccb868e26de76cb32534d6c75f64146dcbfdace1f04390b0b66')
b2sums=('c6c934e9d8206eeebc2eed2726a42e20dc0f505124b9a6c3d9fd9de8c9ce4aeab8e7bbaee2272a2aaac406ab91a0a0ceefec08ea21111a1a7b7a2c24e3f08331'
        'e65ca7da22a20a40882cfc1fe4479643f9a38c90a4f2c3e71e6e5e3de1d6db212a0f17d600097619fe3cdb0a9b860422f8b0b9a9d45441518e51a7eb12a918bb'
        'd0154258fa07cfef0ae8c79f90cb6e79a962aa8293b5c107e5fc129f303ad72aa656d49321192c2341149b9d35f84e75144bda0c88aa33343e005c5a4bfbd1f7'
        '159809a89f18d9df53eccf47dd44aaf2408e6e5cd1d95505ac5e5a3d0ec1543d43caaf42a4c894e2154ed1b9b5d56524c8185a9fa11a1b79d9814a296c8c244c'
        '7a90b520b27d40935a823aaa67e35a1df9cc2e9fb3f8bb6878f63719a75e1e1b4ca3f5da8663e868e9a8e1b613f8e9d2650c8e94ade3e551ea1f4503cd737bf7'
        'f73061dbb1c9059ea7863d2c557eb4f44065fb1c2039368e64881c34bcc958c74933f7b2c2e6d7b596dabdb8c02872fa3659c4070696bf5eb10bd590168e5fa2')
validpgpkeys=(163EB50119225DB3DF8F49EA17ACBA8DFA970E17) # Richard Hughes <richard@hughsie.com>

prepare() {
  # Holo: Backports from next release
  patch -d fwupd -Np1 -i ../legion-hidraw.patch
  patch -d fwupd -Np1 -i ../asus-hidraw.patch
  patch -d fwupd -Np1 -i ../immutable-enumeration.patch
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
  # Don't allow enumeration of any device that might detach a kernel driver
  cp fwupd.conf "${pkgdir}"/etc/fwupd/fwupd.conf

}
