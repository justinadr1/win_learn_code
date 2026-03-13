#include <windows.h>
#include <stdio.h>
#include <string.h>

void RunChild(const char* type, HANDLE hIn, HANDLE hOut) 
{
    char buffer[256] = {0};
    char response[256] = {0};
    DWORD bytesRead, bytesWritten;

    printf("[%s] Waiting for instructions...\n", type);
    
    if (ReadFile(hIn, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        printf("[%s] Parent said: \"%s\"\n", type, buffer);

        if (strstr(buffer, "RENDER")) 
        {
            strcpy(response, "GPU: Frames rendered at 60fps.");
        }
        else if (strstr(buffer, "CALCULATE")) 
        {
            strcpy(response, "WORKER: Calculation complete. Result: 42.");
        } 
        else 
        {
            strcpy(response, "CHILD: Message received, but no command recognized.");
        }

        WriteFile(hOut, response, strlen(response) + 1, &bytesWritten, NULL);
    }

    printf("[%s] Task finished. Press Enter to exit.\n", type);
    getchar();
}

int main(int argc, char* argv[]) {
    
    // child process entry
    if (argc > 2) 
    {
        HANDLE hIn = (HANDLE)atoi(argv[2]);
        HANDLE hOut = (HANDLE)atoi(argv[3]);
        if (strstr(argv[1], "--type=worker")) 
            RunChild("WORKER", hIn, hOut);
        else if (strstr(argv[1], "--type=gpu")) 
            RunChild("GPU", hIn, hOut);
        return 0;
    }

    /*
        hW = worker
        hG = gpu
        In = inbound to the child (parent writes, child reads)
        Out = outbound from the child (child writes, parent reads)
        R = read
        W = write
    */
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hW_In_R, hW_In_W;   
    HANDLE hW_Out_R, hW_Out_W; 
    HANDLE hG_In_R, hG_In_W;   
    HANDLE hG_Out_R, hG_Out_W; 

    CreatePipe(&hW_In_R, &hW_In_W, &sa, 0);
    CreatePipe(&hW_Out_R, &hW_Out_W, &sa, 0);
    CreatePipe(&hG_In_R, &hG_In_W, &sa, 0);
    CreatePipe(&hG_Out_R, &hG_Out_W, &sa, 0);

    // launch child processes
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION piW = {0}, piG = {0};
    char cmdW[512], cmdG[512];

    sprintf(cmdW, "%s --type=worker %d %d", argv[0], (int)hW_In_R, (int)hW_Out_W);
    sprintf(cmdG, "%s --type=gpu %d %d", argv[0], (int)hG_In_R, (int)hG_Out_W);

    CreateProcess(NULL, cmdW, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piW);
    CreateProcess(NULL, cmdG, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piG);

    DWORD written, read;
    char reply[256];

    printf("[MAIN] Sending commands...\n");
    WriteFile(hW_In_W, "CALCULATE_PI", 12, &written, NULL);
    WriteFile(hG_In_W, "RENDER_TRIANGLE", 10, &written, NULL);

    ReadFile(hW_Out_R, reply, sizeof(reply), &read, NULL);
    printf("[MAIN] Worker replied: %s\n", reply);

    ReadFile(hG_Out_R, reply, sizeof(reply), &read, NULL);
    printf("[MAIN] GPU replied: %s\n", reply);

    printf("[MAIN] All replies received. Press Enter to exit.\n");
    getchar();

    return 0;
}