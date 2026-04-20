# Maintainer: Alberto Garcia <berto@igalia.com>

pkgname='holo-fstab-repair'
pkgver=0.2
pkgrel=1
pkgdesc="Disable invalid sdcard entries in fstab"
arch=('any')
license=('LGPL2.1')
source=('holo-fstab-repair'
        'holo-fstab-repair.service')
sha256sums=('fa3de5917ee1e49fa06e792f094e5ba217336f878c7323b253c16aae911493fd'
            'd79a7951438f8495553188da6277c7284df7de9c5680796c43f3dd9099aec1db')

package() {
    mkdir -m 0755 -p "$pkgdir"/usr/lib/holo
    mkdir -m 0755 -p "$pkgdir"/usr/lib/systemd/system/local-fs.target.wants

    install -m 0755 -t "$pkgdir"/usr/lib/holo holo-fstab-repair
    install -m 0644 -t "$pkgdir"/usr/lib/systemd/system holo-fstab-repair.service

    ln -s ../holo-fstab-repair.service "$pkgdir"/usr/lib/systemd/system/local-fs.target.wants
}
sha256sums=('fa3de5917ee1e49fa06e792f094e5ba217336f878c7323b253c16aae911493fd'
            '7df9256b29e29cf7cc260daacd70c0fb652583b3d75d167c9b88f9a7ecb5319f')
