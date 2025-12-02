# Maintainer: Campbell Jones <serebit at archlinux dot org>
# Contributor: Felix Yan <felixonmars@archlinux.org>

# Holo: Apply two downstream patches to adddress https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1584
# The revert needs further investigation to decide if it is a genuine upstream regression
# The second patch is a bugfix, we'll push it upstream and update this PKGBUILD to referece it

pkgbase=ibus
pkgname=(ibus libibus)
pkgver=1.5.32
pkgrel=2.2
pkgdesc="Intelligent input bus for Linux/Unix"
arch=('x86_64')
url="https://github.com/ibus/ibus/wiki"
license=('LGPL-2.1-or-later')
depends=(
    'at-spi2-core'
    'cairo'
    'dconf'
    'gdk-pixbuf2'
    'glib2'
    'graphene'
    'gtk3'
    'gtk4'
    'hicolor-icon-theme'
    'libdbusmenu-glib'
    'libdbusmenu-gtk3'
    'libnotify'
    'libx11'
    'libxkbcommon'
    'libxfixes'
    'libxi'
    'pango'
    'python'
    'python-gobject'
    'wayland'
)
makedepends=(
    'glib2-devel'
    'gobject-introspection'
    'gtk-doc'
    'qt5-base'
    'unicode-character-database'
    'unicode-cldr'
    'unicode-emoji'
    'vala'
    'wayland-protocols'
)
options=('!emptydirs')
source=("https://github.com/$pkgname/$pkgname/releases/download/$pkgver/${pkgname}-${pkgver}.tar.gz"
        # Holo: patches part of https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1584
        # One should go upstream and the other is still TBD
        "0001-Partially-revert-Fix-tests-cases-to-be-run-in-Waylan.patch"
        # Needed to fix korean input on SteamOS which disables pre-edit strings
        # Submitted as https://github.com/ibus/ibus/pull/2830, hopefully can be dropped
        "0002-client-wayland-Connect-delete-surrounding-text.patch"
        )
b2sums=('6f69a92993e378c25473e51cdffd66b9180b163c2206a8256bb7c181fc2e54535d0254c62ac8fd8dd162f7d35aa32d7ae5982f7c786310b1327ba1f3ccd932e6'
        'e04b0e5e5bb7026216af35c2a0894c08c8b3bdfb67a4c5072701b0f00e704d32a95a89db235907f5a13da5c721ee1ecc6e8b53331f974aca72a45e4c9335252c'
        '83e2db1cea4b4e5a436e05894b2cd7202e4aa79d4ac90836f0ccc3ee997e10cc4eeaf04e4b21db6b5c050afdd78b68ea95513a4259090eb555f6920725a7101e')

prepare() {
  cd ${pkgname}-${pkgver}

  local src
  for src in "${source[@]}"; do
    src="${src%%::*}"
    src="${src##*/}"
    [[ $src = *.patch ]] || continue
    echo "Applying patch $src..."
    patch -Np1 < "../$src"
  done
}

build() {
    cd ${pkgname}-${pkgver}
    ./configure \
        --prefix=/usr \
        --libexecdir=/usr/lib/ibus \
        --sysconfdir=/etc \
        --enable-dconf \
        --enable-wayland \
        --enable-gtk-doc \
        --disable-gtk2 \
        --enable-gtk4 \
        --disable-memconf \
        --enable-ui \
        --disable-python2 \
        --with-python=python3 \
        --with-ucd-dir=/usr/share/unicode/
    sed -i 's/ -shared / -Wl,-O1,--as-needed\0/g' libtool
    make
}

package_ibus() {
    depends+=("libibus=$pkgver")

    cd ibus-${pkgver}
    make DESTDIR="$pkgdir" install
    make -C src DESTDIR="$pkgdir" uninstall
    make -C src DESTDIR="$pkgdir" install-dictDATA install-unicodeDATA
    make -C bindings DESTDIR="$pkgdir" uninstall
    make DESTDIR="$pkgdir" uninstall-pkgconfigDATA
}

package_libibus() {
    pkgdesc="IBus support library"
    depends=(libg{lib,object,io}-2.0.so)
    optdepends=('python-gobject: for Python integration')
    provides=('libibus-1.0.so')

    cd ibus-${pkgver}
    make -C src DESTDIR="$pkgdir" install
    make -C src DESTDIR="$pkgdir" uninstall-dictDATA uninstall-unicodeDATA
    make -C bindings DESTDIR="$pkgdir" install
    make DESTDIR="$pkgdir" install-pkgconfigDATA
}
