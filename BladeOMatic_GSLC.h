//<File !Start!>
// FILE: [BladeOMatic_GSLC.h]
// Created by GUIslice Builder version: [0.17.b19]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XProgress.h"
//<Includes !End!>
  
// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
//#include "NULLFreeSans9pt7b.h"
//#include "NULLFreeSansBold9pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_EPEE,E_PG_FOIL,E_PG_SABRE};
enum {E_ELEM_BTN_EPEE,E_ELEM_BTN_FOIL,E_ELEM_BTN_SABRE,E_ELEM_CHECK_GND
      ,E_ELEM_CHECK_SHORT,E_ELEM_CHECK_TIP,E_ELEM_PROGRESSBATTERY
      ,E_ELEM_TEXT11,E_ELEM_TEXT12,E_ELEM_TEXT13,E_ELEM_TEXT14
      ,E_ELEM_TEXT15,E_ELEM_TEXT16,E_ELEM_TEXT17,E_ELEM_TEXT18
      ,E_ELEM_TEXT19,E_ELEM_TEXT4,E_ELEM_TEXT5,E_ELEM_TEXT6
      ,E_ELEM_TEXT8,E_ELEM_TEXT9,E_ELEM_TEXT_EPEE_SHORT
      ,E_ELEM_TEXT_EPEE_TIP,E_ELEM_TEXT_FOIL_SHORT,E_ELEM_TEXT_FOIL_TIP
      ,E_ELEM_TEXT_PRESSEDSHORTE,E_ELEM_TEXT_PRESSEDSHORTF
      ,E_ELEM_TEXT_PRESSEDSHORTS,E_ELEM_TEXT_SABRE_SHORT
      ,E_ELEM_TEXT_SABRE_TIP};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,E_FREESANS9,E_FREESANSBOLD9,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                4

#define MAX_ELEM_PG_BASE 9 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_EPEE 7 // # Elems total on page
#define MAX_ELEM_PG_EPEE_RAM MAX_ELEM_PG_EPEE // # Elems in RAM

#define MAX_ELEM_PG_FOIL 7 // # Elems total on page
#define MAX_ELEM_PG_FOIL_RAM MAX_ELEM_PG_FOIL // # Elems in RAM

