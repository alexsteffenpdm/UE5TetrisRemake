#include "Utils/SuppressableLogging.h"

TAutoConsoleVariable<bool> CVarSuppressFuncLogs(
	TEXT("SuppressableLoggingMacros.bSuppressFuncLogs"),
	false,
	TEXT("If true will suppress logs of functions defined via \"SuppressableLoggingMacros.SuppressableFuncNames\""),
	ECVF_Default
);

TAutoConsoleVariable<bool> CVarCheckPartialFuncNameOverlap(
	TEXT("SuppressableLoggingMacros.bCheckPartialFuncNameOverlap"),
	true,
	TEXT("If true will also supress logs in function when the functions name overlaps partially (e.g. if \"SuppressableLoggingMacros.SuppressableFuncNames\" contains \"Spawn\", then \"SpawnActor\" will also be suppressed)"),
	ECVF_Default
);

TAutoConsoleVariable<FString> CVarSuppressableFuncNames(
	TEXT("SuppressableLoggingMacros.SuppressableFuncNames"),
	FString(""),
	TEXT("Specifies which functions won't be logged when \"SuppressableLoggingMacros.bSuppressFuncLogs\" is enabled"),
	ECVF_Default
);

bool GetSuppressFuncLogsStatus() {
	return CVarSuppressFuncLogs.GetValueOnGameThread();
}

bool GetCheckPartialFuncNameOverlap()
{
	return CVarCheckPartialFuncNameOverlap.GetValueOnGameThread();
}


TArray<FString> GetSuppressableFuncNames() {
	TArray<FString> Out;
	CVarSuppressableFuncNames.GetValueOnGameThread().ParseIntoArray(Out, TEXT(","), true);
	return Out;
}

bool ShouldSuppressFunc(FString InFunc)
{
	if (GetCheckPartialFuncNameOverlap())
	{
		for (FString FuncName : GetSuppressableFuncNames())
		{
			if (InFunc.Contains(FuncName))
			{
				return true;
			}
		}
	}
	return GetSuppressableFuncNames().Contains(InFunc);
}