#include <stdint.h>
#include <stdbool.h>

typedef struct tagcontact
{
  uint32_t uiWindow;
  uint32_t uiCount;

  uint32_t bCurrentState : 1;
  uint32_t bPreviousState : 1;

  uint32_t bEventState : 1;
  uint32_t bEvent : 1;
  uint32_t bReserved : 28;

  uint8_t uiPort;
  uint32_t uiPortAddress;
  uint8_t uiBit;

} CONTACT;

void CONTACT_Init(CONTACT *pContact, uint32_t uiWindow, uint8_t uiPort, uint8_t uiBit);
bool CONTACT_Sample(CONTACT *pContact);
