# Maintainer : Christian Hesse <mail@eworm.de>
# Maintainer : Ronald van Haren <ronald.archlinux.org>
# Contributor: Tobias Powalowski <tpowa@archlinux.org>
# Contributor: Keshav Amburay <(the ddoott ridikulus ddoott rat) (aatt) (gemmaeiil) (ddoott) (ccoomm)>

## "1" to enable IA32-EFI build in Arch x86_64, "0" to disable
_IA32_EFI_IN_ARCH_X64="1"

## "1" to enable EMU build, "0" to disable
_GRUB_EMU_BUILD="0"

[[ "${CARCH}" == 'x86_64' ]] && _EFI_ARCH='x86_64'
[[ "${CARCH}" == 'i686' ]] && _EFI_ARCH='i386'

[[ "${CARCH}" == 'x86_64' ]] && _EMU_ARCH='x86_64'
[[ "${CARCH}" == 'i686' ]] && _EMU_ARCH='i386'

pkgname='grub'
pkgdesc='GNU GRand Unified Bootloader (2)'
epoch=2
_tag='53c5000739db114c229fe69ec3d4b76b92441098' # git rev-parse grub-${_pkgver}
_gnulib_commit='be584c56eb1311606e5ea1a36363b97bddb6eed3'
_unifont_ver='14.0.01'
_pkgver=2.06
pkgver=${_pkgver/-/}
pkgrel=4.5
url='https://www.gnu.org/software/grub/'
arch=('x86_64')
license=('GPL3')
backup=('etc/default/grub'
        'etc/grub.d/40_custom')
install="${pkgname}.install"
options=('!makeflags')

conflicts=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}" 'grub-legacy')
replaces=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}")
provides=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}")

makedepends=('git' 'rsync' 'xz' 'freetype2' 'ttf-dejavu' 'python' 'autogen'
             'texinfo' 'help2man' 'gettext' 'device-mapper' 'fuse2')
depends=('sh' 'xz' 'gettext' 'device-mapper')
optdepends=('freetype2: For grub-mkfont usage'
            'fuse2: For grub-mount usage'
            'dosfstools: For grub-mkrescue FAT FS and EFI support'
            'lzop: For grub-mkrescue LZO support'
            'efibootmgr: For grub-install EFI support'
            'libisoburn: Provides xorriso for generating grub rescue iso using grub-mkrescue'
            'os-prober: To detect other OSes when generating grub.cfg in BIOS systems'
            'mtools: For grub-mkrescue FAT FS support')

if [[ "${_GRUB_EMU_BUILD}" == "1" ]]; then
    makedepends+=('libusbx' 'sdl')
    optdepends+=('libusbx: For grub-emu USB support'
                 'sdl: For grub-emu SDL support')
fi

validpgpkeys=('E53D497F3FA42AD8C9B4D1E835A93B74E82E4209'  # Vladimir 'phcoder' Serbinenko <phcoder@gmail.com>
              'BE5C23209ACDDACEB20DB0A28C8189F1988C2166'  # Daniel Kiper <dkiper@net-space.pl>
              '95D2E9AB8740D8046387FD151A09227B1F435A33') # Paul Hardy <unifoundry@unifoundry.com>

source=("git+https://git.savannah.gnu.org/git/grub.git#tag=${_tag}?signed"
        "git+https://git.savannah.gnu.org/git/gnulib.git#commit=${_gnulib_commit}"
        "https://ftp.gnu.org/gnu/unifont/unifont-${_unifont_ver}/unifont-${_unifont_ver}.bdf.gz"{,.sig}
        'debian-olpc-prefix-hack.patch'
        'debian-core-in-fs.patch'
        'debian-dpkg-version-comparison.patch'
        'debian-grub-legacy-0-based-partitions.patch'
        'debian-disable-floppies.patch'
        'debian-grub.cfg-400.patch'
        'debian-gfxpayload-keep-default.patch'
        'debian-mkrescue-efi-modules.patch'
        'debian-mkconfig-loopback.patch'
        'debian-restore-mkdevicemap.patch'
        'debian-gettext-quiet.patch'
        'debian-install-efi-fallback.patch'
        'debian-mkconfig-ubuntu-recovery.patch'
        'debian-install-locale-langpack.patch'
        'debian-mkconfig-nonexistent-loopback.patch'
        'debian-no-insmod-on-sb.patch'
        'debian-default-grub-d.patch'
        'debian-blacklist-1440x900x32.patch'
        'debian-mkconfig-ubuntu-distributor.patch'
        'debian-linuxefi.patch'
        'debian-mkconfig-signed-kernel.patch'
        'debian-install-signed.patch'
        'debian-wubi-no-windows.patch'
        'debian-maybe-quiet.patch'
        'debian-install-efi-adjust-distributor.patch'
        'debian-quick-boot.patch'
        'debian-quick-boot-lvm.patch'
        'debian-gfxpayload-dynamic.patch'
        'debian-vt-handoff.patch'
        'debian-probe-fusionio.patch'
        'debian-ignore-grub_func_test-failures.patch'
        'debian-mkconfig-recovery-title.patch'
        'debian-install-powerpc-machtypes.patch'
        'debian-ieee1275-clear-reset.patch'
        'debian-ppc64el-disable-vsx.patch'
        'debian-grub-install-pvxen-paths.patch'
        'debian-insmod-xzio-and-lzopio-on-xen.patch'
        'debian-grub-install-extra-removable.patch'
        'debian-mkconfig-other-inits.patch'
        'debian-zpool-full-device-name.patch'
        'debian-net-read-bracketed-ipv6-addr.patch'
        'debian-bootp-new-net_bootp6-command.patch'
        'debian-efinet-uefi-ipv6-pxe-support.patch'
        'debian-bootp-process-dhcpack-http-boot.patch'
        'debian-efinet-set-network-from-uefi-devpath.patch'
        'debian-efinet-set-dns-from-uefi-proto.patch'
        'debian-fix-lockdown.patch'
        'debian-skip-grub_cmd_set_date.patch'
        'debian-bash-completion-drop-have-checks.patch'
        'debian-at_keyboard-module-init.patch'
        'debian-uefi-secure-boot-cryptomount.patch'
        'debian-efi-variable-storage-minimise-writes.patch'
        'debian-no-devicetree-if-secure-boot.patch'
        'debian-grub-install-removable-shim.patch'
        'debian-dejavu-font-path.patch'
        'debian-xen-no-xsm-policy-in-non-xsm-options.patch'
        'debian-safe-alloc-5.patch'
        'debian-bootp-alloc.patch'
        'debian-unix-config-overflow.patch'
        'debian-deviceiter-overflow.patch'
        '0001-00_header-add-GRUB_COLOR_-variables.patch'
        '0002-10_linux-detect-archlinux-initramfs.patch'
        'steamos-0001-SteamOS-stage-II-bootloader-implemented-as-a-grub-mo.patch'
        'steamos-0002-Reduce-eagerness-of-grub-install-to-remove-other-boo.patch'
        'steamos-0003-Patch-grub-install-to-support-a-custom-grub-mkimage.patch'
        'steamos-0005-Fix-Add-configure-option-to-bypass-boot-menu-if-poss.patch'
        'steamos-0006-10_linux-always-hide-the-Loading-messages-in-quiet-m.patch'
        'steamos-0007-00_header-steamenv.patch'
        'grub-recordfail.service'
        'grub.default')

