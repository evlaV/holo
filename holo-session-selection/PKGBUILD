# Maintainer: Martyn Welch <martyn.welch@collabora.com>

pkgname=holo-session-selection
pkgver=1.1
pkgrel=1
pkgdesc="Holo desktop session selection scripts and configuration files."
arch=(any)
optdepends=(
        'steamos-alias: for steamos-alias compatibility symlinks'
)
source=(
        holo-session-select
        holo.conf
)
sha256sums=('15496dc2ea3c2c4fe8a54a044f0e9b0c8ed93c8c29683831a72d2c0d6428110b'
            '03fb4a104e643ef8133f4d4c28fa45d311e3ad61bd71002490c0795f4246e24e')

package() {
  install -D -m755 "$srcdir"/holo-session-select "$pkgdir"/usr/bin/holo-session-select

  # Please keep this filename in sync with steamos-manager's session.rs
  install -D -m644 "$srcdir"/holo.conf "$pkgdir"/usr/lib/sddm/sddm.conf.d/holo.conf
}
