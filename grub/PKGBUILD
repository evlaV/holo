# Maintainer : Christian Hesse <mail@eworm.de>
# Maintainer : Tobias Powalowski <tpowa@archlinux.org>
# Contributor: Ronald van Haren <ronald.archlinux.org>
# Contributor: Keshav Amburay <(the ddoott ridikulus ddoott rat) (aatt) (gemmaeiil) (ddoott) (ccoomm)>

## "1" to enable IA32-EFI build in Arch x86_64, "0" to disable
_IA32_EFI_IN_ARCH_X64="0"

## "1" to enable EMU build, "0" to disable
_GRUB_EMU_BUILD="0"

[[ "${CARCH}" == 'x86_64' ]] && _EFI_ARCH='x86_64'
[[ "${CARCH}" == 'i686' ]] && _EFI_ARCH='i386'

[[ "${CARCH}" == 'x86_64' ]] && _EMU_ARCH='x86_64'
[[ "${CARCH}" == 'i686' ]] && _EMU_ARCH='i386'

pkgname='grub'
pkgdesc='GNU GRand Unified Bootloader (2)'
epoch=2
_tag='03e6ea18f6f834f177cad017279bedbb0a3de594' # git rev-parse grub-${_pkgver}
_gnulib_commit='cfdbd92718d6d4989bfe885448063d7863aa69dc' # git rev-parse origin/stable-202407
_pkgver=2.12
_unifont_ver='15.1.05'
pkgver=${_pkgver/-/}
pkgrel=2.1
url='https://www.gnu.org/software/grub/'
arch=('x86_64')
license=('GPL-3.0-or-later')
backup=('etc/default/grub'
        'etc/grub.d/40_custom')
install="${pkgname}.install"
options=('!makeflags')

conflicts=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}" 'grub-legacy')
replaces=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}")
provides=('grub-common' 'grub-bios' 'grub-emu' "grub-efi-${_EFI_ARCH}")

makedepends=('git' 'rsync' 'xz' 'freetype2' 'ttf-dejavu' 'python>=3.11' 'python<3.12' 'autogen'
             'texinfo' 'help2man' 'gettext' 'device-mapper' 'fuse3')
