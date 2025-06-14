# Maintainer: Fabian Bornschein <fabiscafe@archlinux.org>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Jan de Groot <jgc@archlinux.org>
# Contributor: William Rea <sillywilly@gmail.com>
# Holo: backport of upstream, no changes (except version bump)

pkgname=orca
_srctag=47.5
pkgver=${_srctag##v}
pkgrel=1
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
source=("git+https://gitlab.gnome.org/GNOME/orca.git#tag=${_srctag}")
b2sums=('24bf49a6d2fa6a350f6175713a85ce189510eedbd9c2f3c47ab20c5799a9db32243a00e82ee6d209b6f2baf88de6d1b0d6b96a4800e5dc5daa2c57a40b0787ec')
validpgpkeys=(
  DBDB67681333AA61BBCB97140A042BFD3DA3816C # Joanmarie Diggs <jdiggs@igalia.com>, older
  85D0D0B3FB02946101A46295E7A697B5609D4701 # Joanmarie Diggs <jdiggs@igalia.com>, newer
)

prepare() {
  cd orca
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
