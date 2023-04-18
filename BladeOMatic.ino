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

// Defines
#define PIN_PURPLE_ONE_A    0  //O
#define PIN_WHITE_TWO_B     2  //O
                             //    
#define PIN_ORANGE_THREE_C 15  //O
#define PIN_GREEN_BATTERY 33

#define SAMPLE_TIME_SECS 5
#define CHAR_32_SPACES   "                                "
                        //12345678901234567890123456789012
                        //         1         2         3
// ------------------------------------------------
// Program Globals
// ------------------------------------------------
SemaphoreHandle_t xTipSemaphore = NULL;
//SemaphoreHandle_t xTipCompletionSemaphore = NULL;
TaskHandle_t xTipTaskHandle = NULL;

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemCBCheckBoxGND= NULL;
gslc_tsElemRef* m_pElemCBCheckBoxShort= NULL;
gslc_tsElemRef* m_pElemCBCheckBoxTip= NULL;
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
static int currentPage = E_PG_EPEE;
static int testStage =0;
static int testTipStage = 0;

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

void UpdateBatteryStatus()
{
  pinMode(PIN_GREEN_BATTERY,INPUT_PULLDOWN); //set pin to input
  //read
  float pinReadVoltage = analogRead(PIN_GREEN_BATTERY) * 3.3 / 4096;
  int batteryPercentage = (int)round((3.14/pinReadVoltage) * 100);
  gslc_ElemXProgressSetVal(&m_gui,m_pElemProgressBattery,batteryPercentage);
}
bool TestForShort(gslc_tsElemRef*  elemRefToDisplay)
{
  bool retVal = false;
  gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxShort, GSLC_COL_BLUE);
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxShort, true);

  pinMode(PIN_PURPLE_ONE_A,OUTPUT); //set pin1 out
  pinMode(PIN_WHITE_TWO_B,INPUT_PULLDOWN);   //set pin2 in
  pinMode(PIN_ORANGE_THREE_C,INPUT_PULLDOWN);//set pin3 in
  
  digitalWrite(PIN_PURPLE_ONE_A,HIGH); //set pin1 high
  delay(50); 

  uint16_t pin1_2a = analogRead(PIN_WHITE_TWO_B);  //test pin 2 and 3
  uint16_t pin1_3a = analogRead(PIN_ORANGE_THREE_C);  //test pin 2 and 3
  int pin1_2d = digitalRead(PIN_WHITE_TWO_B);
  int pin1_3d = digitalRead(PIN_ORANGE_THREE_C);  //test pin 2 and 3
  digitalWrite(PIN_PURPLE_ONE_A,LOW); 

  pinMode(PIN_PURPLE_ONE_A,INPUT_PULLDOWN);//set pin3 in  
  pinMode(PIN_WHITE_TWO_B,OUTPUT);//set pin2 out

  digitalWrite(PIN_WHITE_TWO_B,HIGH); //set pin1 high
  delay(50); 

  uint16_t pin2_3a = analogRead(PIN_ORANGE_THREE_C); //test pin 3
  int pin2_3d = digitalRead(PIN_ORANGE_THREE_C);
  digitalWrite(PIN_WHITE_TWO_B,LOW);

  Serial.printf("pin1_2 %d pin2_3 %d pin1_3 %d pin1_2d %d pin2_3d %d pin1_3d %d\n", pin1_2a, pin2_3a, pin1_3a, pin1_2d, pin2_3d, pin1_3d);

  String resultStr = String("No Short");
  
  if (pin1_2d > 0 || pin1_3d > 0 || pin2_3d >0) 
  {
    retVal = false;
    resultStr = "Short: ";
    if (pin1_2d > 0)
      resultStr += "1-2";
    
    if (pin2_3d > 0)
      resultStr += (pin1_2d > 0) ? ",2-3":"2-3";
    
    if (pin1_3d > 0)
      resultStr += (pin1_2d + pin2_3d > 0) ? ",1-3" : "1,3";
    
    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxShort,GSLC_COL_RED);
  }
  else
    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxShort,GSLC_COL_GREEN);

  gslc_ElemSetTxtStr(&m_gui, elemRefToDisplay, resultStr.c_str());
  return retVal;
}
void TestEpeeTip()
{
    bool wasPressed = false;
    
    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip, GSLC_COL_BLUE);
    gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxTip, true);
    
    pinMode(PIN_PURPLE_ONE_A,OUTPUT); //set pin1 out
    pinMode(PIN_WHITE_TWO_B,INPUT_PULLDOWN);   //set pin2 in
    delay(50);
    digitalWrite(PIN_PURPLE_ONE_A,HIGH); //set pin1 high
    
    delay(50);

    String resultStr = String("Testing ");
    
    unsigned long timeMillis = 0;
    for (int secs  = SAMPLE_TIME_SECS; secs > 0; secs--)
    {
      Serial.printf("TestEpeeTip 7.%d\n", secs);
      timeMillis = millis();
      while ((millis() - timeMillis) <  1000UL)
      {
        int pin2d = digitalRead(PIN_WHITE_TWO_B);
        int pin2a = analogRead(PIN_WHITE_TWO_B);
        if (pin2d > 0)
        {
            resultStr = "Contact (";
            wasPressed = true;
         
        }
        else
          resultStr = "No contact (";

        resultStr = resultStr + secs;
        resultStr = resultStr + ")";
       
        if ((millis() - timeMillis) % 500 == 0)
          {
            gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtEpeeTip, GSLC_COL_BLACK);
            gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtEpeeTip, CHAR_32_SPACES);
            gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtEpeeTip, resultStr.c_str());
            gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtEpeeTip, GSLC_COL_YELLOW);
            Serial.printf("TestEpeeTip set text 7.%d %s %ld pin2d %d pin2a %d\n", secs, resultStr.c_str(), millis(), pin2d, pin2a);
          }
        //gslc_Update(&m_gui);
      }
      
    }

    digitalWrite(PIN_PURPLE_ONE_A,LOW); 

    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip,wasPressed ? GSLC_COL_GREEN : GSLC_COL_RED);

    gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtEpeeTip, wasPressed ? "Touch" : "No touch");

    Serial.printf("TestEpeeTip exiting\n");
}

