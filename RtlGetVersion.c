#include <ntddk.h>

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	// Adding tracing
	DbgPrint("Driver1 driver unloaded!\n");
}

NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	// DriverObject is predefined
	// -> is used to access a pointer to a structure (PDRIVER_OBJECT a.k.a DriverObject points to the DRIVER_OBJECT structure)
	// Accessing DriverUnload member for unload routine
	// Define unload routine before invoking DriverEntry code
	DriverObject->DriverUnload = SampleUnload;

	// Parameters need to be referenced to avoid errors
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	// Calling RtlGetVersion function

	// The RTL_OSVERSIONINFOW structure (which contains the members needed) is defined as lpVersionInformation
	// As best practice, initializing all structure members to 0 before use
	RTL_OSVERSIONINFOW lpVersionInformation = { 0 };

	// "A caller specifies which input structure is being used by setting the dwOSVersionInfoSize member of the structure to the size in bytes of the structure that is used"
	// dwOSVersionInfoSize member must be set to the size of the structure (RTL_OSVERSIONINFOW) before the function call
	// . is used to access a member of a structure directly
	lpVersionInformation.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);

	// RtlGetVersion needs a pointer to the PRTL_OSVERSIONINFOW structure (lpVersionInformation is already an alias to RTL_OSVERSIONINFOW, so using a pointer to lpVersionInformation)
	NTSTATUS getVersion = RtlGetVersion(&lpVersionInformation);

	// Error handling
	if (getVersion == STATUS_SUCCESS)
	{
		// Printing the major version, minor version, and build number of the OS
		// Since RtlGetVersion has ran, we can access the structures members to get the intended results
		DbgPrint("Major version: %d, Minor version: %d, Build Number: %d\n", lpVersionInformation.dwMajorVersion, lpVersionInformation.dwMinorVersion, lpVersionInformation.dwBuildNumber);
	}
	else
	{
		DbgPrint("Error calling RtlGetVersion()!\n");
	}

	// Adding tracing
	DbgPrint("Driver1 driver initialized successfully!\n"); 

	return STATUS_SUCCESS;
}
