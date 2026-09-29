# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=holo-config-mtu-probing
pkgver=1.0
pkgrel=1
pkgdesc='Holo customizations - configuration to enable MTU probing'
arch=('any')
url='http://repo.steampowered.com'
license=('LGPLv2+')
source=("20-mtu-probing.conf")
sha256sums=('e299aa02b326e6c89cd3bf594bb0b9c54f16dc7acbe56446136a2e68be7c4c26')

package() {
	install -D -m 0644 $srcdir/20-mtu-probing.conf $pkgdir/usr/lib/sysctl.d/20-mtu-probing.conf
}
