#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	RobotDrive Drive; // robot drive system that goes on y
	RobotDrive Slide;
	Joystick DriveJoystick;
	Joystick SlideJoystick;
	Jaguar GripperRotate;
	Jaguar GripperVertical;
	Talon TotePickup;
	Solenoid GripperRet;
	Solenoid GripperExt;
	Joystick GamePad;
	DigitalInput LeftPE1;
	DigitalInput LeftPE2;
	DigitalInput CenterPE;
	DigitalInput RightPE1;
	DigitalInput RightPE2;
	Relay LS;
	Relay LS1;
	Relay LS2;
	Preferences *prefs;


public:

	float gripperX;
	//float gripperY;
	float lefttrigger;
	float righttrigger;
	float drivechangeinY;
	float drivechangeinX;
	float drivejoystickY;
	float drivejoystickX;
	float drivelimitY;
	float drivelimitX;
	float drivelimitedjoystickY;
	float drivelimitedjoystickX;
	int autonmode;





	Robot() :
			Drive(2,3),	// these must be initialized in the same order
			Slide(0,1),
			DriveJoystick(0),		// as they are declared above.
			SlideJoystick(1),
			GripperRotate(6),
			GripperVertical(5),
			TotePickup(4),
			GripperRet(0),
			GripperExt(1),
			GamePad(2),
			LeftPE1(0),
			LeftPE2(1),
			CenterPE(2),
			RightPE1(3),
			RightPE2(4),
			LS(0),
			LS1(1),
			LS2(2)

	{
		Drive.SetExpiration(0.1);
		Slide.SetExpiration(0.1);
		prefs = Preferences::GetInstance();
		autonmode = prefs->GetInt("AutonomousMode",0);


	}




	//void RobotInit(){

		//prefs = Preferences::GetInstance();
		//autonmode = prefs->GetInt("AutonomousMode",0);


	//}

	void Autonomous()
	{

		Drive.SetSafetyEnabled(false);
		Slide.SetSafetyEnabled(false);
		autonmode = 4;

		switch (autonmode){

		case 0:
			Drive.Drive(0.0,0.0);
			Slide.Drive(0.0,0.0);
			break;

		case 1:
			GripperVertical.Set(0.5);
			Wait(0.5);
			GripperVertical.Set(0);
			GripperRet.Set(true);
			Wait (0.75);
			GripperVertical.Set(0.5);
			Wait(1.0);
			GripperVertical.Set(0.0);
			Drive.Drive(0.9,0.0);
			Slide.Drive(-0.4,0.0);
			Wait(2.5);
			Drive.Drive(0.0,0.0);
			Slide.Drive(0.0,0.0);
			break;

		case 2:
			GripperVertical.Set(0.5);
			Wait(0.5);
			GripperVertical.Set(0);
			GripperRet.Set(true);
			Wait (0.75);
			GripperVertical.Set(0.5);
			Wait(1.0);
			GripperVertical.Set(0.0);
			Drive.Drive(-0.5,0.0);
			Wait(1.0);
			Drive.Drive(0.0,0.0);
			Drive.Drive(0.9,0.0);
			Wait(3.0);
			Drive.Drive(0.0,0.0);
			break;



		case 3:
			GripperVertical.Set(0.5);
			Wait(0.5);
			GripperVertical.Set(0);
			GripperRet.Set(true);
			Wait (0.75);
			GripperVertical.Set(0.5);
			Wait(1.0);
			GripperVertical.Set(0.0);
			Drive.Drive(-0.5,0.0);
			Wait(1.0);
			Drive.Drive(0.0,0.0);
			Drive.Drive(0.9,0.0);
			Wait(3.0);
			Drive.Drive(0.0,0.0);
			break;


		case 4:
			Slide.Drive(-0.5,0.0);
			Wait(2.0);
			Slide.Drive(0.0,0.0);
			break;

		case 5:
			Drive.Drive(0.6,0.0);
			Wait(1.0);
			Slide.Drive(-0.2,0.0);
			Wait(1.5);
			Drive.Drive(0.0,0.0);
			Slide.Drive(0.0,0.0);



		}

	}

	void OperatorControl()
	{
		Drive.SetSafetyEnabled(true);
		Slide.SetSafetyEnabled(true);

		while (IsOperatorControl() && IsEnabled())
		{

			drivejoystickY = DriveJoystick.GetY();

			drivejoystickX = DriveJoystick.GetX();

			Drive.ArcadeDrive(-drivejoystickY,-drivejoystickX); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time

			Slide.ArcadeDrive(SlideJoystick.GetX(),0.0); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time


			//gripperY = (-GamePad.GetRawAxis(4));
			gripperX = (GamePad.GetRawAxis(5));
			//if (gripperY > 0.0 && gripperY < 0.3) gripperY = 0;
			//if (gripperY < 0.0 && gripperY > -0.3) gripperY = 0;
			if (gripperX > 0.0 && gripperX < 0.5) gripperX = 0;
			if (gripperX < 0.0 && gripperX > -0.5) gripperX = 0;

			lefttrigger = (GamePad.GetRawAxis(2));
			righttrigger = (GamePad.GetRawAxis(3));

			GripperVertical.Set(gripperX);
			GripperRotate.Set(lefttrigger - righttrigger);

			TotePickup.Set(-GamePad.GetRawAxis(1));

			if (GamePad.GetRawButton(6)) GripperExt.Set(true);
			else if (!GamePad.GetRawButton(6)) GripperExt.Set(false);
			if (GamePad.GetRawButton(5)) GripperRet.Set(true);
			else if (!GamePad.GetRawButton(5)) GripperRet.Set(false);


			if (LeftPE1.Get()) LS.Set(Relay::kOn);
			else if (!LeftPE1.Get()) LS.Set(Relay::kForward);

			if (LeftPE2.Get() && !CenterPE.Get()) LS1.Set(Relay::kForward);
			else if (!LeftPE2.Get() && CenterPE.Get()) LS1.Set(Relay::kReverse);
			else if (LeftPE2.Get() && CenterPE.Get()) LS1.Set(Relay::kOn);
			else if (!LeftPE2.Get() && !CenterPE.Get()) LS1.Set(Relay::kOff);

			if (RightPE2.Get() && !RightPE1.Get()) LS2.Set(Relay::kForward);
			else if (!RightPE2.Get() && RightPE1.Get()) LS2.Set(Relay::kReverse);
			else if (RightPE2.Get() && RightPE1.Get()) LS2.Set(Relay::kOn);
			else if (!RightPE2.Get() && !RightPE1.Get()) LS2.Set(Relay::kOff);

		}

	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
