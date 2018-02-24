/*

MQTT topics & messages

# Vocabulary

- T : device Type
- N : device Number
- G : device Group
- I : device ID

# From Luciol Bridge to Devices (B2D)

B2D/T/<type>/<cmd>
B2D/N/<number>/<cmd>
B2D/G/<group>/<cmd>
B2D/I/<group>/<cmd>
B2D/all/<cmd>

## Examples

  Topic             |  Message contents  |  Signification
--------------------+--------------------+-------------------------------------------------------------
B2D/T/luciol/app    | 3                  | Switch to 'app' '3' on 'luciol' devices
B2D/N/4/app         | 7                  | Switch to 'app' '7' on device number '4'
B2D/G/1/ambience    | 4                  | Switch to 'ambience' '4' on devices in group '1'
B2D/all/ambience    | 5                  | Switch to 'ambience' '5' on ALL devices
B2D/N/4/resume      |                    | Starts/resume animations till next step on device number '4'
B2D/I/147/locate    |                    | Asks device with ID '147' to come out
--------------------+--------------------+-------------------------------------------------------------

# From Luciol Devices to Bridge (D2B)

D2B/<number>/alive
D2B/<number>/paused

## Examples

  Topic             |  Message contents  |  Signification
--------------------+--------------------+-------------------------------------------------------------
D2B/alive           | 7                  | Device number '7' is alive
D2B/paused          | 4                  | Device number '4' has reached its animation end
--------------------+--------------------+-------------------------------------------------------------
*/

#include "core/Luciol/Display.h"
#include "core/Luciol/LuciolDevice.h"
#include "core/Luciol/AppManager.h"

#include "apps/Text/TextApp.h"
#include "apps/Clock/ClockApp.h"
#include "apps/Gradient/GradientApp.h"

#include "core/Luciol/PropertiesAnimator.h"

// ----------------------------------------------------------------------------
// Setup
// ----------------------------------------------------------------------------


AppManager*   appManager;
Display*      display;
LuciolDevice* luciol;


void setup() {
  Serial.begin(9600);

  appManager = AppManager::get();
  display    = Display::get();

  luciol = new LuciolDevice();
  luciol->init();

  appManager->registerApp("text", new TextApp);

  PropertiesAnimator pa;
  pa.add("x", new Property<int>(250, -2, 3));
  pa.add("opacity", new Property<float>(250, 1.0, 0.0));
  pa.start();

  pa.getFloat("opacity");
}


// ----------------------------------------------------------------------------
// Main loop
// ----------------------------------------------------------------------------


void loop() {
  luciol->loop();
  appManager->loop();
  display->render();
}
