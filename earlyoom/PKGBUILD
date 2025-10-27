# Maintainer: Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
# Maintainer: Maxim Baz <$pkgname at maximbaz dot com>
# Maintainer (Holo): Manuel A. Fernandez Montecelo <mafm@igalia.com>


####################################################
# Can be dropped when ArchLinux repos have v1.9.0+ #
####################################################


pkgname=earlyoom
pkgver=1.8.2
pkgrel=1.2
_commit=cbf0bb2e5d99db196003098d24439f632c1a067b
pkgdesc="Early OOM Daemon for Linux"
arch=('x86_64')
url="https://github.com/rfjakob/earlyoom"
license=('MIT')
depends=('glibc')
makedepends=('pandoc')
optdepends=('systembus-notify: desktop notifications')
backup=("etc/default/earlyoom")
source=("git+https://github.com/rfjakob/${pkgname}.git#commit=${_commit}")
sha256sums=('b0247f8eeae69a5d9a33f2b1351bd1c45e411d4f533a1cee5d53753d5ce805ca')

prepare() {
    #cd "$pkgname-$pkgver"
    cd "$pkgname"
    sed "/systemctl|chcon/d" -ri Makefile
    sed '/^DynamicUser=/a SupplementaryGroups=proc' -i earlyoom.service.in
    sed 's;^EARLYOOM_ARGS="(.*)";EARLYOOM_ARGS="\1 -n --avoid '\''(^|/)(init|systemd|Xorg|sshd)$'\''";' -ri earlyoom.default
}

build() {
    #cd "$pkgname-$pkgver"
    cd "$pkgname"
    make PREFIX=/usr SYSTEMDUNITDIR=/usr/lib/systemd/system VERSION=$pkgver earlyoom
}

package() {
    #cd "$pkgname-$pkgver"
    cd "$pkgname"
    make install DESTDIR="$pkgdir" PREFIX=/usr SYSTEMDUNITDIR=/usr/lib/systemd/system
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
