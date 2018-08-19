// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDialog.h"

#include <algorithm>
#include <string>
//#include "FileOps.h"
#include "FileDialog.h"


bool UOpenDialog::ShowOpenFileDialog(FString InitialDir, FString Title, bool UseFilter, FString& Filepath) {
	FileDialog* dialog = new FileDialog();
	dialog->FilterIndex = 1;
	InitialDir = InitialDir.Replace(TEXT("/"), TEXT("\\"));
	dialog->InitialDir = InitialDir.GetCharArray().GetData(); //cast FString to *TCHAR (not const *TCHAR)
	dialog->Title = Title.GetCharArray().GetData();

	if (UseFilter) {
		dialog->Filter = TEXT("XML Files (*.xml)\0*.xml\0All Files\0*.*\0\0");
	}

	if (dialog->ShowOpenFileDialog()) {
		Filepath = dialog->FileName;
		Filepath = Filepath.Replace(_T("\\"), _T("/"));
		return true;
	}
	return false;
}