void TestFoilTip()
{ 
  Serial.printf("Entering TestFoilTip\n");
  bool wasPressed = false;
  
  gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip, GSLC_COL_BLUE);
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxTip, true);
  
  pinMode(PIN_ORANGE_THREE_C,OUTPUT); //set pin3 out
  pinMode(PIN_WHITE_TWO_B,INPUT_PULLDOWN);   //set pin2 in
  delay(50);
  digitalWrite(PIN_ORANGE_THREE_C,HIGH); //set pin3 high
  
  delay(50);

  String resultStr = String("Testing ");
  
  unsigned long timeMillis = 0;
  for (int secs  = SAMPLE_TIME_SECS; secs > 0; secs--)
  {
    Serial.printf("TestFoilTip 7.%d\n", secs);
    timeMillis = millis();
    while ((millis() - timeMillis) <  1000UL)
    {
      int pin2d = digitalRead(PIN_WHITE_TWO_B);
      int pin2a = analogRead(PIN_WHITE_TWO_B);
      if (pin2d > 0)
      {
          resultStr = "Contact (";
          wasPressed = true;
        
      }
      else
        resultStr = "No contact (";

      resultStr = resultStr + secs;
      resultStr = resultStr + ")";
      
      if ((millis() - timeMillis) % 500 == 0)
        {
          gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtFoilTip, GSLC_COL_BLACK);
          gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtFoilTip, CHAR_32_SPACES);
          gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtFoilTip, resultStr.c_str());
          gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtFoilTip, GSLC_COL_YELLOW);
          Serial.printf("TestFoilTip set text 7.%d %s %ld pin2d %d pin2a %d\n", secs, resultStr.c_str(), millis(), pin2d, pin2a);
        }
      //gslc_Update(&m_gui);
    } 
     
  }

  digitalWrite(PIN_ORANGE_THREE_C,LOW); 

  gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip,wasPressed ? GSLC_COL_GREEN : GSLC_COL_RED);

  gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtFoilTip, wasPressed ? "Touch" : "No touch");
  gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip,wasPressed ? GSLC_COL_GREEN : GSLC_COL_RED);

  Serial.printf("TestFoilTip exiting\n");
}