sha256sums=('SKIP'
            'SKIP'
            '391d194f6307fcd0915daafd360509a734e26f3e4013e63d47deb2530d59e66e'
            'SKIP'
            '417fb948234b9f1a7b466a88ec9aef51e9409131f375fc2bacd9216504088b14'
            'be150109b09f937a9c70174d2ec7a4f38add4125908842219d3d8f8abc9619a6'
            '418a1b11549ffaa5b96f974916d36b5d00f003ed58631fdd199f96bb7cf925ea'
            '40dfa6adfdf4638a72ee87c8e2ff2fbdcaf41e81dca5e330e53a1c87ecff8eaf'
            '39691deec693addac7ec6bcaecd24b6917884034d32742d58410f17d48174baa'
            '95d7a502e81330268e05b8fb0fd9021f48b44f9d843a5b24197c15f272ae6c5e'
            '2f7e94dd9206092881df157141794ac8e8559ee95643db165f212e6f8e266222'
            '90be90bbd604875e17a4d97b6689b94d7c8b695f17a4eb917fe62fc0e09bdb6d'
            'bf84445900797c5a1d4605a0c750e24e285d98b124ce0b78400bd21294709a37'
            '978c0dbbbfc210f251b6fffbe8da630330769decb059f81ef5c3e43a4ed4e048'
            '52bdaaea2596b93666a3470ee354f5f20db1fdca5e6c6765ac5a32e4a8c26345'
            'b2b2c805e308c62198ed81428f2c6f143d0da1f48a0e6562c3f0467e34e2dcf8'
            'aef21376173bce3c85dc2153ff0fb8c1366e8b119a492dd4e87e10578e4f95cb'
            '5b4a5d64ab5808b966df54b42ab5066cd46062814d0c9f547c752afb148c5c39'
            '9c8e36577c8493ea9c199bc0cebaaafb3be7518b6fc2da730bd4f4c95f6f148b'
            '1eb9a22aaaf724617218c2d57ae1816c0eccc1d2fccbe08d5d26cf7184f9a236'
            '33ef7e232cef526b4ab5e801f7423ff44ef0b4cbaf129da510edc92ffd4ca223'
            '7afefd1e0afb21924e2207cc644f6fd30b8cab7364fe24864df1bf64e054d61d'
            'f9e204a019f0ca2acca826ae98540d099497272402d5d934d0b44d1a533b8403'
            '8210af34ccca0b67697206b124f646ca88093899d73dd0911c506e51d13204a1'
            '2a71f86bf11c8fad0f6a3301d22b7d9e6341585d39814dddc21ea995765bb972'
            '0465eece73e6cc4937118f6649a8aad7e4f86217b829bc92688f2fdb39304a00'
            'da1d54da56b1175c41f7ea5ed55c7d305b714b61eb10361bd50dd402fd66628f'
            '4560286dfe5afe95afa91a8d46aa36a3fd10ad2bf6b7c7847bb19084c3a4c640'
            '26f815c4ac19100aa75a0dbd2fa2cc8ae1a0be38e9ae09c8e72d1eda3baf56a9'
            'dd396c05333d1551c19531dc06fab446980cdf5920cbca85f2a835d5d1910f69'
            '3f3936df78b71cec700116457d6d2a5c089d49325ec7aa8fad35f94312d6f917'
            'a94bcf2ca5b3652a4ad2c100e46110514220809255221b6d9271044f4b0e904d'
            'f514b17eb9e21d305927bc8c0eb033bb9eaa5814f626ad183a4f3a9ffb6a5358'
            '0b71ab17279c1c700a4c4e64317feaece8d97500c59719a011b10c270e48e8f6'
            '07b4dfe8550930f76d224a999923c3d4bf5f5871fa5c6914dfe90d0079d25622'
            'b9819422f62c0471cd7fb21782d9d480224286df1cf32e7cc3a8fc313b46dfb2'
            '7dbf5c8bf695422b109963d44f88c5947748498a13f66bc0bcb8b2e80fc7b27a'
            '4bc3f581363225c4a7c9d5e6d3238bd96ddb06ecdac2c8e6e4de6d9504389e2b'
            '61f422db46a9642656cbaebaad674a58952c25e4ab0dc5f93e20be4a9fc250c4'
            '8672a82d06e53d17b5cbb599151c7e48b6b789da7ad4925a5733b754261b4554'
            'f9ef7d3d4c39549f73643ff1a28719c09dc7dd01fa2285158fe4347b8645017d'
            '7b09400c7a9bcd18ca7d535404688d7bb8b024ebc8bfad73a9b9bb81d097ddd9'
            'f83c19cdf398e5a3c0ddab722566d9e1753a68a5177663ff6944451a40454230'
            'f54f6558eb17affdce9974f7917ef5ef28afb675faa1b7de066d048aa9f36205'
            '7a2df4ae172381ef4f1a3049f8f18a7dccfd1918414da0a06a126491ba89e617'
            'cfdcd31f37483930ce0affa3f379c6b62f948dd4099000e2765e49c5868e8e74'
            '22fae003a69c01e25708d4463eed29e4b3e0fa462ca1a2d76fd5890bad5c86dd'
            'f7d9b9a863dfa944e0845e0f18e2d7c2a4085df50991791ccc08bfcb94a2e0a1'
            'dc01caea3c829c8afc265f709acc0b3cf8b9796c37dd9d9832ffe27757c25cef'
            '22754f2d2ec7b2953bc2c91280a388d1d36a60c5f48ba63306a6fa3941eef39c'
            '1f318d66edc8b22d9b51f3bef5654b4a6f8c7ea61fe3aa1ffeb72db0b1f9998d'
            '9a14439fbe608b638ef2466706bf2f4ac8d4c2e22986a32d03b34e472eeb9dff'
            'cf0fa7c6a236f5cd72cece363bb64cb06678a9f6737d351e7dc2c614e3095523'
            'e0f2f5b3e97088f23294deae56a61c8a0ef104de0b97469347ed682813827b45'
            'c8baf1fc62b3e55014fe6fd29acec749164ca09007cb51fd426271719e88cf38'
            'e49f107bbb8d161c49610c918f03dd37a89b13b373e767b4db3971046225d955'
            '75e2fbe4de204fe7fb3ff67a84edbb49e14c3161fc5da09e1f0bb0bc559ed6fe'
            '5f35ac60acab77e3f3d7c644368df6fd1151ee02275f97e07c6a5ebe5e39e726'
            '44a1ec4c5cadf5899b5e99c8cb385179d36840d6c8a036b06097ea127ae7ef15'
            'f1572755df503b3566a01ce6e8d8b4ff1a6cea29fdc7330c7ab15928daa0a869'
            '4d1ce68c2ccad6b7829fc2bf081c59b04ec9b6327a7a4a13b9074e438727ce88'
            'cbc785aab8d6211f2e12db87e28e6ee10302bde82236320991a1a85b099b9315'
            'd785f4c4cdea03af111c9f9a0d3f0d7922fe44409e91bfbb101996394ca0518b'
            '77bc269851a5ef01db256a745b93bb191936a2c9018884f88a9a7b0d657741b9'
            '5dee6628c48eef79812bb9e86ee772068d85e7fcebbd2b2b8d1e19d24eda9dab'
            '06f756f57fe017188c53bd363bd367ea2ea0cef0aef4253469f7017802a7bf63'
            'e6d9fb71295a96ff5c7f4971cc6d14f1eac72db2473a1084ec7c8116a657f5d4'
            'c2b46fa4f3c43161de12ebd0ff4e12da37eeae07fcb3ffb487e0c194630d9ee6'
            'bb3f5f2729ed7ab35d749fae3c15b229cc719b189f94224a685742230595db86'
            '943bdf086bd2b386322bcce608b15de90e7955c92f1fcded491255c2bc3167c5'
            'cca890f4be9a2c58fc290b488b4ef9eeb490066726297e4fda5ec87215d9e7a9'
            '95e7805670c72b26afb94d6a4765e9ec5f19298fb8a75e97b9543847be5e6148'
            '65d41c0bcb933cf06060082b60571ba6c4e40b873e13117fca5708101e7182c2'
            '9f6fad49d082d7e1372563a971c7d1221df7603dca3fb6de16324ee7c10528e9')

_backports=(
	# fs/xfs: Fix unreadable filesystem with v4 superblock
	'a4b495520e4dc41a896a8b916a64eda9970c50ea'
)

_configure_options=(
	FREETYPE="pkg-config freetype2"
	BUILD_FREETYPE="pkg-config freetype2"
	--enable-mm-debug
	--enable-nls
	--enable-device-mapper
	--enable-cache-stats
	--enable-grub-mkfont
	--enable-grub-mount
	--prefix="/usr"
	--bindir="/usr/bin"
	--sbindir="/usr/bin"
	--mandir="/usr/share/man"
	--infodir="/usr/share/info"
	--datarootdir="/usr/share"
	--sysconfdir="/etc"
	--program-prefix=""
	--with-bootdir="/boot"
	--with-grubdir="grub"
	--disable-silent-rules
	# SteamOS: #T21734: quick-boot and quiet-boot are imported from debian(via patch)
	# but disabled by default so enable manually.
	--enable-quiet-boot
	--enable-quick-boot
	--disable-werror
)

prepare() {
	cd "${srcdir}/grub/"

	echo "Apply backports..."
	local _c
	for _c in "${_backports[@]}"; do
		git log --oneline -1 "${_c}"
		git cherry-pick -n "${_c}"
	done

	echo "Patches from debian..."
	patch -Np1 -i "${srcdir}/debian-olpc-prefix-hack.patch"
	patch -Np1 -i "${srcdir}/debian-core-in-fs.patch"
	patch -Np1 -i "${srcdir}/debian-dpkg-version-comparison.patch"
	patch -Np1 -i "${srcdir}/debian-grub-legacy-0-based-partitions.patch"
	patch -Np1 -i "${srcdir}/debian-disable-floppies.patch"
	patch -Np1 -i "${srcdir}/debian-grub.cfg-400.patch"
	patch -Np1 -i "${srcdir}/debian-gfxpayload-keep-default.patch"
	patch -Np1 -i "${srcdir}/debian-mkrescue-efi-modules.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-loopback.patch"
	patch -Np1 -i "${srcdir}/debian-restore-mkdevicemap.patch"
	patch -Np1 -i "${srcdir}/debian-gettext-quiet.patch"
	patch -Np1 -i "${srcdir}/debian-install-efi-fallback.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-ubuntu-recovery.patch"
	patch -Np1 -i "${srcdir}/debian-install-locale-langpack.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-nonexistent-loopback.patch"
	patch -Np1 -i "${srcdir}/debian-no-insmod-on-sb.patch"
	patch -Np1 -i "${srcdir}/debian-default-grub-d.patch"
	patch -Np1 -i "${srcdir}/debian-blacklist-1440x900x32.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-ubuntu-distributor.patch"
	patch -Np1 -i "${srcdir}/debian-linuxefi.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-signed-kernel.patch"
	patch -Np1 -i "${srcdir}/debian-install-signed.patch"
	patch -Np1 -i "${srcdir}/debian-wubi-no-windows.patch"
	patch -Np1 -i "${srcdir}/debian-maybe-quiet.patch"
	patch -Np1 -i "${srcdir}/debian-install-efi-adjust-distributor.patch"
	patch -Np1 -i "${srcdir}/debian-quick-boot.patch"
	patch -Np1 -i "${srcdir}/debian-quick-boot-lvm.patch"
	patch -Np1 -i "${srcdir}/debian-gfxpayload-dynamic.patch"
	patch -Np1 -i "${srcdir}/debian-vt-handoff.patch"
	patch -Np1 -i "${srcdir}/debian-probe-fusionio.patch"
	patch -Np1 -i "${srcdir}/debian-ignore-grub_func_test-failures.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-recovery-title.patch"
	patch -Np1 -i "${srcdir}/debian-install-powerpc-machtypes.patch"
	patch -Np1 -i "${srcdir}/debian-ieee1275-clear-reset.patch"
	patch -Np1 -i "${srcdir}/debian-ppc64el-disable-vsx.patch"
	patch -Np1 -i "${srcdir}/debian-grub-install-pvxen-paths.patch"
	patch -Np1 -i "${srcdir}/debian-insmod-xzio-and-lzopio-on-xen.patch"
	patch -Np1 -i "${srcdir}/debian-grub-install-extra-removable.patch"
	patch -Np1 -i "${srcdir}/debian-mkconfig-other-inits.patch"
	patch -Np1 -i "${srcdir}/debian-zpool-full-device-name.patch"
	patch -Np1 -i "${srcdir}/debian-net-read-bracketed-ipv6-addr.patch"
	patch -Np1 -i "${srcdir}/debian-bootp-new-net_bootp6-command.patch"
	patch -Np1 -i "${srcdir}/debian-efinet-uefi-ipv6-pxe-support.patch"
	patch -Np1 -i "${srcdir}/debian-bootp-process-dhcpack-http-boot.patch"
	patch -Np1 -i "${srcdir}/debian-efinet-set-network-from-uefi-devpath.patch"
	patch -Np1 -i "${srcdir}/debian-efinet-set-dns-from-uefi-proto.patch"
	patch -Np1 -i "${srcdir}/debian-fix-lockdown.patch"
	patch -Np1 -i "${srcdir}/debian-skip-grub_cmd_set_date.patch"
	patch -Np1 -i "${srcdir}/debian-bash-completion-drop-have-checks.patch"
	patch -Np1 -i "${srcdir}/debian-at_keyboard-module-init.patch"
	patch -Np1 -i "${srcdir}/debian-uefi-secure-boot-cryptomount.patch"
	patch -Np1 -i "${srcdir}/debian-efi-variable-storage-minimise-writes.patch"
	patch -Np1 -i "${srcdir}/debian-no-devicetree-if-secure-boot.patch"
	patch -Np1 -i "${srcdir}/debian-grub-install-removable-shim.patch"
	patch -Np1 -i "${srcdir}/debian-dejavu-font-path.patch"
	patch -Np1 -i "${srcdir}/debian-xen-no-xsm-policy-in-non-xsm-options.patch"
	patch -Np1 -i "${srcdir}/debian-safe-alloc-5.patch"
	patch -Np1 -i "${srcdir}/debian-bootp-alloc.patch"
	patch -Np1 -i "${srcdir}/debian-unix-config-overflow.patch"
	patch -Np1 -i "${srcdir}/debian-deviceiter-overflow.patch"

	echo "Patch to enable GRUB_COLOR_* variables in grub-mkconfig..."
	## Based on http://lists.gnu.org/archive/html/grub-devel/2012-02/msg00021.html
        patch -Np1 -i "${srcdir}/0001-00_header-add-GRUB_COLOR_-variables.patch"

	echo "Patch to detect of Arch Linux initramfs images by grub-mkconfig..."
        patch -Np1 -i "${srcdir}/0002-10_linux-detect-archlinux-initramfs.patch"

	echo "Patch for SteamOS..."
	patch -Np1 -i "${srcdir}/steamos-0001-SteamOS-stage-II-bootloader-implemented-as-a-grub-mo.patch"
	patch -Np1 -i "${srcdir}/steamos-0002-Reduce-eagerness-of-grub-install-to-remove-other-boo.patch"
	patch -Np1 -i "${srcdir}/steamos-0003-Patch-grub-install-to-support-a-custom-grub-mkimage.patch"
	patch -Np1 -i "${srcdir}/steamos-0005-Fix-Add-configure-option-to-bypass-boot-menu-if-poss.patch"
	patch -Np1 -i "${srcdir}/steamos-0006-10_linux-always-hide-the-Loading-messages-in-quiet-m.patch"
        patch -Np1 -i "${srcdir}/steamos-0007-00_header-steamenv.patch"
	echo

	echo "Revert patch that handle the Debian kernel version numbers..."
	patch -Rp1 -i "${srcdir}/debian-dpkg-version-comparison.patch"
	echo

	echo "Fix DejaVuSans.ttf location so that grub-mkfont can create *.pf2 files for starfield theme..."
	sed 's|/usr/share/fonts/dejavu|/usr/share/fonts/dejavu /usr/share/fonts/TTF|g' -i "configure.ac"

	echo "Fix mkinitcpio 'rw' FS#36275..."
	sed 's| ro | rw |g' -i "util/grub.d/10_linux.in"

	echo "Fix OS naming FS#33393..."
	sed 's|GNU/Linux|Linux|' -i "util/grub.d/10_linux.in"

	echo "Pull in latest language files..."
	./linguas.sh

	echo "Avoid problem with unifont during compile of grub..."
	# http://savannah.gnu.org/bugs/?40330 and https://bugs.archlinux.org/task/37847
	gzip -cd "${srcdir}/unifont-${_unifont_ver}.bdf.gz" > "unifont.bdf"

	echo "Run bootstrap..."
	./bootstrap \
		--gnulib-srcdir="${srcdir}/gnulib/" \
		--no-git

	echo "Make translations reproducible..."
	sed -i '1i /^PO-Revision-Date:/ d' po/*.sed
}

_build_grub-common_and_bios() {
	echo "Set ARCH dependent variables for bios build..."
	if [[ "${CARCH}" == 'x86_64' ]]; then
		_EFIEMU="--enable-efiemu"
	else
		_EFIEMU="--disable-efiemu"
	fi

	echo "Copy the source for building the bios part..."
	cp -r "${srcdir}/grub/" "${srcdir}/grub-bios/"
	cd "${srcdir}/grub-bios/"

	echo "Unset all compiler FLAGS for bios build..."
	unset CFLAGS
	unset CPPFLAGS
	unset CXXFLAGS
	unset LDFLAGS
	unset MAKEFLAGS

	echo "Run ./configure for bios build..."
	./configure \
		--with-platform="pc" \
		--target="i386" \
		"${_EFIEMU}" \
		--enable-boot-time \
		"${_configure_options[@]}"

	if [ ! -z "${SOURCE_DATE_EPOCH}" ]; then
		echo "Make info pages reproducible..."
		touch -d "@${SOURCE_DATE_EPOCH}" $(find -name '*.texi')
	fi

	echo "Run make for bios build..."
	make
}

_build_grub-efi() {
	echo "Copy the source for building the ${_EFI_ARCH} efi part..."
	cp -r "${srcdir}/grub/" "${srcdir}/grub-efi-${_EFI_ARCH}/"
	cd "${srcdir}/grub-efi-${_EFI_ARCH}/"

	echo "Unset all compiler FLAGS for ${_EFI_ARCH} efi build..."
	unset CFLAGS
	unset CPPFLAGS
	unset CXXFLAGS
	unset LDFLAGS
	unset MAKEFLAGS

	echo "Run ./configure for ${_EFI_ARCH} efi build..."
	./configure \
		--with-platform="efi" \
		--target="${_EFI_ARCH}" \
		--disable-efiemu \
		--enable-boot-time \
		"${_configure_options[@]}"

	echo "Run make for ${_EFI_ARCH} efi build..."
	make
}

_build_grub-emu() {
	echo "Copy the source for building the emu part..."
	cp -r "${srcdir}/grub/" "${srcdir}/grub-emu/"
	cd "${srcdir}/grub-emu/"

	echo "Unset all compiler FLAGS for emu build..."
	unset CFLAGS
	unset CPPFLAGS
	unset CXXFLAGS
	unset LDFLAGS
	unset MAKEFLAGS

	echo "Run ./configure for emu build..."
	./configure \
		--with-platform="emu" \
		--target="${_EMU_ARCH}" \
		--enable-grub-emu-usb=no \
		--enable-grub-emu-sdl=no \
		--disable-grub-emu-pci \
		"${_configure_options[@]}"

	echo "Run make for emu build..."
	make
}

build() {
	cd "${srcdir}/grub/"

	echo "Build grub bios stuff..."
	_build_grub-common_and_bios

	echo "Build grub ${_EFI_ARCH} efi stuff..."
	_build_grub-efi

	if [[ "${CARCH}" == "x86_64" ]] && [[ "${_IA32_EFI_IN_ARCH_X64}" == "1" ]]; then
		echo "Build grub i386 efi stuff..."
		_EFI_ARCH="i386" _build_grub-efi
	fi

	if [[ "${_GRUB_EMU_BUILD}" == "1" ]]; then
		echo "Build grub emu stuff..."
		_build_grub-emu
	fi
}

_package_grub-common_and_bios() {
	cd "${srcdir}/grub-bios/"

	echo "Run make install for bios build..."
	make DESTDIR="${pkgdir}/" bashcompletiondir="/usr/share/bash-completion/completions" install

	echo "Remove gdb debugging related files for bios build..."
	rm -f "${pkgdir}/usr/lib/grub/i386-pc"/*.module || true
	rm -f "${pkgdir}/usr/lib/grub/i386-pc"/*.image || true
	rm -f "${pkgdir}/usr/lib/grub/i386-pc"/{kernel.exec,gdb_grub,gmodule.pl} || true

	echo "Install /etc/default/grub (used by grub-mkconfig)..."
	install -D -m0644 "${srcdir}/grub.default" "${pkgdir}/etc/default/grub"
}

_package_grub-efi() {
	cd "${srcdir}/grub-efi-${_EFI_ARCH}/"

	echo "Run make install for ${_EFI_ARCH} efi build..."
	make DESTDIR="${pkgdir}/" bashcompletiondir="/usr/share/bash-completion/completions" install

	echo "Remove gdb debugging related files for ${_EFI_ARCH} efi build..."
	rm -f "${pkgdir}/usr/lib/grub/${_EFI_ARCH}-efi"/*.module || true
	rm -f "${pkgdir}/usr/lib/grub/${_EFI_ARCH}-efi"/*.image || true
	rm -f "${pkgdir}/usr/lib/grub/${_EFI_ARCH}-efi"/{kernel.exec,gdb_grub,gmodule.pl} || true

	_sbat_file="${pkgdir}/usr/share/grub/sbat.csv"
	touch "${_sbat_file}"
	echo "sbat,1,SBAT Version,sbat,1,https://github.com/rhboot/shim/blob/main/SBAT.md" >> "${_sbat_file}"
	echo "grub,1,Free Software Foundation,grub,${_pkgver},https//www.gnu.org/software/grub/" >> "${_sbat_file}"
	echo "grub.arch,1,Arch Linux,grub,${_pkgver},https://archlinux.org/packages/core/x86_64/grub/" >> "${_sbat_file}"
}

_package_grub-emu() {
	cd "${srcdir}/grub-emu/"

	echo "Run make install for emu build..."
	make DESTDIR="${pkgdir}/" bashcompletiondir="/usr/share/bash-completion/completions" install

	echo "Remove gdb debugging related files for emu build..."
	rm -f "${pkgdir}/usr/lib/grub/${_EMU_ARCH}-emu"/*.module || true
	rm -f "${pkgdir}/usr/lib/grub/${_EMU_ARCH}-emu"/*.image || true
	rm -f "${pkgdir}/usr/lib/grub/${_EMU_ARCH}-emu"/{kernel.exec,gdb_grub,gmodule.pl} || true
}

package() {
	cd "${srcdir}/grub/"

	echo "Package grub ${_EFI_ARCH} efi stuff..."
	_package_grub-efi

	if [[ "${CARCH}" == "x86_64" ]] && [[ "${_IA32_EFI_IN_ARCH_X64}" == "1" ]]; then
		echo "Package grub i386 efi stuff..."
		_EFI_ARCH="i386" _package_grub-efi
	fi

	if [[ "${_GRUB_EMU_BUILD}" == "1" ]]; then
		echo "Package grub emu stuff..."
		_package_grub-emu
	fi

	echo "Package grub bios stuff..."
	_package_grub-common_and_bios

	echo "Package recordfail stuff..."
	install -D -m644 ${srcdir}/grub-recordfail.service "${pkgdir}/usr/lib/systemd/system/grub-recordfail.service"

	echo "Move grub binaries to libdir..."
	mv "${pkgdir}/usr/bin/grub-install" "${pkgdir}/usr/lib/grub/grub-install"
	mv "${pkgdir}/usr/bin/grub-mkimage" "${pkgdir}/usr/lib/grub/grub-mkimage"
}
