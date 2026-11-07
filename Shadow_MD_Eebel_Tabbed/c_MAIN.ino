
// =======================================================================================
//           Main Program Loop - This is the recurring check loop for entire sketch
// =======================================================================================

void loop()
{   
    //Useful to enable with serial console when having controller issues.
    #ifdef TEST_CONROLLER
      testPS3Controller();
    #endif

    //LOOP through functions from highest to lowest priority.

    if ( !readUSB() )
    {
      //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
#if ENABLE_ROS2D2
      // A faulty controller is as good as a lost one: face tracking goes off, so the dome
      // does not turn on its own after a fault.
      domeTrackSetOff(FA_CONTROLLER);
#endif
      printOutput();
      return;
    }
    
#if ENABLE_ROS2D2
    domeTrackCheckController();
    rosReadUsb();
#endif
    footMotorDrive();
    domeDrive();
    marcDuinoDome();
    marcDuinoFoot();
    toggleSettings();
    printOutput();
    
    // If running a custom MarcDuino Panel Routine - Call Function
    if (runningCustRoutine)
    {
       custMarcDuinoPanel();     
    }
    
    // If dome automation is enabled - Call function
#if ENABLE_ROS2D2
    // Not while the Pi is turning the dome (face tracking)
    if (domeAutomation && time360DomeTurn > 1999 && time360DomeTurn < 8001 && domeAutoSpeed > 49 && domeAutoSpeed < 101 && !domeTrackerActive())
#else
    if (domeAutomation && time360DomeTurn > 1999 && time360DomeTurn < 8001 && domeAutoSpeed > 49 && domeAutoSpeed < 101)  
#endif
    {
       autoDome(); 
    }   
}
