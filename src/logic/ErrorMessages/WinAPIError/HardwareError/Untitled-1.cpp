#include <windows.h>
#include <sddl.h>
#include <iostream>

// Helper function to print individual control flag states
void InspectControlFlags(SECURITY_DESCRIPTOR_CONTROL control)
{
    std::cout << "\n--- Security Descriptor Control Flags ---\n";

    std::cout << "Self-Relative Format:  "
              << ((control & SE_SELF_RELATIVE) ? "YES" : "NO (Absolute)") << "\n";

    std::cout << "DACL Present:          "
              << ((control & SE_DACL_PRESENT) ? "YES" : "NO (Null DACL / No Access Control)") << "\n";

    if (control & SE_DACL_PRESENT)
    {
        std::cout << "DACL Defaulted:        "
                  << ((control & SE_DACL_DEFAULTED) ? "YES" : "NO") << "\n";
        std::cout << "DACL Protected:        "
                  << ((control & SE_DACL_PROTECTED) ? "YES" : "NO") << "\n";
        std::cout << "DACL Auto-Inherited:   "
                  << ((control & SE_DACL_AUTO_INHERITED) ? "YES" : "NO") << "\n";
    }

    std::cout << "SACL Present: 
    
    "
              << ((control & SE_SACL_PRESENT) ? "YES" : "NO") << "\n";

    if (control & SE_SACL_PRESENT)
    {
        std::cout << "SACL Protected:        "
                  << ((control & SE_SACL_PROTECTED) ? "YES" : "NO") << "\n";
        std::cout << "SACL Auto-Inherited:   "
                  << ((control & SE_SACL_AUTO_INHERITED) ? "YES" : "NO") << "\n";
    }

    std::cout << "RM Control Valid:      "
              << ((control & SE_RM_CONTROL_VALID) ? "YES" : "NO") << "\n";
}

int main()
{
    HANDLE hProcess = GetCurrentProcess();
    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD dwSizeNeeded = 0;

    // Step 1: Query the required buffer size for the process security descriptor
    GetKernelObjectSecurity(
        hProcess,
        DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
        NULL,
        0,
        &dwSizeNeeded);

    DWORD dwError = GetLastError();
    if (dwError != ERROR_INSUFFICIENT_BUFFER)
    {
        std::cerr << "GetKernelObjectSecurity failed to size buffer. Error: " << dwError << "\n";
        return 1;
    }

    // Step 2: Allocate raw heap memory for the Security Descriptor
    pSD = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeNeeded);
    if (pSD == NULL)
    {
        std::cerr << "Failed to allocate memory for Security Descriptor.\n";
        return 1;
    }

    // Step 3: Retrieve the actual Security Descriptor
    if (!GetKernelObjectSecurity(
            hProcess,
            DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
            pSD,
            dwSizeNeeded,
            &dwSizeNeeded))
    {
        std::cerr << "GetKernelObjectSecurity failed. Error: " << GetLastError() << "\n";
        HeapFree(GetProcessHeap(), 0, pSD);
        return 1;
    }

    // Step 4: Variables to receive control flags and revision
    SECURITY_DESCRIPTOR_CONTROL sdControl = 0;
    DWORD dwRevision = 0;

    // Step 5: Call GetSecurityDescriptorControl
    if (GetSecurityDescriptorControl(pSD, &sdControl, &dwRevision))
    {
        std::cout << "Successfully retrieved Security Descriptor Control.\n";
        std::cout << "Security Descriptor Revision: " << dwRevision << "\n";
        std::cout << "Raw Control Bitmask (HEX):   0x" << std::hex << sdControl << std::dec << "\n";

        // Step 6: Interpret the retrieved flags
        InspectControlFlags(sdControl);
    }
    else
    {
        std::cerr << "GetSecurityDescriptorControl failed. Error: " << GetLastError() << "\n";
    }

    // Step 7: Clean up heap memory
    HeapFree(GetProcessHeap(), 0, pSD);
    return 0;
}