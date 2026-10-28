# Maintainer: Alberto Garcia <berto@igalia.com>

pkgname='holo-nix-offload'
pkgver=0.4
pkgrel=2
pkgdesc="Holo Nix Offload"
arch=('any')
license=('LGPL2.1')
# This package depends on 'holo-fs-offload' (filesystem bind mounts and targets
# for "offload", previously in steamos-customizations[-jupiter]).
depends=('holo-fs-offload')
source=("nix.mount")
sha256sums=('c678704b31e154199404cb1c8c0d61402faea236b44e979b34cef7abbdbfdd6e')

package() {
    mkdir -m 0755 -p "$pkgdir"/nix
    mkdir -m 0755 -p "$pkgdir"/usr/lib/systemd/system/holo-fs-offload.target.wants
    install -m 0644 -t "$pkgdir"/usr/lib/systemd/system nix.mount
    ln -s ../nix.mount "$pkgdir"/usr/lib/systemd/system/holo-fs-offload.target.wants
}
