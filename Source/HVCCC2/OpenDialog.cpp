// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDialog.h"

#include <algorithm>
#include <string>
//#include "FileOps.h"
#include "FileDialog.h"

using namespace std;

bool UOpenDialog::ShowOpenFileDialog(FString InitialDir, FString Title, bool UseFilter, FString& outputPath) {
	FileDialog* dialog = new FileDialog();
	dialog->FilterIndex = 1;
	InitialDir = InitialDir.Replace(TEXT("/"), TEXT("\\"));
	dialog->InitialDir = InitialDir.GetCharArray().GetData(); //cast FString to *TCHAR (not const *TCHAR)
	dialog->Title = Title.GetCharArray().GetData();

	if (UseFilter) {
		dialog->Filter = TEXT("XML Files (*.xml)\0*.xml\0All Files\0*.*\0\0");
	}

	if (dialog->ShowOpenFileDialog()) {
		FString Filepath = dialog->FileName;
		Filepath = Filepath.Replace(_T("\\"), _T("/"));

		string formatPath = string(TCHAR_TO_UTF8(*Filepath));

		formatPath = formatPath.substr(0, formatPath.find_last_of("\\/"));
		outputPath = FString(formatPath.c_str());

		return true;
	}
	return false;
}

