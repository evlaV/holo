# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Jan de Groot <jgc@archlinux.org>

pkgname=zenity-gtk3 # Holo: rename the package
pkgver=3.44.5
pkgrel=1.1
pkgdesc="Display graphical dialog boxes from shell scripts using GTK3"
url="https://gitlab.gnome.org/GNOME/zenity"
arch=(x86_64)
license=(LGPL)
depends=(
  gtk3
  libnotify
)
makedepends=(
  git
  meson
  yelp-tools
)
optdepends=('perl: gdialog wrapper')
source=("git+https://gitlab.gnome.org/GNOME/zenity.git#tag=$pkgver")
b2sums=('60f67b16ce2deefd81b07bd5de7d353f808868c123ed4c5feaa7865a9c19ccd1bdc87fb67133642c1181e734fe7dcdd6447e9ebe93d7ec111feafc1f6854e5a2')

# Holo: ensure that we can't install both zenity and zenity-gtk3 at the same time
provides=('zenity')
conflicts=('zenity')

pkgver() {
  cd zenity
  git describe --tags | sed 's/-real//;s/[^-]*-g/r&/;s/-/+/g'
}

prepare() {
  cd zenity
}

build() {
  local meson_options=(
    -D libnotify=true
  )

  arch-meson zenity build "${meson_options[@]}"
  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

package() {
  meson install -C build --destdir "$pkgdir"
}

# vim:set sw=2 sts=-1 et:
