# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>

pkgname=xdg-dbus-proxy
pkgver=0.1.8
pkgrel=1.1 # Rebuild for Holo
pkgdesc="Filtering proxy for D-Bus connections"
url="https://github.com/flatpak/xdg-dbus-proxy"
arch=(x86_64)
license=(LGPL-2.1-or-later)
depends=(
  glib2
  glibc
  libgcc
)
makedepends=(
  docbook-xsl
  git
  meson
)
source=("git+$url#tag=$pkgver")
b2sums=('69b4ad2ae007072c117493bb5801086ae2a341096a0930a6176d614d8a09f17d23211795550a2221dc957772177889a0b8816ccc61a7454525be9b6337b18db2')

prepare() {
  cd $pkgname
}

build() {
  arch-meson $pkgname build
  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

package() {
  meson install -C build --destdir "$pkgdir"
}

# vim:set sw=2 sts=-1 et:
