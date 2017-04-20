#include <fstream>
#include <string>
#include <unistd.h> /* sleep in main() */

/* Beaglebone Black LED controller */
namespace BBBLedController
{
    /* LED */
    class BBBLed
    {
    private:
        /* Sysfs class path */
        class Path
        {
        public:
            static std::string brightness(int num)
            { return ("/sys/class/leds/beaglebone:green:usr" + std::to_string(num) + "/brightness"); }

            static std::string trigger(int num)
            { return ("/sys/class/leds/beaglebone:green:usr" + std::to_string(num) + "/trigger"); }
        };

        std::string trigger;    /* Trigger */
        const int num;          /* LED number (0 - 3) */

    public:
        static const int on = 255;  /* LED brightness, on == 255 */
        static const int off = 0;   /* LED brightness, off == 0 */

        BBBLed(int num)
        : num(num)
        { TriggerBackup(); }

        ~BBBLed(void)
        { TriggerRestore(); }

        void TriggerBackup(void)
        {
            std::getline(std::ifstream(Path::trigger(num)), trigger);   /* backup the original trigger state */
            std::ofstream(Path::trigger(num))               /* release the trigger */
                << "[none] rc-feedback kbd-scrolllock kbd-numlock kbd-capslock kbd-kanalock kbd-shiftlock kbd-altgrlock kbd-ctrllock kbd-altlock kbd-shiftllock kbd-shiftrlock kbd-ctrlllock kbd-ctrlrlock nand-disk usb-gadget usb-host mmc0 mmc1 timer oneshot heartbeat backlight gpio default-on";
        }

        void TriggerRestore(void)
        {
            std::ofstream(Path::trigger(num)) << trigger;   /* restore the original trigger state */
        }

        /* Turn on the LED */
        void On(void)
        { std::ofstream(Path::brightness(num)) << on; }

        /* Turn off the LED */
        void Off(void)
        { std::ofstream(Path::brightness(num)) << off; }
    };
}

int
main(void)
{
    BBBLedController::BBBLed led0(0), led1(1), led2(2), led3(3);

    //while(true)
    for(int i = 0; i < 10; ++i)
    {
        led0.Off();
        led1.Off();
        led2.Off();
        led3.Off();
        usleep(500000);

        led0.On();
        led1.On();
        led2.On();
        led3.On();
        usleep(500000);
    }

    return 0;
}
