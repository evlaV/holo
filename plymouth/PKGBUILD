# Maintainer: Balló György <ballogyor+arch at gmail dot com>
# Contributor: Taijian <taijian@posteo.de>
# Contributor: Sebastian Lau <lauseb644@gmail.com>
# Contributor: Damian01w <damian01w@gmail.com>
# Contributor: Padfoot <padfoot@exemail.com.au>

pkgname=plymouth
pkgver=22.02.122
pkgrel=7.2
pkgdesc='Graphical boot splash screen'
arch=('x86_64')
url='https://www.freedesktop.org/wiki/Software/Plymouth/'
license=('GPL2')
depends=('bash' 'cairo' 'cantarell-fonts' 'filesystem' 'glib2' 'glibc' 'libdrm'
         'libpng' 'pango' 'systemd-libs'
         'fontconfig' 'freetype2'           # SteamOS: x11 backend
         'libevdev' 'libx11' 'libxkbcommon' # SteamOS: x11 backend
         'xkeyboard-config'                 # SteamOS: x11 backend
         'holo-plymouth-themes') # SteamOS: firmware update splash
makedepends=('gtk3' 'docbook-xsl')
optdepends=('ttf-dejavu: For true type font support'
            'xf86-video-fbdev: Support special graphic cards on early startup'
            'cantarell-fonts: True Type support for BGRT theme'
            'gtk3: x11 renderer')
backup=('etc/plymouth/plymouthd.conf')

# The drm scrape and bgrt patch series' (0012-0016)come from:
# https://gitlab.freedesktop.org/bbeckett/plymouth/-/tree/22.02.122+closefb+drm-scrape
# They have not (as of 2025-10-24) been upstreamed
# We use BGRT in our firmware update splash (holo-plymouth-themes) but not DRM scrape
#
# 0010,0011 are generic "do not clear the drm buffer on exit" support
# We also use that in holo-plymouth-themes.
source=("https://www.freedesktop.org/software/$pkgname/releases/$pkgname-$pkgver.tar.xz"
        "plymouth-shutdown.patch::https://gitlab.freedesktop.org/plymouth/plymouth/-/commit/2f12aa4c5d27d1ee5a46f412559073f016d236ae.patch"
        'plymouth.initcpio_hook'
        'plymouth.initcpio_install'
        'plymouth-deactivate.service' # needed for sddm # SteamOS: allow silent failure
        'plymouth-quit.service.in.patch'        # SteamOS: plymouth timing during startup (masked by next patch)
        'plymouth-systemd-units.patch'          # SteamOS: disable on startup
        'plymouthd.conf.patch'                  # SteamOS: historical, not sure this matters anymore.
        '0001-defaults-set-DeviceScale-1.patch' # SteamOS: explicit DeviceScale=1
        '0001-Revert-drm-Honour-screen-rotation-when-detecting-HiD.patch' # SteamOS: temporary revert the orientation detection
        '0010-Close-the-FB-if-possible-to-keep-the-image-on-the-sc.patch' # SteamOS: preserve drm buffer/display on handover
        '0011-retain-splash-when-quitting.patch'                          # SteamOS: Ibid
        '0012-script-add-bgrt-special-Image.patch'                        # SteamOS: Support reading of BIOS BGRT image
        '0013-ply-pixel-buffer-add-ability-to-read-raw-pixel-data.patch'  # SteamOS: Ibid
        '0014-ply-renderer-add-interface-to-allow-head-scraping.patch'    # SteamOS: Ibid
        '0015-drm-implement-drm-head-scraping.patch'                      # SteamOS: Ibid
        '0016-script-add-scrape_display-special-image.patch'              # SteamOS: Ibid
        '0020-Suppress-unimportant-unused-result-warnings-in-ply_b.patch' # SteamOS: plymouth build flags & arch defaults clash
)

sha256sums=('100551442221033ce868c447ad6c74d831d209c18ae232b98ae0207e34eadaeb'
            'cd35f5d5c6ceff353375500fbe4ea2293b5bfb13c3a02dab2c82c1a85b808288'
            '6b7d54b69f37a6c87fbf072eed03b82c52b1f6e2b88d1e2fc9bde03e86ea05c7'
            '91125025f33f3d74957cec7b01e7930073067768b36455728c5e761e1aed6ee3'
            '7a2a83b98a3b79145ac4f41d6bff9829ca601e8ff3b35d78bdee5e001364d320'
            'e7744dbc89e0facf72a8202b2dc4f310bcc84d5f77bc4fa077984b865f9f860a'
            '5b51b1c4f8ab74fd25a1a2a48e4d2a4e752b816531581c255455d08dca85ab4c'
            '71d34351b4313da01e1ceeb082d9776599974ce143c87e93f0a465f342a74fd2'
            '5be4e85480db4fbd0acf81855500ea3275cd06eaabd5553e39ff694b85dab9bc'
            'ebf03812c3c338287349c5e8471adf9716a19b972e1c119410a797c6f823ac92'
            '5716036462d91f8e50160332c15b6d36d02932162a9add5d2c5cb526ca559695'
            '36c485db1f671378dbca431ef2bd3c4980bcaceeb7c034a7edc9781f28fdc6b3'
            '26c73c8dd23119ba45d410041249e1346c7135d89ca545dd1f107037038bb4c1'
            '3044397d078988687575f638e7aaa91f7753a8305fcd9093c5c648f01348e30a'
            'd823030159231db1c9992359b62fe9db42657953c3294f07562169c2226766e0'
            'f5fda6cef4e054bac8e880d8c7f64311d3f747ae063d0399c14335434194bd91'
            '3409d1efc64cd9e20a9941de6a7cbde3623c193f9137b507118515c40739d2b3'
            'ab1cca2bb02897d8915e936b5e8f449d55b7bf4217128ff36e23ea2296c984de')

prepare() {
  cd "$pkgname-$pkgver"

  ###########################################################
  # SteamOS: Apply all patches from sources automatically
  local patch=
  for patch in "${source[@]}";
  do
    patch=${patch%%::*}
    case $patch in
      *.patch)
        echo "PATCH $srcdir/$patch from $(pwd)"
        patch -p1 -i $srcdir/$patch
        ;;
    esac
  done
  ###########################################################

  # Use mkinitcpio to update initrd
  sed -i 's/dracut -f/mkinitcpio -P/' scripts/plymouth-update-initrd

  # Change default theme (changed to 'holo') in SteamOS
  sed -i 's/^Theme=spinner$/Theme=holo/' src/plymouthd.defaults
}

build() {
  cd "$pkgname-$pkgver"
  ############################################################
  # SteamOS - Arch linux default fortify clashes with plymouth
  # so we strip out the clashing settings here - otherwise we
  # get a warning every single time we call gcc
  local -a FIXED_CFLAGS=()
  local f=

  for f in $CFLAGS
  do
    case $f in
      *_FORTIFY_SOURCE*|--std=*) true ;;
      *) FIXED_CFLAGS+=("$f") ;;
    esac
  done
  CFLAGS="${FIXED_CFLAGS[*]}"
  ############################################################

  # SteamOS: we can have a different autoconf version to what
  # upstream shipped, so call autoreconf just in case:
  autoreconf -ivf

  # SteamOS: We turn on more features than upstream plymouth,
  # (in particular the x11 backend) and we use a different
  # fallback logo:
  ./configure \
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
    --enable-gtk=yes \
    --with-release-file=/etc/os-release \
    --with-logo=/usr/share/pixmaps/steamos.png \
    --with-background-color=0x000000 \
    --with-background-start-color-stop=0x000000 \
    --with-background-end-color-stop=0x4D4D4D \
    --without-rhgb-compat-link \
    --without-system-root-install \
    --with-runtimedir=/run
  make V=0
}

package() {
  cd "$pkgname-$pkgver"
  make DESTDIR="$pkgdir" install
  rm -r "$pkgdir/var/run"

  # Install mkinitcpio hook
  install -Dm644 ../plymouth.initcpio_hook "$pkgdir/usr/lib/initcpio/hooks/$pkgname"
  install -Dm644 ../plymouth.initcpio_install "$pkgdir/usr/lib/initcpio/install/$pkgname"
  install -Dm644 "$srcdir/plymouth-deactivate.service" 	"$pkgdir/usr/lib/systemd/system/plymouth-deactivate.service"
}