void TestSabreTip()
{
 bool wasPressed = false;
    
    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip, GSLC_COL_BLUE);
    gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxTip, true);
    
    pinMode(PIN_ORANGE_THREE_C,OUTPUT); //set pin1 out
    pinMode(PIN_WHITE_TWO_B,INPUT_PULLDOWN);   //set pin2 in
    delay(50);
    digitalWrite(PIN_ORANGE_THREE_C,HIGH); //set pin1 high
    
    delay(50);

    String resultStr = String("Testing ");
    
    unsigned long timeMillis = 0;
    for (int secs  = SAMPLE_TIME_SECS; secs > 0; secs--)
    {
      Serial.printf("TestSabreTip 7.%d\n", secs);
      timeMillis = millis();
      while ((millis() - timeMillis) <  1000UL)
      {
        int pin2d = digitalRead(PIN_WHITE_TWO_B);
        int pin2a = analogRead(PIN_WHITE_TWO_B);
        if (pin2d > 0)
        {
            resultStr = "Contact (";
            wasPressed = true;
         
        }
        else
          resultStr = "No contact (";

        resultStr = resultStr + secs;
        resultStr = resultStr + ")";
       
        if ((millis() - timeMillis) % 500 == 0)
        {
          gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtSabreTip, GSLC_COL_BLACK);
          gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtSabreTip, CHAR_32_SPACES);
          gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtSabreTip, resultStr.c_str());
          gslc_ElemSetTxtCol(&m_gui, m_pElemOutTxtSabreTip, GSLC_COL_YELLOW);
          Serial.printf("TestSabreTip set text 7.%d %s %ld pin2d %d pin2a %d\n", secs, resultStr.c_str(), millis(), pin2d, pin2a);
        }
        //gslc_Update(&m_gui);
      }
      
    }

    digitalWrite(PIN_ORANGE_THREE_C,LOW); 

    gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxTip,wasPressed ? GSLC_COL_GREEN : GSLC_COL_RED);

    gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxtSabreTip, wasPressed ? "Touch" : "No touch");

    Serial.printf("TestSabreTip exiting\n");
}

void TestToGND()
{
  gslc_ElemXCheckboxSetColour(&m_gui, m_pElemCBCheckBoxGND, GSLC_COL_BLUE);
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxGND, true);
}
void InitPageElements (gslc_tsElemRef*  elemShort, gslc_tsElemRef*  elemTip, gslc_tsElemRef*  elemGND)
{
  Serial.printf("InitPageElements\n");
  gslc_ElemSetTxtStr(&m_gui, elemShort, "No Short");
  gslc_ElemSetTxtStr(&m_gui, elemTip, "Not Tested");
  gslc_ElemSetTxtStr(&m_gui, elemGND, "No Short");
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxShort, false);
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxGND, false);
  gslc_ElemXCheckboxSetState(&m_gui, m_pElemCBCheckBoxTip, false);

  testStage = 0;
}
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
  int targetPage = -1;
  gslc_tsElemRef* elemShort = NULL;
  gslc_tsElemRef* elemTip = NULL;
  gslc_tsElemRef* elemGND = NULL;

  Serial.printf("CbBtnCommon() elemID %d eTouch %d x %d y%d\n", pElem->nId, eTouch, nX, nY);

  if ( eTouch == GSLC_TOUCH_DOWN_IN ) 
  {     // From the element's ID we can determine which button was pressed.
    currentPage =  gslc_GetPageCur(&m_gui);
    switch (pElem->nId) 
    {
//<Button Enums !Start!>
      case E_ELEM_BTN_EPEE:
        targetPage = E_PG_EPEE;
        elemShort = m_pElemOutTxtEpeeShort;
        elemTip = m_pElemOutTxtEpeeTip;
        elemGND = m_pElemOutTxtEpeeGND;
        break;
      case E_ELEM_BTN_FOIL:
        targetPage = E_PG_FOIL;
        elemShort = m_pElemOutTxtFoilShort;
        elemTip = m_pElemOutTxtFoilTip;
        elemGND = m_pElemOutTxtFoilGND;
       break;
      case E_ELEM_BTN_SABRE:
        targetPage = E_PG_SABRE;
        elemShort = m_pElemOutTxtSabreShort;
        elemTip = m_pElemOutTxtSabreTip;
        elemGND = m_pElemOutTxtSabreGND;
        break;
//<Button Enums !End!>
      default:
        break;
    }
    if (currentPage != targetPage)  //page has changed
    {
      InitPageElements(elemShort, elemTip, elemGND);
      gslc_SetPageCur(&m_gui, targetPage);
      currentPage = targetPage;
      testStage = 0;
    }
    else
    {
       Serial.printf("currentPage == targetPage ************ testTipStage = %d ************ testStage %d\n", testTipStage, testStage);  
      if (testStage == 0)
        {
          Serial.printf("calling TestForShort\n");
          TestForShort(elemShort);
          testStage = 1;
        }
      else 
        if (testStage == 1)
          {
            Serial.printf("************ testTipStage = %d ************ testStage %d\n", testTipStage, testStage );  
            if (testTipStage < 1) // not running
              {
                Serial.printf("giving Tip sem\n");
                testTipStage = 0;
                xSemaphoreGive(xTipSemaphore);
                Serial.printf("************ TestTipStage = %d ************ testStage %d\n", testTipStage, testStage );  
              }
            Serial.printf("************* testTipStage = %d ************  testStage %d\n", testTipStage, testStage );  
            if (testTipStage == 2)
              {
                testStage = 2;
                testTipStage = 0;
              }
          }  
          else
            if (testStage == 2)
              {
                TestToGND();
                testStage = 0;
              }  
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  if (pElemRef == NULL) {
    return false;
  }
  
  //boolean bChecked = gslc_ElemXCheckboxGetState(pGui,pElemRef);

  // Determine which element issued the callback
  switch (pElem->nId) {
//<Checkbox Enums !Start!>

    case E_ELEM_CHECK_SHORT:
      break;
    case E_ELEM_CHECK_TIP:
      break;
    case E_ELEM_CHECK_GND:
      break;
//<Checkbox Enums !End!>
    default:
      break;
  } // switch
  return true;
}
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
void monitorTipTask (void *arg)
{
  Serial.printf("starting monitorTipTask\n");
  while(1)
  {
    Serial.printf("waiting for semaphore in monitorTipTask\n");
    if(xSemaphoreTake(xTipSemaphore, portMAX_DELAY))
    {
      Serial.printf("got semaphore in monitorTipTask %d\n", testTipStage);
      testTipStage = 1;
      Serial.printf("Received Message [%d] %d\n", xTaskGetTickCount(), testTipStage);
       switch( currentPage)
           {
             case  E_PG_EPEE:
                TestEpeeTip();
                break;
            case E_PG_FOIL:
                TestFoilTip();
                break;
            case E_PG_SABRE:
                TestSabreTip();
                break;
            default:
                Serial.println("XXXXXXXXXXXXXXXXXXXXX No currentPage in monitorTipTask XXXXXXXXXXXXXXXXXXXXXXXX ");
                break;
           }
        testTipStage = 2;
        Serial.printf("completed monitorTipTask %d\n", testTipStage); 
        //xSemaphoreGive(xTipCompletionSemaphore);
    }
  }
}
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
  xTipSemaphore = xSemaphoreCreateBinary();
  //xTipCompletionSemaphore = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(
                    monitorTipTask,   /* function that implements the task */
                    "monitorTipTask", /* Task name */
                    10000,      /* number of words to be allocated on stack */
                    NULL,       /* input parameter for the task (may be NULL) */
                    1,          /* task priority (0 to N) */
                    &xTipTaskHandle,       /*reference for the task (may be NULL) */
                    0);         /* Kernel core that will execute the task */
                                //Both the SETUP and the main functions of the LOOP are executed with a priority of 1 and in core 1.

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

