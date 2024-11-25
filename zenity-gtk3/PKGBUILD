# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Jan de Groot <jgc@archlinux.org>

pkgname=zenity-gtk3 # Holo: rename the package
pkgver=3.44.2
pkgrel=3
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
_commit=e9a591aa1d182e220013d9ab50dcc7607734d7b1  # tags/3.44.2-real^0
source=("git+https://gitlab.gnome.org/GNOME/zenity.git#commit=$_commit")
b2sums=('SKIP')

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
