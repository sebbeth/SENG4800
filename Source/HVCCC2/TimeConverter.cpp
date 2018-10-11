// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeConverter.h"
#include <math.h>

#include <iostream>
#include <string>

using namespace std;

bool UTimeConverter::ConvertTime(bool totalTime, float hoursIn, float timeOffset, int& hoursOut, int& daysOut, int& weeksOut, FString& outputWD, FString& outputHM) {
	hoursOut = 0;
	daysOut = 0;
	weeksOut = 0;

	float hvcccTime = hoursIn; //for debug purposes only.

	hoursIn = hoursIn + timeOffset;
	
	//Convert hoursIn to the corresponding variables
	if (hoursIn > 24.0) {
		//Convert to days
		daysOut = hoursIn / 24.0;
		hoursOut = fmod(hoursIn, 24.0);
	}
	else {
		hoursOut = hoursIn;
	}

	if (daysOut >= 7.0) {
		weeksOut = daysOut / 7.0;
		daysOut = fmod(daysOut, 7.0);
	}

	double intpart;

	float minutesOut = modf(hoursIn, &intpart) * 60;

	//Cast hoursOut to a string
	FString hoursOutStr = "";
	hoursOutStr.AppendInt(hoursOut);

	//Cast minutesOut to a string
	FString minutesOutStr = "";
	minutesOutStr.AppendInt(minutesOut);

	//Prepend the 0 if 1 digit
	hoursOutStr = prepend(hoursOutStr);
	//Prepend the 0 if 1 digit
	minutesOutStr = prepend(minutesOutStr);

	//set string to empty
	outputWD = "";
	outputHM = "";

	//Format the output

	outputWD = "Week: ";
	outputWD.AppendInt(weeksOut);
	outputWD.Append(", ");


	outputWD.Append("Day: ");
	outputWD.AppendInt(daysOut);

	string hoursInString = to_string(hvcccTime);

	FString hoursInStr = "";
	hoursInStr.Append(FString(hoursInString.c_str()));


	if (!totalTime) {
		outputHM.Append(hoursOutStr);
		outputHM.Append(":");
		outputHM.Append(minutesOutStr);
		outputHM.Append("  HVCCC: ");
		outputHM.Append(hoursInStr);
	}
	else {
		outputWD.Append("   ");
		outputWD.Append(hoursOutStr);
		outputWD.Append(":");
		outputWD.Append(minutesOutStr);
	}

	return true;
}


FString UTimeConverter::prepend(FString input) {
	FString output = "0";

	if (input.Len() == 1) 
		output.Append(input);
	else 
		output = input;

	return output;
}