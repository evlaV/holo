# Maintainer: Vlad Zahorodnii <vladzzag@gmail.com>
pkgname=drm_janitor
pkgver=0.0.4
pkgrel=2
pkgdesc="A helper that resets the DRM state to reasonable defaults"
arch=(x86_64)
url="https://github.com/zzag/drm_janitor"
license=('MIT')
depends=(libdrm)
makedepends=(meson)
source=("$pkgname-$pkgver.tar.gz"::"https://github.com/zzag/$pkgname/archive/$pkgver.tar.gz"
        drm_janitor.conf)
sha256sums=('712702f131a246d369e766563548bf46355aecaf4a51517fbad01c7af4df0516'
            'SKIP')

build() {
    arch-meson build "${pkgname}-${pkgver}"
    meson compile -C build
}

package() {
    meson install -C build --destdir="${pkgdir}"
    install -Dm644 "${pkgname}-${pkgver}/LICENSE" "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
    install -Dm644 drm_janitor.conf "${pkgdir}/usr/lib/systemd/system/sddm.service.d/drm_janitor.conf"
}