depends=('sh' 'xz' 'gettext' 'device-mapper')
optdepends=('freetype2: For grub-mkfont usage'
            'fuse3: For grub-mount usage'
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

# this is for tracking patches from elsewhere (debian, arch, etc)
# that we should not be using. It's not standard pkgbuild but it
# lets us catch patches if someone adds them back in:
declare -A excluded_patches=(
    ['arch-0003-support-dropins-for-default-configuration.patch']='Arch: subset of debian-default-grub-d.patch'
    ['debian-olpc-prefix-hack.patch']='OpenBoot/OFW: ieee1275 support hack - not required'
    ['debian-grub-legacy-0-based-partitions.patch']='GRUB legacy support - obsolete'
    ['debian-disable-floppies.patch']='Ignores floppies: we do not need to as they do not exist'
    ['debian-gfxpayload-keep-default.patch']='Suppresses the ‘keep’ graphics default - not needed'
    ['debian-mkconfig-ubuntu-distributor.patch']='Ubuntu: Distribution specific label changes'
    ['debian-install-stage2-confusion.patch']='GRUB legacy support - obsolete'
    ['debian-install-efi-fallback.patch']='Fallback to non-EFI boot: Not supported by x86 SteamOS'
    ['debian-mkconfig-ubuntu-recovery.patch']='Ubuntu: recovery mode support - not needed'
    ['debian-install-locale-langpack.patch']='Ubuntu: langpack support - not needed'
    ['debian-install-efi-adjust-distributor.patch']='Cosmetic kubuntu and devuan labels - not needed'
    ['debian-quick-boot.patch']='Quick Boot: not useful on EFI as there is no keydown detection'
    ['debian-quick-boot-lvm.patch']='Quick Boot: not useful on EFI as there is no keydown detection'
    ['debian-gfxpayload-dynamic.patch']='Legacy: boot gfxpayload=keep support - not needed'
    ['debian-vt-handoff.patch']='Legacy: VT handoff for flicker free boot - not needed'
    ['debian-probe-fusionio.patch']='FusionIO disc support - obsolete'
    ['debian-ignore-grub_func_test-failures.patch']='Disable a video mode test - not needed'
    ['debian-mkconfig-recovery-title.patch']='Text for recovery boot entries - not needed'
    ['debian-skip-grub_cmd_set_date.patch']='Disables a test - not needed'
    ['debian-pc-verifiers-module.patch']='Disables verifiers on grub-pc - not a supported platform for SteamOS'
    ['debian-revert-term-ns8250-spcr.patch']='Legacy: diables serial auto detection on grub-pc - not a supported platform for SteamOS'
    ['debian-install-powerpc-machtypes.patch']='PowerPC: NVRAM quirks - not needed'
    ['debian-ieee1275-clear-reset.patch']='PowerPC: OFW text mode quirk - not needed'
    ['debian-ppc64el-disable-vsx.patch']='PowerPC PPC64: (Power7 and Power8) - not needed'
    ['debian-grub-install-pvxen-paths.patch']='Xen: boot path support - not needed'
    ['debian-insmod-xzio-and-lzopio-on-xen.patch']='Xen: xzio and lzio support - not needed'
    ['debian-zpool-full-device-name.patch']='ZFS initramfs support - not needed'
    ['debian-bootp-new-net_bootp6-command.patch']='bootp6: network booting - not needed'
    ['debian-bootp-process-dhcpack-http-boot.patch']='bootp fix: network booting - not needed'
    ['debian-uefi-secure-boot-cryptomount.patch']='secureboot + full disk encryption support - not needed'
    ['debian-xen-no-xsm-policy-in-non-xsm-options.patch']='Xen: build system quirk workaround'
    ['debian-recovery-dis_ucode_ldr.patch']='Failsafe: ignore microcode loader in recovery option - SteamOS does not have a recovery option'
    ['debian-hwmatch-only-on-grub-pc-platform.patch']='Legacy: i386 only hardware blacklist'
    ['debian-install-signed.patch']='Secureboot: Install signed images - not supported by SteamOS'
    ['debian-grub-install-removable-shim.patch']='Secureboot: install signed shim - not supported by SteamOS'
)
# Arch patch '0003-support-dropins-for-default-configuration.patch' excluded
# as it is a subset of the debian patch 'debian-default-grub-d.patch'
source=("git+https://git.savannah.gnu.org/git/grub.git#tag=${_tag}?signed"
        "git+https://git.savannah.gnu.org/git/gnulib.git#commit=${_gnulib_commit}"
        "https://ftp.gnu.org/gnu/unifont/unifont-${_unifont_ver}/unifont-${_unifont_ver}.bdf.gz"{,.sig}
        'arch-0001-00_header-add-GRUB_COLOR_-variables.patch'
        'arch-0002-10_linux-detect-archlinux-initramfs.patch'
        'debian-core-in-fs.patch'
        'debian-mkconfig-loopback.patch'
        'debian-restore-mkdevicemap.patch'
        'debian-gettext-quiet.patch'
        'debian-mkconfig-nonexistent-loopback.patch'
        'debian-default-grub-d.patch'
        'debian-blacklist-1440x900x32.patch'
        'debian-maybe-quiet.patch'
        'debian-bash-completion-drop-have-checks.patch'
        'debian-at_keyboard-module-init.patch'
        'debian-efi-variable-storage-minimise-writes.patch'
        'debian-debug_verifiers.patch'
        'debian-mkimage-fix-section-sizes.patch'
        'debian-987008-lvrename-boot-fail.patch'
        'debian-grub_os-prober.patch'
        'debian-zstd-require-8-byte-buffer.patch'
        'debian-fat-fix-listing-the-root-directory.patch'
        'debian-efivar-check-that-efivarfs-is-writeable.patch'
        'debian-fdt-add-debug-output-to-devicetree-command.patch'
        'debian-fdt-device-tree-fixup-protocol.patch'
        'debian-grub-install-extra-removable.patch'
        'steamos-0001-SteamOS-stage-II-bootloader-implemented-as-a-grub-mo.patch'
        'steamos-0002-Reduce-eagerness-of-grub-install-to-remove-other-boo.patch'
        'steamos-0003-Patch-grub-install-to-support-a-custom-grub-mkimage.patch'
        'steamos-0006-10_linux-always-hide-the-Loading-messages-in-quiet-m.patch'
        'steamos-0008-Use-SteamOS-specific-kernel-command-line-settings-if.patch'
        'steamos-0009-Disable-EFI-1.0-UGA-Support.patch'
        'steamos-0010-Defer-theme-loading-until-we-know-we-need-it.patch'
        'build-tweaks-1.patch'
        'build-tweaks-2.diff' # applied via bootstrap by build-tweaks-1.patch
        'grub.default')

# unifont-15.1.05.bdf.gz
# 8ea5b5a14d71e3353d1fea373f5d88d198ad1e285cedd8294655926ee11fd91d
sha256sums=('SKIP'
            'SKIP'
            '8ea5b5a14d71e3353d1fea373f5d88d198ad1e285cedd8294655926ee11fd91d'
            'SKIP'
            'f63ab8e6d340052d5248f93aaf856a3c7ae910eedef6ceaf653802408ebab573'
            '8488aec30a93e8fe66c23ef8c23aefda39c38389530e9e73ba3fbcc8315d244d'
            '9dfd44b21a2aa3bf1e16036cda753baa325b64c8c1ebc2ddfa0ce138b00b1e92'
            '070f87c281a99a0be14910bfd953684e951f16f6dc14b9597032a6153db58e66'
            '3fac7b90aee01637def80e5de3f70fbe3a0647a67f5ebc6f2eaef5738223cfd1'
            'e2c846cb7bc7f59d7786112ee94285710ee318cc67139c46dc100035376575a1'
            'ee6521ef5c2b0b93b435dad2b13107710753e8d71339babeae92743b3ca88f1a'
            '19b58743baf889c80b72bc691fa58113517f8eb47dea830095747d93e506d533'
            'ca30ff7d77be2b89622ae94fbf4b5f28a04fb0b0433ef13270fec5b44fdf76b0'
            '6e575cec0e095ada41390742ab468ad5cfb8e7f36b6015da07c7a6ec2097c592'
            '1963f5f5303e99c6e74ce8d89541c0b180a12830f181ab8c432f53d5fca75e6c'
            'cf500cd47d4d49c08988d59880e991b2a84f8df842141dcff539fee3d764e348'
            '4fe12f176b1a7fe883ed228412a45e879b1e3847a8dbb922d7028b73f6bcc205'
            '724d9d6fa3052242385946aae19c45a729c3844122ce784eba08e04496097d27'
            '26f670ac83a7587d015563897962bd5721534c2a015e67c939c92c5314ad7f40'
            '50747adf074ef0b5d63b616bb68524eb30adde6467902b1899d8a0445395836e'
            'a043e3f7f4833cbd3ece6e29d2c9dcedd7ecc31a9adfb69cb964858c373480dc'
            'a78363e16d192de4cdde43ff3366613fc18870e4a6b29724a7d6aac59cecf805'
            'd928cedb7bd6b404fbf71b5052628462f6b2d6b893f3b2918ecb17f133057c13'
            '8bdcde4e42d5860c0bedba21901ea83f49ace602d8011377e38506192c95e7cd'
            '658bd3474f84fbbfe675da93e2e05b6d156658c92a2d604b52d6a0b23223c71b'
            '6e8c873eae8988cb99fd6b3de0857c0ec4db0ed2fd90c6d0054a3f88361c013c'
            '02eb5080d99bebd6843b172367813ab7968508e48894f241c409703cf05aeff2'
            '08b4970c01cedeeeb4ef87bf748f8eb46278a58db42abea3fc84f4ad93d69cd0'
            '4dc26722812df2a261f9e27632bcacdb5899d49b7270a66dd67f270b6eba05e1'
            'ccd8ba6646a298f015707d6cbf5f20db418569a1878617224f2946d2dbb503fc'
            'cca890f4be9a2c58fc290b488b4ef9eeb490066726297e4fda5ec87215d9e7a9'
            'cf078325cbd14fbe01c59632e1bc41188b55748ae355a3c8d1198ebff09cab90'
            'b44f10d3f30a0bc0aff94617cce0570593d408b09e3cc5f05d7d97a4888169b0'
            'f80fd0837be9edcb77cd0e346357218cc39dda325ef932fa888eabad8570ffc7'
            '2cfb4c61f1724e496fafc7224bdf4218012f4dc612f267055ea2c140522a0505'
            '7caac232189069e46cd3dd68e615c68712625d287cdbce34fe9169b51b0070ea'
            '7a8e55d517de423bbe0f1e16d1c43e9cf1a6600b8169764000e23e547a7b6989'
)

patch_allowed () {
    local patch_name="${1:-}"
    local msg="${excluded_patches[$patch_name]:-}"

    if [ -n "$msg" ]
    then
        echo "Patch $patch_name rejected: ${msg:-Reason not recorded}" >&2
        return 1
    fi

    return 0
}

filter_patchlist () {
    local -i n=0
    local -a _src=()
    local -a _sum=()

    while [ $n -lt ${#source[@]} ]
    do
        case ${source[$n]} in
            debian-*.patch|arch-*.patch|steamos-*.patch|build-*.patch)
                if patch_allowed ${source[$n]}
                then
                    _src+=(${source[$n]})
                    _sum+=(${sha256sums[$n]})
                fi
                ;;
            *.patch)
                echo "ERROR: Unexpcted patch name ${source[$n]}" >&2
                echo "  Patches must be arch- steamos- debian- or build-" >&2
                exit 1
                ;;
            *)
                _src+=(${source[$n]})
                _sum+=(${sha256sums[$n]})
                ;;
        esac
        n=$((n + 1))
    done

    source=("${_src[@]}")
    sha256sums=("${_sum[@]}")
}

