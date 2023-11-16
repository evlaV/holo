# Maintainer: Alberto Garcia <berto@igalia.com>

pkgname='holo-flatpak-tmpfiles'
pkgver=0.1
pkgrel=1
pkgdesc="systemd tmpfiles.d configuration for Flatpak"
arch=('any')
license=('LGPL2.1')

package() {
    # https://github.com/flatpak/flatpak/issues/1119
    install -m 0644 -D /dev/stdin "$pkgdir"/usr/lib/tmpfiles.d/holo-flatpak.conf <<-EOF
	R! /var/tmp/flatpak-cache-*
EOF
}
