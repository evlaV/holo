#!/bin/bash

# SPDX-License-Identifier: MIT
#
# Copyright 2025 © Valve Corporation.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the “Software”), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set -u

if ! [[ -v EARLYOOM_PID && -v EARLYOOM_UID && -v EARLYOOM_NAME && -v EARLYOOM_CMDLINE ]]; then
    echo "error: $0 invoked without EARLYOOM_* vars defined, exiting." >&2
    exit 1
fi

STEAMAPPID_FILE="/run/holo-earlyoom/prehook-report-${EARLYOOM_PID}"
if [[ ! -r "${STEAMAPPID_FILE}" ]]; then
    STEAMAPPID="missing or cannot read file '${STEAMAPPID_FILE}'"
else
    STEAMAPPID=$(cat "${STEAMAPPID_FILE}" 2>&1)
fi

TAG=$(basename "${0}")
DATE=$(date '+%F_%T')

LOGDIR="/run/holo-earlyoom"
if [[ ! -d "${LOGDIR}" ]]; then
    mkdir --mode=0750 "${LOGDIR}"
fi

LOGFILE=$(mktemp "${LOGDIR}/logger-${DATE}-XXXXXXXX.log")
chmod 0600 "${LOGFILE}"

# D-BUS notifications, write variables to file for proper quoting of
# strings (esp. command-line)
{
    # assuming 4 EARLYOOM_* vars
    DBUS_VARS_N=4

    # retrieve SteamAppId, strip var name and non-digit characters
    if [[ "${STEAMAPPID}" =~ SteamAppId=.* ]]; then
	SteamAppId=$(echo "${STEAMAPPID}" | sed -e 's/SteamAppId=//')
	if [[ -n "${SteamAppId//[0-9]/}" ]]; then
	    echo "warning: SteamAppId='${SteamAppId}' contains garbage, clearing and ignoring it." >&2
	    unset SteamAppId
	else
	    SteamAppId_dbus_var=" steamappid u ${SteamAppId}"
	    ((DBUS_VARS_N++))
	fi
    fi

    echo "Will send D-BUS notification/signal with command:"
    (
	# subshell for the "-x" flag to only affect this single line, to
	# register the 'busctl' command issued for auditing/debugging purposes
	set -x
	busctl emit /com/steampowered/HoloEarlyoom com.steampowered.HoloEarlyoom ProcessKilled -- "a{sv}" "${DBUS_VARS_N}" \
	       ${SteamAppId_dbus_var:-} \
	       pid u "${EARLYOOM_PID}" \
	       uid u "${EARLYOOM_UID}" \
	       comm s "${EARLYOOM_NAME}" \
	       command_line s "${EARLYOOM_CMDLINE}"
    )
} &>> "${LOGFILE}"

# Log variables and command to be executed
{
    echo "EARLYOOM_PID:     ${EARLYOOM_PID}"
    echo "EARLYOOM_UID:     ${EARLYOOM_UID}"
    echo "EARLYOOM_NAME:    ${EARLYOOM_NAME}"
    echo "EARLYOOM_CMDLINE: ${EARLYOOM_CMDLINE}"

    if [[ -v SteamAppId ]]; then
        echo "SteamAppId=${SteamAppId}"
    else
        echo "error: could not read a proper SteamAppId from the killed process,"
	echo "       perhaps not launched from Steam (thus no SteamAppId env var)"
	echo "       or the pre-hook could not retrieve SteamAppId for some reason:"
        echo "       ${STEAMAPPID}"
    fi
} &>> "${LOGFILE}"

logger --tag "${TAG}" --file "${LOGFILE}"

# clean-up
rm -rf "${LOGFILE}" "${STEAMAPPID_FILE}"
