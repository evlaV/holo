# Maintainer (Holo): Manuel A. Fernandez Montecelo <mafm@igalia.com>

pkgname=holo-earlyoom
pkgver=1.0
pkgrel=1
pkgdesc="Depend on 'earlyoom' and change config without modifying /etc/default/earlyoom"
arch=(any)
license=(MIT)
depends=(
  "earlyoom>=1.7-1"
)
source=(holo-earlyoom.systemd.conf)
b2sums=(SKIP)

package() {
  local dest_systemd_unit_path="${pkgdir}/usr/lib/systemd/system"

  # override earlyoom's package config
  install -Dm644 holo-earlyoom.systemd.conf "${dest_systemd_unit_path}/earlyoom.service.d/holo-earlyoom.conf"

  # enable the earlyoom systemd service
  mkdir -pv "${dest_systemd_unit_path}/multi-user.target.wants"
  ln -sv "../earlyoom.service" "${dest_systemd_unit_path}/multi-user.target.wants/earlyoom.service"
}

# -*- mode: sh; indent-tabs-mode: nil; sh-basic-offset: 2; -*-
# vim: ts=2 sw=2 et:
