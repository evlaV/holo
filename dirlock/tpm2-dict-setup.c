/*
 * Copyright © 2025 Valve Corporation
 * Author: Alberto Garcia <berto@igalia.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * This is a small helper tool to change the default values of the TPM
 * dictionary attack mechanism in order to give users more failed
 * authentication attempts before they are locked out by the TPM.
 *
 * Note that this is only used to help test dirlock and is not a
 * proper TPM provisioning tool. In particular this does not protect
 * the dictionary attack lockout mechanism with a password or a
 * policy, so any user with root access can change the values set
 * here.
 */

#include <tss2/tss2_esys.h>
#include <tss2/tss2_tctildr.h>
#include <tss2/tss2_rc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const char *tcti;
    TSS2_TCTI_CONTEXT *tcti_ctx = NULL;
    ESYS_CONTEXT *esys_ctx = NULL;
    TPMS_CAPABILITY_DATA *cap = NULL;
    const TPMS_TAGGED_PROPERTY *props;
    UINT32 pt_permanent = 0;
    UINT32 max_tries, recovery_time, lockout_recovery = 1000;
    int ret;
    size_t i;

    /* Read the commmand-line parameters */
    if (argc != 3) {
        fprintf(stderr, "Usage: tpm2-dict-setup <max-tries> <recovery-time>\n");
        return 1;
    }

    ret = atoi(argv[1]);
    if (ret > 0 && ret <= UINT32_MAX) {
        max_tries = ret;
    } else {
        fprintf(stderr, "Error: incorrect value for max-tries '%s'\n", argv[1]);
        return 1;
    }

    ret = atoi(argv[2]);
    if (ret > 0 && ret <= UINT32_MAX) {
        recovery_time = ret;
    } else {
        fprintf(stderr, "Error: incorrect value for recovery-time '%s'\n", argv[2]);
        return 1;
    }

    /* Tell the TSS library not to log anything to stderr */
    setenv("TSS2_LOG", "all+NONE", 1);

    /* We use /dev/tpm0, it can be overridden with the TCTI variable */
    tcti = getenv("TCTI");
    if (!tcti)
        tcti = "device:/dev/tpm0";

    /* Initialize the TCTI context */
    ret = Tss2_TctiLdr_Initialize(tcti, &tcti_ctx);
    if (ret != TPM2_RC_SUCCESS)
        goto out;

    /* Initialize the ESYS context */
    ret = Esys_Initialize(&esys_ctx, tcti_ctx, NULL);
    if (ret != TPM2_RC_SUCCESS)
        goto out;

    /* Get all variable properties */
    ret = Esys_GetCapability(
        esys_ctx,
        ESYS_TR_NONE,
        ESYS_TR_NONE,
        ESYS_TR_NONE,
        TPM2_CAP_TPM_PROPERTIES,
        TPM2_PT_VAR,
        TPM2_MAX_TPM_PROPERTIES,
        0,
        &cap);
    if (ret != TPM2_RC_SUCCESS)
        goto out;

    /*
     * The properties that we want are:
     * - The value of lockoutAuthSet (to see if we can make changes)
     * - The value of LOCKOUT_RECOVERY (because we want to keep it)
     */
    props = cap->data.tpmProperties.tpmProperty;
    for (i = 0; i < cap->data.tpmProperties.count; i++) {
        /* We cannot do anything if lockoutAuth is set (i.e. if the
           dictionary attack lockout mechanism is password protected) */
        if (props[i].property == TPM2_PT_PERMANENT && pt_permanent & TPMA_PERMANENT_LOCKOUTAUTHSET) {
            ret = TPM2_RC_AUTH_MISSING;
            goto out;
        }

        if (props[i].property == TPM2_PT_LOCKOUT_RECOVERY) {
            lockout_recovery = props[i].value;
        }
    }

    /* Set the new values. max_tries and recovery_time are passed
       from the command line, lockout_recovery is the existing value */
    ret = Esys_DictionaryAttackParameters(
        esys_ctx,
        ESYS_TR_RH_LOCKOUT,
        ESYS_TR_PASSWORD,
        ESYS_TR_NONE,
        ESYS_TR_NONE,
        max_tries,
        recovery_time,
        lockout_recovery);

out:
    free(cap);

    if (esys_ctx != NULL)
        Esys_Finalize(&esys_ctx);

    if (tcti_ctx != NULL)
        Tss2_TctiLdr_Finalize(&tcti_ctx);

    if (ret != TPM2_RC_SUCCESS)
        printf("Error: %s\n", Tss2_RC_Decode(ret));

    return ret == TPM2_RC_SUCCESS ? 0 : 1;
}