filter_patchlist

_backports=(
)

_configure_options=(
	PACKAGE_VERSION="${epoch}:${pkgver}-${pkgrel}"
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
	# SteamOS: #T21734: quiet-boot is imported from debian (via patch)
	# but disabled by default so enable manually.
        # quick-boot was imported the same way but is no longer necessary
	--enable-quiet-boot
	--disable-werror
)

patch_ident () {
    local _input="$1"
    local _ident=

    _ident=$(grep '^Subject:' ../"$_input")
    _ident=${_ident#Subject: }

    echo "${_ident:-$_input}"
}

prepare() {
	cd "${srcdir}/grub/"

	echo "Apply backports..."
	local _c
	for _c in "${_backports[@]}"; do
		git log --oneline -1 "${_c}"
		git cherry-pick -n "${_c}"
	done

	echo "Patches from debian..."
        local _p
        for _p in "${source[@]}"; do
            case $_p in
                debian-*.patch)
                    echo "Applying: ""$(patch_ident $_p)"
                    patch -Np1 -i ../"$_p"
                    ;;
            esac
        done

	echo "Patches from Arch..."
        for _p in "${source[@]}"; do            
            case $_p in
                arch-*.patch)
                    echo "Applying: ""$(patch_ident $_p)"
                    patch -Np1 -i ../"$_p"
                    ;;
            esac
        done

        echo "Patches from SteamOS..."
        for _p in "${source[@]}"; do
            case $_p in
                steamos-*.patch)
                    echo "Applying: ""$(patch_ident $_p)"
                    patch -Np1 -i ../"$_p"
                    ;;
            esac
        done

        echo "Build system fixes (fewer warnings)..."
        patch -Np1 -i "${srcdir}/build-tweaks-1.patch"

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

	#echo "Build grub bios stuff..."
	#_build_grub-common_and_bios

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

	echo "Install /etc/default/grub (used by grub-mkconfig)..."
	install -D -m0644 "${srcdir}/grub.default" "${pkgdir}/etc/default/grub"
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

	#echo "Package grub bios stuff..."
	#_package_grub-common_and_bios

	echo "Move grub binaries to libdir..."
	mv "${pkgdir}/usr/bin/grub-install" "${pkgdir}/usr/lib/grub/grub-install"
	mv "${pkgdir}/usr/bin/grub-mkimage" "${pkgdir}/usr/lib/grub/grub-mkimage"
}
