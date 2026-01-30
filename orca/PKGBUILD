# Maintainer: Fabian Bornschein <fabiscafe@archlinux.org>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Jan de Groot <jgc@archlinux.org>
# Contributor: William Rea <sillywilly@gmail.com>

pkgname=orca
pkgver=48.9
pkgrel=1.0
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
  0001-Use-signals-to-perform-a-couple-of-actions.patch
  0002-Orca-Don-t-restart-speech-when-reloading-settings-vi.patch
  0003-Add-support-for-automatic-language-switching-in-docu.patch
)
b2sums=('317befc8789a8cd8577d261ec4e7ea3389bf36b59180fcfa0b8323bcc493376cc706222b313a9b7c77b56910712aa8fd52d2e3c4e2fbdb33b51ae5cd65ef1def'
        'e1c15d7ec55da4d3604e5751cbaa33a9cabea134acb6260b357e5de9528964ff46796e67616a5e972d2debd83cac18830c9f333f733d32e3eb88b8c8307a37fd'
        'cd92774d3b43589a54322e431564cc693dbbfeab1ca4fc8fb733473fe5002b07bc2b6329e515d71938919f37fe51272a37b802b9a07c7c5c07b7375f3219bc8b'
        '2fdc9171519ad584b0059ece7d339033b3453bd8304b6941d9d22e4df34948c5749b84676f55cc82026951f410915d4042300b0c91d6820fd963a3e6ed704b8a')

validpgpkeys=(
  DBDB67681333AA61BBCB97140A042BFD3DA3816C # Joanmarie Diggs <jdiggs@igalia.com>, older
  85D0D0B3FB02946101A46295E7A697B5609D4701 # Joanmarie Diggs <jdiggs@igalia.com>, newer
)

prepare() {
  cd orca
  patch -p1 < ../0001-Use-signals-to-perform-a-couple-of-actions.patch
  patch -p1 < ../0002-Orca-Don-t-restart-speech-when-reloading-settings-vi.patch
  patch -p1 < ../0003-Add-support-for-automatic-language-switching-in-docu.patch
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
