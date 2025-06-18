# Maintainer: Fabian Bornschein <fabiscafe@archlinux.org>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Jan de Groot <jgc@archlinux.org>
# Contributor: William Rea <sillywilly@gmail.com>

pkgname=orca
pkgver=48.2
pkgrel=1.1
pkgdesc="Screen reader for individuals who are blind or visually impaired"
url="https://orca.gnome.org/"
arch=(any)
license=(LGPL-2.1-or-later)
depends=(
  at-spi2-core
  brltty
  glib2
  gobject-introspection-runtime
  gsettings-desktop-schemas
  gstreamer
  gst-plugins-base # playbin, audiotestsrc, basic decoders
  gst-plugins-good # pulsesink, more decoders
  gtk3
  hicolor-icon-theme
  liblouis
  libwnck3
  pango
  python
  python-cairo
  python-dbus
  python-gobject
  python-psutil
  python-setproctitle
  speech-dispatcher
  xorg-xkbcomp
  xorg-xmodmap
)
makedepends=(
  git
  itstool
  meson
  yelp-tools
)
groups=(gnome)
source=("git+https://gitlab.gnome.org/GNOME/orca.git?signed#tag=${pkgver/[a-z]/.&}"
  0001-Use-signals-to-perform-a-couple-of-actions.patch)
b2sums=('375ea7e15a7363e5f0265e3a8823af81c10692f4794a46011a368e3f5b4f549dc5ef755bb537c9b5f2c5a6471ae47e873f815b7f4675f434dc098eeeef8ab5de'
        'e1c15d7ec55da4d3604e5751cbaa33a9cabea134acb6260b357e5de9528964ff46796e67616a5e972d2debd83cac18830c9f333f733d32e3eb88b8c8307a37fd')
validpgpkeys=(
  DBDB67681333AA61BBCB97140A042BFD3DA3816C # Joanmarie Diggs <jdiggs@igalia.com>, older
  85D0D0B3FB02946101A46295E7A697B5609D4701 # Joanmarie Diggs <jdiggs@igalia.com>, newer
)

prepare() {
  cd orca
  patch -p1 < ../0001-Use-signals-to-perform-a-couple-of-actions.patch
}

build() {
  local meson_options=(
    -D spiel=false
  )

  arch-meson orca build "${meson_options[@]}"
  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

package() {
  meson install -C build --destdir "$pkgdir"
}

# vim:set sw=2 sts=-1 et:
