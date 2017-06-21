#include <fstream>
#include <string>
#include <unistd.h> /* sleep in main() */

/* Beaglebone Black LED controller */
namespace BBBLedController
{
    /* LED */
    class GPIOLed
    {
    private:
        /* Sysfs class path */
        class Path
        {
        public:
            static std::string value(int num)
            { return ("/sys/class/gpio/gpio" + std::to_string(num) + "/value"); }

            static std::string direction(int num)
            { return ("/sys/class/gpio/gpio" + std::to_string(num) + "/direction"); }
        };

        const int num;      /* GPIO number */

    public:
        static const int on = 255;  /* LED brightness, on == 255 */
        static const int off = 0;   /* LED brightness, off == 0 */

        GPIOLed(int num)
        : num(num)
        {}

        ~GPIOLed(void)
        {}

        /* Set direction in */
        void SetDirectionIn(void)
        { std::ofstream(Path::direction(num)) << "in"; }

        /* Set direction out */
        void SetDirectionOut(void)
        { std::ofstream(Path::direction(num)) << "out"; }

        /* Turn on the LED */
        void On(void)
        {
            SetDirectionOut();
            std::ofstream(Path::value(num)) << on;
        }

        /* Turn off the LED */
        void Off(void)
        {
            SetDirectionOut();
            std::ofstream(Path::value(num)) << off;
        }
    };
}

int
main(void)
{
    BBBLedController::GPIOLed led31(31);    /* P9.13 == GPIO0_31 */

    while(true)
    {
        led31.Off();
        usleep(500000);

        led31.On();
        usleep(500000);
    }

    return 0;
}
