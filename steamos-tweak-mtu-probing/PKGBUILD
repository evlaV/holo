# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=steamos-tweak-mtu-probing
pkgver=1
pkgrel=1
pkgdesc='SteamOS tweak - Enable MTU probing'
arch=('any')
url='http://repo.steampowered.com'
license=('LGPLv2+')
depends=('systemd')
source=("20-mtu-probing.conf")
sha256sums=('4097ac41f0c519a5dc3552453a2bbd8487e3a9d6bee8136d4bbfdf8012e7e5a8')

package() {
	install -Dm644 $srcdir/20-mtu-probing.conf $pkgdir/usr/lib/sysctl.d/20-mtu-probing.conf
}

