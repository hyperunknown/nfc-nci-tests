#include <stdio.h>
#include <unistd.h>

#include "linux_nfc_factory_api.h"
#include "linux_nfc_api.h"

static nfcTagCallback_t cb_tag;

void tagArrived(nfc_tag_info_t *p_taginfo)
{
    printf("\nTag arrived!\n");
}

void tagDeparted(void)
{
    printf("\nTag departed!\n");
}

int main(int argc, char ** argv)
{
    // initialize nfcManager
    int result = nfcManager_doInitialize();
    if(result != 0) {
        printf("nfcManager_doInitialize failed with error code %d", result);
        return result;
    }

    // try to get versions
    printf("nfcFactory_GetMwVersion:\t%x\n", nfcFactory_GetMwVersion());
    printf("nfcManager_getFwVersion:\t%x\n", nfcManager_getFwVersion());

    // set up tag-callback
	cb_tag.onTagArrival = tagArrived;
	cb_tag.onTagDeparture = tagDeparted;
	nfcManager_registerTagCallback(&cb_tag);

	nfcManager_enableDiscovery(DEFAULT_NFA_TECH_MASK, 0x00, 0x00, 0);

    do {
        sleep(1);
    } while(1);

    printf("Exiting...\n");
    return 0;
}