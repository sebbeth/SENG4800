// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "WindowsApplication.h"
#include "Windows/WindowsSystemIncludes.h"
#include "AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>
/**
 * 
 */
class HVCCC2_API FileDialog
{
public:
	FileDialog(void);

	TCHAR* DefaultExtension;
	TCHAR* FileName;
	LPCWSTR Filter;
	int FilterIndex;
	int Flags;
	TCHAR* InitialDir;
	HWND Owner;
	TCHAR* Title;

	bool ShowOpenFileDialog();
	bool ShowSaveFileDialog();
};