#define MAX_ELEM_PG_SABRE 7 // # Elems total on page
#define MAX_ELEM_PG_SABRE_RAM MAX_ELEM_PG_SABRE // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_EPEE_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_EPEE];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_FOIL_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_FOIL];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_SABRE_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_SABRE];
gslc_tsXProgress                m_sXBarGauge2;
gslc_tsXCheckbox                m_asXCheck1;
gslc_tsXCheckbox                m_asXCheck2;
gslc_tsXCheckbox                m_asXCheck3;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemCBCheckBoxGND;
extern gslc_tsElemRef* m_pElemCBCheckBoxShort;
extern gslc_tsElemRef* m_pElemCBCheckBoxTip;
extern gslc_tsElemRef* m_pElemOutTxtEpeeGND;
extern gslc_tsElemRef* m_pElemOutTxtEpeeShort;
extern gslc_tsElemRef* m_pElemOutTxtEpeeTip;
extern gslc_tsElemRef* m_pElemOutTxtFoilGND;
extern gslc_tsElemRef* m_pElemOutTxtFoilShort;
extern gslc_tsElemRef* m_pElemOutTxtFoilTip;
extern gslc_tsElemRef* m_pElemOutTxtSabreGND;
extern gslc_tsElemRef* m_pElemOutTxtSabreShort;
extern gslc_tsElemRef* m_pElemOutTxtSabreTip;
extern gslc_tsElemRef* m_pElemProgressBattery;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  Serial.println("InitGUIslice_gen()");
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { 
    Serial.println("InitGUIslice_gen() - bad INIT");
    return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANS9,GSLC_FONTREF_PTR,&FreeSans9pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANSBOLD9,GSLC_FONTREF_PTR,&FreeSansBold9pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_EPEE,m_asPage1Elem,MAX_ELEM_PG_EPEE_RAM,m_asPage1ElemRef,MAX_ELEM_PG_EPEE);
  gslc_PageAdd(&m_gui,E_PG_FOIL,m_asPage2Elem,MAX_ELEM_PG_FOIL_RAM,m_asPage2ElemRef,MAX_ELEM_PG_FOIL);
  gslc_PageAdd(&m_gui,E_PG_SABRE,m_asPage3Elem,MAX_ELEM_PG_SABRE_RAM,m_asPage3ElemRef,MAX_ELEM_PG_SABRE);

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_EPEE);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // create E_ELEM_BTN_EPEE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_EPEE,E_PG_BASE,
    (gslc_tsRect){390,20,80,40},(char*)"Epee",0,E_FREESANSBOLD9,&CbBtnCommon);
  
  // create E_ELEM_BTN_FOIL button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_FOIL,E_PG_BASE,
    (gslc_tsRect){390,130,80,40},(char*)"Foil",0,E_FREESANSBOLD9,&CbBtnCommon);
  
  // create E_ELEM_BTN_SABRE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_SABRE,E_PG_BASE,
    (gslc_tsRect){390,230,80,40},(char*)"Sabre",0,E_FREESANSBOLD9,&CbBtnCommon);
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_BASE,(gslc_tsRect){50,290,114,8},
    (char*)"Blade O Matic V 0.1",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_BASE,(gslc_tsRect){360,290,48,12},
    (char*)"Battery:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // Create progress bar E_ELEM_PROGRESSBATTERY 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESSBATTERY,E_PG_BASE,&m_sXBarGauge2,
    (gslc_tsRect){420,290,50,12},0,100,0,GSLC_COL_GREEN,false);
  m_pElemProgressBattery = pElemRef;
   
  // create checkbox E_ELEM_CHECK_SHORT
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK_SHORT,E_PG_BASE,&m_asXCheck1,
    (gslc_tsRect){250,61,10,10},false,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemCBCheckBoxShort = pElemRef;
   
  // create checkbox E_ELEM_CHECK_TIP
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK_TIP,E_PG_BASE,&m_asXCheck2,
    (gslc_tsRect){250,124,10,10},false,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemCBCheckBoxTip = pElemRef;
   
  // create checkbox E_ELEM_CHECK_GND
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK_GND,E_PG_BASE,&m_asXCheck3,
    (gslc_tsRect){250,183,10,10},false,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemCBCheckBoxGND = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_EPEE
  
  
  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_EPEE,(gslc_tsRect){10,60,186,13},
    (char*)"Shorts across wires 1-3",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_EPEE,(gslc_tsRect){10,120,67,16},
    (char*)"Tip state",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_EPEE,(gslc_tsRect){10,180,217,16},
    (char*)"Tip shorts to GND on press",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT17,E_PG_EPEE,(gslc_tsRect){160,20,144,17},
    (char*)"Testing for Epee: ",0,E_FREESANSBOLD9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT_EPEE_SHORT runtime modifiable text
  static char m_sDisplayText21[33] = "No short";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_EPEE_SHORT,E_PG_EPEE,(gslc_tsRect){270,60,200,13},
    (char*)m_sDisplayText21,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtEpeeShort = pElemRef;
  
  // Create E_ELEM_TEXT_EPEE_TIP runtime modifiable text
  static char m_sDisplayText22[33] = "Not Tested";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_EPEE_TIP,E_PG_EPEE,(gslc_tsRect){270,120,200,16},
    (char*)m_sDisplayText22,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtEpeeTip = pElemRef;
  
  // Create E_ELEM_TEXT_PRESSEDSHORTE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_PRESSEDSHORTE,E_PG_EPEE,(gslc_tsRect){270,180,67,13},
    (char*)"No short",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtEpeeGND = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_FOIL
  
  
  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG_FOIL,(gslc_tsRect){10,60,186,13},
    (char*)"Shorts across wires 1-3",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT12,E_PG_FOIL,(gslc_tsRect){10,120,67,16},
    (char*)"Tip state",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT13,E_PG_FOIL,(gslc_tsRect){10,180,217,16},
    (char*)"Tip shorts to GND on press",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT18,E_PG_FOIL,(gslc_tsRect){160,20,133,17},
    (char*)"Testing for Foil: ",0,E_FREESANSBOLD9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT_FOIL_SHORT runtime modifiable text
  static char m_sDisplayText24[33] = "No short";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_FOIL_SHORT,E_PG_FOIL,(gslc_tsRect){270,60,200,13},
    (char*)m_sDisplayText24,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtFoilShort = pElemRef;
  
  // Create E_ELEM_TEXT_FOIL_TIP runtime modifiable text
  static char m_sDisplayText25[33] = "Not Tested";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_FOIL_TIP,E_PG_FOIL,(gslc_tsRect){270,120,200,16},
    (char*)m_sDisplayText25,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtFoilTip = pElemRef;
  
  // Create E_ELEM_TEXT_PRESSEDSHORTF text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_PRESSEDSHORTF,E_PG_FOIL,(gslc_tsRect){270,180,67,13},
    (char*)"No short",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtFoilGND = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SABRE
  
  
  // Create E_ELEM_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_SABRE,(gslc_tsRect){10,60,186,13},
    (char*)"Shorts across wires 1-3",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT15,E_PG_SABRE,(gslc_tsRect){10,120,67,16},
    (char*)"Tip state",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT16,E_PG_SABRE,(gslc_tsRect){10,180,217,16},
    (char*)"Tip shorts to GND on press",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT19,E_PG_SABRE,(gslc_tsRect){160,20,151,17},
    (char*)"Testing for Sabre: ",0,E_FREESANSBOLD9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT_SABRE_SHORT runtime modifiable text
  static char m_sDisplayText27[33] = "No short";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_SABRE_SHORT,E_PG_SABRE,(gslc_tsRect){270,60,200,13},
    (char*)m_sDisplayText27,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtSabreShort = pElemRef;
  
  // Create E_ELEM_TEXT_SABRE_TIP runtime modifiable text
  static char m_sDisplayText28[33] = "Not Tested";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_SABRE_TIP,E_PG_SABRE,(gslc_tsRect){270,120,200,16},
    (char*)m_sDisplayText28,33,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtSabreTip = pElemRef;
  
  // Create E_ELEM_TEXT_PRESSEDSHORTS text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_PRESSEDSHORTS,E_PG_SABRE,(gslc_tsRect){270,180,67,13},
    (char*)"No short",0,E_FREESANS9);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxtSabreGND = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
