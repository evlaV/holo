# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Contributor: Patrick Griffis <tingping@tingping.se>

pkgname=xdg-desktop-portal-gtk
pkgver=1.15.1
pkgrel=2.1 # Holo: Drop the gtk-portal.conf that Arch adds
pkgdesc="A backend implementation for xdg-desktop-portal using GTK"
url="https://github.com/flatpak/xdg-desktop-portal-gtk"
arch=(x86_64)
license=(LGPL-2.0-or-later)
depends=(
  fontconfig
  gcc-libs
  gdk-pixbuf2
  glib2
  glibc
  gsettings-desktop-schemas
  gtk3
  xdg-desktop-portal
)
makedepends=(
  git
  glib2-devel
  meson
  python
  python-packaging
)
optdepends=("evince: Print preview")
provides=(xdg-desktop-portal-impl)
source=("git+$url#tag=$pkgver")
b2sums=('417e43bb375c15bb351dd5434fdbc1665a22cc409d839408d99d29b7a2747f54c8440d9dc3087ac0246ff3e332d5a86f10025c48ec45f12894d26a0074111ec9')

prepare() {
  cd $pkgname
}

build() {
  local meson_options=(
    -D wallpaper=disabled
  )

  arch-meson $pkgname build "${meson_options[@]}"
  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

package() {
  meson install -C build --destdir "$pkgdir"

  # Holo: we do not need the gtk-portals.conf that Arch adds
}

# vim:set sw=2 sts=-1 et:
