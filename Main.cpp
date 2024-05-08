#include <string>
#include <Windows.h>
#include <TlHelp32.h>

DWORD find_process_id(const std::wstring& process_name);
void change_process_affinity(DWORD process_id);

int main()
{
    // Fixing Rainbow Six Siege
    change_process_affinity(find_process_id(L"RainbowSix.exe"));

    // End the execution and close the fix
    return 0;
}

DWORD find_process_id(const std::wstring& process_name)
{
    PROCESSENTRY32 process_info{};
    process_info.dwSize = sizeof(process_info);

    // Creating a handle snapshot of current process in execution
    const HANDLE processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    // Returning zero in case the snapshot is invalid
    if (processes_snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    // Checking if the first process is the needed
    Process32First(processes_snapshot, &process_info);
    if (process_name == process_info.szExeFile)
    {
        // Closing the handle
        CloseHandle(processes_snapshot);

        // Returning the pid of the process
        return process_info.th32ProcessID;
    }

    // Checking the remaining processes
    while (Process32Next(processes_snapshot, &process_info))
    {
        if (process_name == process_info.szExeFile)
        {
            // Closing the handle
            CloseHandle(processes_snapshot);

            // Returning the pid of the process
            return process_info.th32ProcessID;
        }
    }

    // Closing the handle
    CloseHandle(processes_snapshot);

    // Returning zero in case the process has not been found
    return 0;
}

void change_process_affinity(const DWORD process_id)
{
    // Return to avoid errors
    if (process_id == 0) return;

    // Creating a handle to manipulate the process
	const HANDLE handle_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

    // Vars to save the process default affinity
	DWORD_PTR dw_process_affinity;
	DWORD_PTR dw_system_affinity;

    // Getting and saving the process default affinity
	GetProcessAffinityMask(handle_process, &dw_process_affinity, &dw_system_affinity);

    // Changing the process cpu affinity to the cpu 0
    SetProcessAffinityMask(handle_process, 1);

    // Waiting 0.25 seconds
    Sleep(250);

    // Restoring the default process cpu affinity
    SetProcessAffinityMask(handle_process,dw_process_affinity);

    // Closing the handle
    CloseHandle(handle_process);
}
