# HDLc
Michael Leocádio @ 2015

[![C++](https://img.shields.io/static/v1?label=&message=C%2B%2B&color=%231E40AF&logo=C%2B%2B)](https://)

[![Status - Archived](https://img.shields.io/badge/Release-1.1.0-darkgreen)](https://)

[![Status - Archived](https://img.shields.io/badge/Status-Active-green)](https://)

- **Description**<br>
Very simple tray indicator for hard drive read/write activity (for computers lacking the chassis LED)

- **Reasoning**<br>
Since my desktop days (2000-2014) I used to rely on the HD LED 🚨 on the hardware chassis to know if the system was hung or just heavily working on something. However, back in 2015, I was using a very weak laptop (with a dinosaur HDD 🦕) that lacked that external indicator, so it annoyed me a lot not to know if the PC was frozen or if I should just wait; when the light is constantly on or blinking a lot it means heavy disk operation is being done, otherwise an unresponsive system and a turned off LED means the system certainly crashed, so I developed this very simple (not even an exit button 😅) utility to simulate the HD LED as a tray icon indicator.

- **Usage / Features**<br>
Run the *Install.cmd* (as Admin) and it will automatically add the executable to %windir% and PC initialization, or just run *HDLc.exe* to test drive it.<br>It does not have an exit button (as for the nature of the application, should it?). I made the tray icon light/dark theme agnostic.
