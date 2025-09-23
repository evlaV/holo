# Maintainer: Fabian Bornschein <fabiscafe@archlinux.org>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>

pkgbase=libei
pkgname=(
  libei
  libei-docs
)
pkgver=1.4.1
pkgrel=3
pkgdesc="Library for Emulated Input"
url="https://libinput.pages.freedesktop.org/libei/"
arch=(x86_64)
license=(MIT)
depends=(
  gcc-libs
  glibc
  libevdev
  systemd-libs
)
makedepends=(
  doxygen
  git
  libxkbcommon
  meson
  python-attrs
  python-dbusmock
  python-jinja
  python-pytest
  python-structlog
  python-yaml
  systemd
)
checkdepends=(
  python-pytest-xdist
  valgrind
)
source=(
  "git+https://gitlab.freedesktop.org/libinput/libei.git?signed#tag=$pkgver"
  "nemequ-munit::git+https://github.com/nemequ/munit#commit=fbbdf1467eb0d04a6ee465def2e529e4c87f2118"
  "0001-Add-a-new-text-interface-for-sending-keysyms-and-utf.patch"
)
# Use sha256sums so we can verify the local patch while skipping VCS sources.
sha256sums=('640184b3981f394de2fe9b6e39ff14a570a2839e0e6d722d606631727a7f812e'
            '636ed5930324a4348877a291df36cea53a718cbf76aaf4be3d3b4182fdc9a9df'
            'd054b63e5d2e161d3d39fa2fe847a389c271d64ef4c3ead82c87a78e52b79693')
validpgpkeys=(
  3C2C43D9447D5938EF4551EBE23B7E70B467F0BF # Peter Hutterer <peter.hutterer@who-t.net>
)

prepare() {
  # Inject munit
  ln -s nemequ-munit munit

  cd libei

  # Apply local patch
  patch -Np1 -i "$srcdir/0001-Add-a-new-text-interface-for-sending-keysyms-and-utf.patch" # https://gitlab.freedesktop.org/libinput/libei/-/merge_requests/355
}

build() {
  local meson_options=(
    -D documentation=api
  )

  # Inject munit
  export MESON_PACKAGE_CACHE_DIR="$srcdir"

  arch-meson libei build "${meson_options[@]}"
  meson compile -C build
  meson compile -C build doxygen
}

# check() {
#   # protocol tests are flaky
#   meson test -C build --print-errorlogs --no-suite python
#   meson test -C build --print-errorlogs --suite python
#
#   # Extra valgrind tests
#   meson test -C build --print-errorlogs --setup valgrind
# }

package_libei() {
  provides=(lib{ei,eis,oeffis}.so)

  meson install -C build --destdir "$pkgdir" --skip-subprojects

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 libei/COPYING
}

package_libei-docs() {
  pkgdesc+=" (API documentation)"
  depends=()

  mkdir -p "$pkgdir/usr/share/doc/$pkgname"
  cp -a build/doc/html "$pkgdir/usr/share/doc/$pkgname/api"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 libei/COPYING
}

# vim:set sw=2 sts=-1 et:
