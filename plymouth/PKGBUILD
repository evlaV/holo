# Maintainer: Taijian <taijian@posteo.de>
# Contributor: Sebastian Lau <lauseb644@gmail.com>
# Contributor Damian01w <damian01w@gmail.com>
# Contributor: Padfoot <padfoot@exemail.com.au>
#

pkgname=plymouth
pkgver=22.02.122
# Scaling fixes
# - explicit workaround DeviceScale=1, since our kernel is missing rotation
# Disable on start, allow deactivate to fail
pkgrel=1.5
pkgdesc="A graphical boot splash screen with kernel mode-setting support"
url="https://www.freedesktop.org/wiki/Software/Plymouth/"
arch=('i686' 'x86_64')
license=('GPL')

depends=('libdrm' 'pango' 'systemd')
makedepends=('docbook-xsl')
optdepends=('ttf-dejavu: For true type font support'
        'xf86-video-fbdev: Support special graphic cards on early startup'
        'cantarell-fonts: True Type support for BGRT theme')
backup=('etc/plymouth/plymouthd.conf')

options=('!libtool' '!emptydirs')

source=("https://gitlab.freedesktop.org/${pkgname}/${pkgname}/-/archive/${pkgver}/${pkgname}-${pkgver}.tar.gz"
      'arch-logo.png'
       'plymouth.encrypt_hook'
       'plymouth.encrypt_install'
       'lxdm-plymouth.service'
       'lightdm-plymouth.service'
       'sddm-plymouth.service'
       'plymouth-deactivate.service' # needed for sddm # SteamOS: allow silence failure
       'plymouth.initcpio_hook'
       'plymouth.initcpio_install'
       'sd-plymouth.initcpio_install'
       'plymouth-quit.service.in.patch'
       'plymouth-systemd-units.patch'          # SteamOS: disable on startup
       'plymouthd.conf.patch'
       '0001-defaults-set-DeviceScale-1.patch' # SteamOS: explicit DeviceScale=1
       '0001-Revert-drm-Honour-screen-rotation-when-detecting-HiD.patch' # SteamOS: temporary revert the orientation detection
)

sha256sums=('8921cd61a9f32f5f8903ceffb9ab0defaef8326253e1549ef85587c19b7f2ab6'
            'de4369ad5a5511b684305e3a882c2c56204696514ea8ccdb556dd656eca062e7'
            '748e0cfa0e10ab781bc202fceeed46e765ed788784f1b85945187b0f29eafad7'
            '373ec20fe4c47e693a0c45cc06dd906e35dd1d70a85546bd1d571391de11763a'
            '06b31999cf60f49e536c7a12bc1c4f75f2671feb848bf5ccb91a963147e2680d'
            '86d0230d9393c9d83eb7bb430e6b0fb5e3f32e78fcd30f3ecd4e6f3c30b18f71'
            'c39f526f7e99173bc8f012900f53257537a25e2d8c19e23df630f1fe9a7627ba'
            'b16f35f130f7b1ea3b71d9950467fe516ceacb5973506daa61bfd48ab9ce83e6'
            '2a80e2cad8de428358647677afa166219589d3338c5f94838146c804a29e2769'
            'd2201253d9f4a1f7e556e60a04401237273a4577e157a8c4471d5c81bff88ccd'
            'd254f3d01631024ed4563d39fcaa631b0ace097faf7ed05de382859ccfa48a08'
            'dec28b86ddea93704f8479d33e08f81cd7ff4ccaad57e9053c23bd046db2278a'
            '5b51b1c4f8ab74fd25a1a2a48e4d2a4e752b816531581c255455d08dca85ab4c'
            '71d34351b4313da01e1ceeb082d9776599974ce143c87e93f0a465f342a74fd2'
            '5be4e85480db4fbd0acf81855500ea3275cd06eaabd5553e39ff694b85dab9bc'
            'ebf03812c3c338287349c5e8471adf9716a19b972e1c119410a797c6f823ac92')

prepare() {
	cd "$srcdir"/${pkgname}-${pkgver}

	sed -i 's/dracut -f/mkinitcpio -P/' scripts/plymouth-update-initrd

	patch -p1 -i $srcdir/plymouth-quit.service.in.patch
	patch -p1 -i $srcdir/plymouthd.conf.patch
	patch -p1 -i $srcdir/0001-defaults-set-DeviceScale-1.patch
	patch -p1 -i $srcdir/plymouth-systemd-units.patch
	patch -p1 -i $srcdir/0001-Revert-drm-Honour-screen-rotation-when-detecting-HiD.patch
}

build() {
	cd "$srcdir"/${pkgname}-${pkgver}

	LDFLAGS="$LDFLAGS -ludev" ./autogen.sh \
		--prefix=/usr \
		--exec-prefix=/usr \
		--sysconfdir=/etc \
		--localstatedir=/var \
		--libdir=/usr/lib \
		--libexecdir=/usr/lib \
		--sbindir=/usr/bin \
		--enable-systemd-integration \
		--enable-drm \
		--enable-tracing \
		--enable-pango \
		--enable-gtk=no \
		--with-release-file=/etc/os-release \
		--with-logo=/usr/share/plymouth/arch-logo.png \
		--with-background-color=0x000000 \
		--with-background-start-color-stop=0x000000 \
		--with-background-end-color-stop=0x4D4D4D \
		--without-rhgb-compat-link \
		--without-system-root-install \
		--with-runtimedir=/run

	make
}

package() {
	cd "$srcdir"/${pkgname}-${pkgver}

	make DESTDIR="$pkgdir" install

	install -Dm644 "$srcdir/arch-logo.png" "$pkgdir/usr/share/plymouth/arch-logo.png"

	install -Dm644 "$srcdir/plymouth.encrypt_hook" "$pkgdir/usr/lib/initcpio/hooks/plymouth-encrypt"
	install -Dm644 "$srcdir/plymouth.encrypt_install" "$pkgdir/usr/lib/initcpio/install/plymouth-encrypt"
	install -Dm644 "$srcdir/plymouth.initcpio_hook" "$pkgdir/usr/lib/initcpio/hooks/plymouth"
	install -Dm644 "$srcdir/plymouth.initcpio_install" "$pkgdir/usr/lib/initcpio/install/plymouth"
	install -Dm644 "$srcdir/sd-plymouth.initcpio_install" "$pkgdir/usr/lib/initcpio/install/sd-plymouth"

	for i in {sddm,lxdm,lightdm}-plymouth.service; do
		install -Dm644 "$srcdir/$i" "$pkgdir/usr/lib/systemd/system/$i"
	done

	install -Dm644 "$srcdir/plymouth-deactivate.service" 	"$pkgdir/usr/lib/systemd/system/plymouth-deactivate.service"
	install -Dm644 "$pkgdir/usr/share/plymouth/plymouthd.defaults" "$pkgdir/etc/plymouth/plymouthd.conf"
}
