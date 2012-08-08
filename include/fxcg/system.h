#ifdef __cplusplus
extern "C" {
#endif

// This adds in syscalls for interfacing with the OS

void SetAutoPowerOffTime(int duration); // in minutes
void SetBacklightDuration(char duration); // in half-minutes

int GetAutoPowerOffTime();
char GetBacklightDuration();

int GetMainBatteryVoltage(int one);
#ifdef __cplusplus
}
#endif
