<!-- Author: Jongmin Kim <jmkim@pukyong.ac.kr> -->
# 2016 임베디드시스템 프로그래밍 II 기말고사
<!-- Notice:
    이 문서는 Markdown 문서입니다.

    Markdown reader (Chrome extension)
        - 다운로드 URL: https://chrome.google.com/webstore/detail/markdown-reader/gpoigdifkoadgajcincpilkjmejcaanc?utm_source=chrome-app-launcher-info-dialog
        - 설치 후 chrome://extensions/ 에서 "Allow access to file URLs"에 체크하세요.
        - 설치가 끝나면 Chrome으로 이 문서를 열어주세요.
-->

## 문제 1
BBB의 P9_13번 핀에 연결된 LED를 0.5초 단위로 점멸하는 C 혹은 C++ 프로그램을 작성하라.

### 참고사항
-   P9 헤더의 13번 핀은 GPIO0_31이며,
    sysfs class의 `/sys/class/gpio/gpio31`로 접근할 수 있다.

### 예상답안

*[예제 보기]( https://github.com/kdzlvaids/esp2017/tree/master/examples/BBB%20LED%20%EC%A0%90%EB%A9%B8 )*

```cpp
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
```


## 문제 2
test_callback.cpp 프로그램에서 inGPIO->waitForEdge(&activateLED, k)로 호출하고 버튼을
k번 누르면 Button pressed라고 출력하고 종료하도록 수정하라. GPIO.cpp에서 기존 코드를
수정하지 말고 2개의 매개변수를 받는 함수 waitForEdge 및 필요한 다른 함수들을 추가하여
해결하라. Button Pressed라는 메시지는 반드시 callback 함수인 activateLED 함수에 의해서
출력되도록 하라.

### 참고사항
-   [`exploringBB/chp06/GPIO/tests` 바로가기]( https://github.com/derekmolloy/exploringBB/tree/master/chp06/GPIO/tests )
-   [exploringBB]( https://github.com/derekmolloy/exploringBB ) 다운로드가 필요하다.

    ```bash
    $ git clone https://github.com/derekmolloy/exploringBB.git
    ```

    또는

    ```bash
    $ wget https://github.com/derekmolloy/exploringBB/archive/master.zip
    $ unzip master.zip
    ```

### test_callback.cpp 프로그램의 소스 코드
```cpp
#include <iostream>
#include <unistd.h>     // for usleep
#include "GPIO.h"

using namespace exploringBB;
using namespace std;

GPIO *outGPIO, *inGPIO; // global pointers

int
activateLED (int var)
{
  outGPIO->streamWrite (HIGH);    // turn on the LED
  cout << "Button Pressed" << endl;
  return 0;
}

int
main ()
{
  if (getuid () != 0)
    {
      cout << "You must run this program as root. Exiting." << endl;
      return -1;
    }

  inGPIO = new GPIO (115);        // button (P9_27)
  outGPIO = new GPIO (49);        // LED    (P9_23)

  inGPIO->setDirection (INPUT);   // button is an input
  outGPIO->setDirection (OUTPUT); // LED is an output

  outGPIO->streamOpen ();         // fast write to LED
  outGPIO->streamWrite (LOW);     // turn the LED off

  inGPIO->setEdgeType (RISING);   // wait for rising edge

  cout << "You have 10 seconds to press the button:" << endl;
  inGPIO->waitForEdge (&activateLED);   // pass the function

  cout << "Listening, but also doing something else..." << endl;
  usleep (10000000);              // allow 10 seconds

  outGPIO->streamWrite (LOW);     // turn off the LED after 10 seconds
  outGPIO->streamClose ();        // shutdown

  return 0;
}
```

### 예상답안

[예상답안]( https://github.com/kdzlvaids/esp2017/tree/master/exam/solution-2016-final-src/02 )


## 문제 3
Ubuntu에서 /dev/mymiscdev라는 이름의 device file을 생성하고, 이 파일에 다음과 같이
하나의 문자를 쓰고 읽는 기능을 제공하는 misc device driver를 mymisc.c 파일로 작성하라.

```bash
$ sudo chmod 777 /dev/mymiscdev
$ cat /dev/mymiscdev
$ echo -n h > /dev/mymiscdev
$ cat /dev/mymiscdev
h                           # (여기서 h가 출력되고 줄이 바뀌지 않아도 됨)
$ echo -n k > /dev/mymiscdev
$ cat /dev/mymiscdev
k
```

### 예상답안

```c
```
