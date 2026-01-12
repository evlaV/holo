# SPDX-License-Identifier: LGPL-2.1-or-later
#
# Copyright (c) 2021 Valve.
# Maintainer: Guilherme G. Piccoli <gpiccoli@igalia.com>

pkgname=kdumpst
pkgver=1.2
pkgrel=1.1 # Cherry pick create-mount-folder.patch
pkgdesc="kdumpst, a tool for collecting pstore/kdump logs."
arch=('any')
url="https://gitlab.freedesktop.org/gpiccoli/kdumpst"
license=('LGPL2.1')
install=kdumpst.install

source=("https://gitlab.freedesktop.org/gpiccoli/$pkgname/-/archive/v$pkgver/$pkgname-v$pkgver.tar.gz"
        "create-mount-folder.patch")
sha256sums=('e623107293a737c7549e5723076f1094c16c98aeb63e2fa85e35a9d4062f7358'
            'e816ee4a73d08dd814e0b7875b450b5813d2df56db81ad3dceb000164b8edc5b')
depends=('dmidecode' 'kexec-tools' 'makedumpfile' 'zip' 'zstd')

prepare() {
	patch -p1 -d "$pkgname-v$pkgver" -i "${srcdir}/create-mount-folder.patch"
}

package() {
	cd $pkgname-v$pkgver
	make install DESTDIR="${pkgdir}"
}
