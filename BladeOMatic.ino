//<App !Start!>
// FILE: [BladeOMatic.ino]
// Created by GUIslice Builder version: [0.17.b19]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "BladeOMatic_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemOutTxtEpeeGND= NULL;
gslc_tsElemRef* m_pElemOutTxtEpeeShort= NULL;
gslc_tsElemRef* m_pElemOutTxtEpeeTip= NULL;
gslc_tsElemRef* m_pElemOutTxtFoilGND= NULL;
gslc_tsElemRef* m_pElemOutTxtFoilShort= NULL;
gslc_tsElemRef* m_pElemOutTxtFoilTip= NULL;
gslc_tsElemRef* m_pElemOutTxtSabreGND= NULL;
gslc_tsElemRef* m_pElemOutTxtSabreShort= NULL;
gslc_tsElemRef* m_pElemOutTxtSabreTip= NULL;
gslc_tsElemRef* m_pElemProgressBattery= NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  Serial.printf("CbBtnCommon() elemID %d eTouch %d x %d y%d\n", pElem->nId, eTouch, nX, nY);

  if ( eTouch == GSLC_TOUCH_DOWN_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN_EPEE:
        gslc_SetPageCur(&m_gui, E_PG_EPEE);
        break;
      case E_ELEM_BTN_FOIL:
        gslc_SetPageCur(&m_gui, E_PG_FOIL);
        break;
      case E_ELEM_BTN_SABRE:
        gslc_SetPageCur(&m_gui, E_PG_SABRE);
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}

