#include <portio.h>
#include <kernel/pci.h>
#define internal
#include "ata.h"

ata_pci_dev_t ata_pci_devs[10];
ata_pci_dev_t *ata_pci_dev=ata_pci_devs;
void ata_init()
{
	return;
}
