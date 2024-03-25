# Maintainer: Alberto Garcia <berto@igalia.com>

pkgname='holo-nfs-utils-tmpfiles'
pkgver=0.1
pkgrel=1
pkgdesc="systemd tmpfiles.d configuration for nfs-utils"
arch=('any')
license=('LGPL2.1')
depends=('nfs-utils')

package() {
    # https://marc.info/?l=linux-nfs&m=168924387828205&w=2
    install -m 0644 -D /dev/stdin "$pkgdir"/usr/lib/tmpfiles.d/holo-nfs-utils.conf <<-EOF
	# This is a systemd-tmpfiles configuration file
	# type path			mode	uid	gid	age	argument
	d /var/lib/nfs/statd/sm		0700	rpcuser	:root	-       -
	d /var/lib/nfs/statd/sm.bak	0700	rpcuser	:root	-	-
EOF
}
