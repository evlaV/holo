# Maintainer: Campbell Jones <serebit at archlinux dot org>
# Contributor: Felix Yan <felixonmars@archlinux.org>

# Holo: Apply two downstream patches to adddress https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1584
# The revert needs further investigation to decide if it is a genuine upstream regression
# The second patch is a bugfix, we'll push it upstream and update this PKGBUILD to referece it

pkgbase=ibus
pkgname=(ibus libibus)
pkgver=1.5.31
pkgrel=2.1
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
)
options=('!emptydirs')
source=("https://github.com/$pkgname/$pkgname/releases/download/$pkgver/${pkgname}-${pkgver}.tar.gz"
        # Holo: patches part of https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1584
        # One should go upstream and the other is still TBD
        "0001-Partially-revert-Fix-tests-cases-to-be-run-in-Waylan.patch"
        "0001-bus-inputcontext-Use-the-correct-string-marshaller.patch")
b2sums=('2fa895369f5326339b50da34777e2f34124000cff40a4bc871bb0c1cdac4a22cc327240b8338bc6c4fc85267a83ccc0bd5963abcf4763a373b1227bdb5753b76'
        'e04b0e5e5bb7026216af35c2a0894c08c8b3bdfb67a4c5072701b0f00e704d32a95a89db235907f5a13da5c721ee1ecc6e8b53331f974aca72a45e4c9335252c'
        'be37c7b79a18745dad3b9565ff789cf264378bb9d3a82905a33538a5c30021dbddd3661280220d91ab0e514fc47b7182d2556e1c7a8fb009437297a50ae1462b')

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
