# Maintainer: Alberto Garcia <berto@igalia.com>

pkgname='holo-nix-offload'
pkgver=0.4
pkgrel=1
pkgdesc="Holo Nix Offload"
arch=('any')
license=('LGPL2.1')
depends=('steamos-customizations')
source=("nix.mount")
sha256sums=('af1de9d03eb53c5fe9a3b697bdfe95655fb263834c26a89e3ced961956945c1d')

package() {
    mkdir -m 0755 -p "$pkgdir"/nix
    mkdir -m 0755 -p "$pkgdir"/usr/lib/systemd/system/holo-offload.target.wants
    install -m 0644 -t "$pkgdir"/usr/lib/systemd/system nix.mount
    ln -s ../nix.mount "$pkgdir"/usr/lib/systemd/system/holo-offload.target.wants
}
