# Maintainer (Holo): Alberto Garcia <berto@igalia.com>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Contributor: Jan Alexander Steffens (heftig) <jan.steffens@gmail.com>

# TODO: Keep at stable versions starting with 1.16.0
# https://gitlab.archlinux.org/archlinux/packaging/packages/flatpak/-/issues/1

pkgbase=flatpak
pkgname=(
  flatpak
  flatpak-docs
)
pkgver=1.15.6
pkgrel=2.1
epoch=1
pkgdesc="Linux application sandboxing and distribution framework (formerly xdg-app)"
url="https://flatpak.org"
arch=(x86_64)
license=(LGPL)
depends=(
  appstream
  bubblewrap
  curl
  dbus
  fuse3
  glib2
  json-glib
  libarchive
  libmalcontent
  libseccomp
  libxau
  ostree
  polkit
  python
  systemd
  wayland
  xdg-dbus-proxy
  xdg-utils
)
makedepends=(
  docbook-xsl
  git
  gobject-introspection
  gtk-doc
  meson
  python-pyparsing
  wayland-protocols
  xmlto
)
checkdepends=(
  socat
  valgrind
)
_commit=27b11b93c2a80a91c9461bc6c7f5e9a201406041  # tags/1.15.6^0
source=(
  "git+https://github.com/flatpak/flatpak#commit=$_commit"
  git+https://gitlab.gnome.org/GNOME/libglnx.git
  git+https://github.com/projectatomic/bubblewrap
  git+https://github.com/flatpak/xdg-dbus-proxy
  git+https://gitlab.gnome.org/alexl/variant-schema-compiler.git
  https://dl.flathub.org/repo/flathub.flatpakrepo
  flatpak-bindir.sh
  0001-HACK-Use-fusermount3.patch
  # Holo: Fix and test case for CVE-2024-32462 -- https://github.com/flatpak/flatpak/security/advisories/GHSA-phv6-cpc2-2fgj
  CVE-2024-32462-fix.patch
  CVE-2024-32462-test.patch
  # Holo: Show app name instead of developer name in 'flatpak list' -- https://github.com/flatpak/flatpak/issues/5700
  show-app-name-fix.patch
  show-app-name-test.patch
)
b2sums=('SKIP'
        'SKIP'
        'SKIP'
        'SKIP'
        'SKIP'
        'c094461a28dab284c1d32cf470f38118a6cbce27acce633b81945fb859daef9bdec1261490f344221b5cacf4437f53934cb51173f7ad2f1d2e05001139e75c54'
        '1c45caa65e2a1598f219977d5a81dcb8ea5d458880c43c40ba452b0c77cbbf41b36fa6911741f22c807d318e04e39e4fcc1455ed8d68faaba10162dae2570abc'
        '76ab2ae38c6043adfa7e521e222d9d1ab0dda70c8cca162218d04b3a1eba53e0c4b8b8df9cd005aa7dc38fc82927a9bba8bb5e235512ddaf90dc98716e242469'
        'c8ed25db884e2f92f3eb0d2b7089f3b81496e4334791662e6f2cb9926a0714aa6fff538be5ead6853ac548e5a5285aae9b9ec969806a148f41f8c2c227a7c119'
        '7540ade8bc582c41ad189fa2c6d3db64a4f84072ae184b54ac7045af70de808f2224ec3c2f81f4b536f275a2f166346e7bebeee0bfbcd20df39c9069c4d7d454'
        'a984e06a29459f8202e3d2a69c8045fc819640561a887e623d1e0f99ddc8ad44d84ef75f20c09f8a2db15b8d9d4ed732411d17217df7384a2a562a8ad835bb6f'
        'abdb1c39fd7828c40c6a1a73f76595a3d8fd6698e0895a4a49a94059f1a99295489d8c06033797479858e37eeceff719aa1fea30de8aabfe40aaa95298c2a76a')

pkgver() {
  cd flatpak
  git describe --tags | sed 's/[^-]*-g/r&/;s/-/+/g'
}

prepare() {
  cd flatpak

  # Support fuse3
  # https://bugs.archlinux.org/task/75623
  git apply -3 ../0001-HACK-Use-fusermount3.patch

  # Holo: Fix for CVE-2024-32462
  git apply -3 "$srcdir/CVE-2024-32462-fix.patch"
  git apply -3 "$srcdir/CVE-2024-32462-test.patch"

  # Holo: Fix for flatpak#5700
  git apply -3 "$srcdir/show-app-name-fix.patch"
  git apply -3 "$srcdir/show-app-name-test.patch"

  git submodule init
  git submodule set-url subprojects/libglnx "$srcdir/libglnx"
  git submodule set-url subprojects/bubblewrap "$srcdir/bubblewrap"
  git submodule set-url subprojects/dbus-proxy "$srcdir/xdg-dbus-proxy"
  git submodule set-url subprojects/variant-schema-compiler "$srcdir/variant-schema-compiler"
  git -c protocol.file.allow=always submodule update
}

build() {
  local meson_options=(
    -D dbus_config_dir=/usr/share/dbus-1/system.d
    -D selinux_module=disabled
    -D system_bubblewrap=bwrap
    -D system_dbus_proxy=xdg-dbus-proxy
  )

  arch-meson flatpak build "${meson_options[@]}"
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

package_flatpak() {
  depends+=(
    libostree-1.so
    xdg-desktop-portal
  )
  provides=(libflatpak.so)

  meson install -C build --destdir "$pkgdir"

  install -Dt "$pkgdir/etc/profile.d" -m644 flatpak-bindir.sh
  install -Dt "$pkgdir/etc/flatpak/remotes.d" flathub.flatpakrepo

  _pick docs "$pkgdir"/usr/share/{doc,gtk-doc}
}

package_flatpak-docs() {
  pkgdesc+=" (documentation)"
  depends=()
  mv docs/* "$pkgdir"
}

# vim:set sw=2 sts=-1 et:
