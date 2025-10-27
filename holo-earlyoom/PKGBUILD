# Maintainer (Holo): Manuel A. Fernandez Montecelo <mafm@igalia.com>

pkgname=holo-earlyoom
pkgver=1.1
pkgrel=1
pkgdesc="Depend on 'earlyoom' and change config without modifying /etc/default/earlyoom"
arch=(any)
license=(MIT)
depends=(
  "earlyoom>=1.8.2-1"
)
source=(holo-earlyoom-logger.sh
	holo-earlyoom-prehook.c
	holo-earlyoom.systemd.conf
	holo-earlyoom.tmpfiles.d)
b2sums=(SKIP
	SKIP
	SKIP
	SKIP)

build() {
  gcc -Wall -O1 -o holo-earlyoom-prehook holo-earlyoom-prehook.c
  strip holo-earlyoom-prehook
}

package() {
  local dest_systemd_unit_path="${pkgdir}/usr/lib/systemd/system"

  # override earlyoom's package config
  install -Dm644 holo-earlyoom.systemd.conf "${dest_systemd_unit_path}/earlyoom.service.d/holo-earlyoom.conf"

  # enable the earlyoom systemd service
  mkdir -pv "${dest_systemd_unit_path}/multi-user.target.wants"
  ln -sv "../earlyoom.service" "${dest_systemd_unit_path}/multi-user.target.wants/earlyoom.service"

  install -Dm0755 holo-earlyoom-logger.sh "${pkgdir}/usr/lib/holo-earlyoom/holo-earlyoom-logger.sh"

  install -Dm0644 holo-earlyoom.tmpfiles.d "${pkgdir}/usr/lib/tmpfiles.d/holo-earlyoom.conf"
  install -Dm0755 holo-earlyoom-prehook "${pkgdir}/usr/lib/holo-earlyoom/steamos-earlyoom-prehook"
}

# -*- mode: sh; indent-tabs-mode: nil; sh-basic-offset: 2; -*-
# vim: ts=2 sw=2 et:
