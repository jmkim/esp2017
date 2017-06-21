<!-- Author: Jongmin Kim <jmkim@pukyong.ac.kr> -->
# 2012 임베디드 시스템 프로그래밍 기말시험
<!-- Notice:
    이 문서는 Markdown 문서입니다.

    Markdown reader (Chrome extension)
        - 다운로드 URL: https://chrome.google.com/webstore/detail/markdown-reader/gpoigdifkoadgajcincpilkjmejcaanc?utm_source=chrome-app-launcher-info-dialog
        - 설치 후 chrome://extensions/ 에서 "Allow access to file URLs"에 체크하세요.
        - 설치가 끝나면 Chrome으로 이 문서를 열어주세요.
-->

## 문제 1
문자열을 복사하여 새로운 문자열을 생성하는 함수 duplicate를 작성하라. 가령

```c
p = duplicate(str)
```

은 문자열 str과 동일한 길이의 문자열을 저장할 메모리를 동적으로 할당받은 후 문자열
str의 내용을 할당된 메모리에 복사하고 그 주소를 반환한다. 동적 메모리 할당이 실패할
경우 null pointer를 반환한다.

### 예상답안

```c
#include <stdlib.h>
#include <string.h>

char *
duplicate(char * in)
{
    char * out = (char *)malloc(strlen(in) + sizeof(char));
    return (out != NULL) ? strcpy(out, in) : NULL;
}
```


## 문제 2
다음 프로그램의 출력은 무엇인가? 또한 왜 그런지 간략히 설명하라.

```c
#include <stdio.h>

int f1(int (*f)(int));
int f2(int I);

int main(void)
{
    printf("Answer: %d\n", f1(f2));
}

int f1(int (*f)(int))
{
    int n=0;
    while ((*f)(n)) n++;
    return n;
}

int f2(int i)
{
    return i * i + i - 12; 
}
```

### 참고사항
위 코드는 다음과 같이 다시 쓸 수 있다.

```c
#include <stdio.h>

int
main(void)
{
    printf("Answer: %d\n", f1());
}

int
f1(void)
{
    int n=0;
    while (n * n + n - 12) n++; /* f2() was inlined. */
    return n;
}
```

### 예상답안
- 출력은 `Answer: 3`이다.
- 설명:

    | `f1`의 `n`값      | `f2`의 `i`값      | `f2`의 반환값     |
    | ----              | ----              | ----              |
    | 1                 | 1                 | -10               |
    | 2                 | 2                 | -6                |
    | 3                 | 3                 | 0                 |

    `f1` 내의 `while`문 조건에서 `f2`의 반환값이 0이 되면 반복으로부터 탈출한다.
    그 다음 줄에서 `f1`은 `n`을 반환하며, 그 값은 3이다.


## 문제 3
`debug.h` 헤더 파일의 내용은 다음과 같다.

```c
#ifdef DEBUG
#define PRINT_DEBUG(n) printf("The value is: %d\n", n)
#else
#define PRINT_DEBUG(n)
#endif
```

`debug.c` 소스 파일의 내용은 다음과 같다. 프로그램의 출력은?

```c
#include <stdio.h>
#define DEBUG
#include "debug.h"

int main(void)
{
    int i=1, j=2, k=3;
#ifdef DEBUG
    printf("Output if DEBUG is defined:\n");
#else
    printf("Output if DEBUG is not defined:\n");
#endif

    PRINT_DEBUG(i);
    PRINT_DEBUG(j);
    PRINT_DEBUG(k);
    PRINT_DEBUG(i+j);
    PRINT_DEBUG(2*i+j-k);

    return 0;
}
```

### 참고사항
전처리기를 거친 후의 코드는 대략 이럴 것이다.

```c
...

int main(void)
{
    int i=1, j=2, k=3;
    printf("Output if DEBUG is defined:\n");

    printf("The value is: %d\n", i);
    printf("The value is: %d\n", j);
    printf("The value is: %d\n", k);
    printf("The value is: %d\n", i+j);
    printf("The value is: %d\n", 2*i+j-k);

    return 0;
}
```

### 예상답안

```bash
The value is: 1
The value is: 2
The value is: 3
The value is: 3
The value is: 1
```


## 문제 4
프로그램은 3개의 소스 파일 `main.c`, `f1.c`, `f2.c`와 두 개의 헤더(header) 파일 `f1.h`,
`f2.h`로 구성된다. 모든 소스 파일들은 `f1.h`를 include하고, `f1.c`와 `f2.c`는 `f2.h`를
include한다. 이 프로그램을 위한 Makefile을 작성하라. 컴파일러는 `gcc`이고 실행파일의
이름은 `demo`라고 가정한다.

### 예상답안

*[예제 보기]( https://github.com/kdzlvaids/esp2017/tree/master/examples/Makefile%20%EC%9E%91%EC%84%B1 )*

```makefile
CC = gcc
LD = gcc
ODIR = .obj
CCFLAGS =
LDFLAGS =

all: demo

demo: main.o f1.o f2.o
	$(LD) -o $@ $^ $(LDFLAGS)

main.o: main.c f1.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

f1.o: f1.c f1.h f2.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

f2.o: f2.c f1.h f2.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o *.d demo
```

## 문제 5
철이는 crosstool-ng라는 툴을 다운로드한 후 매뉴얼을 참고해서 다음과 같이 열심히
cross compilation tool을 빌드하였다.

```bash
$ 소스 다운로드 및 패키지 설치 완료
$ ./bootstrap
$ ./configure --enable-local
$ make
$ make install
$ ./ct-ng arm-unknown-linux-uclibcgnueabi
$ ./ct-ng menuconfig        // 특별한 설정변경 없이 완료
$ ./ct-ng build
```

그리고 신의 도움으로 악명 높은 오류들을 피해 무사히 빌드가 완료되었다. 의기양양한 마음으로
다음과 같이 간단한 hello.c 프로그램을 작성한 후 컴파일을 시도하였다. 하지만 아래와
같은 오류 메시지를 받고 말았다. 뭐가 문제일까? 그리고 어떻게 해야 할까? 빌드 과정에는
아무 문제가 없었다고 가정한다.

```bash
$ gedit hello.c
// hello.c 프로그램 작성

$ arm-unknown-linux-uclibcgnueabi-gcc -o hello hello.c
-bash: arm-unknown-linux-uclibcgnueabi-gcc: command not found
```

### 예상답안
Cross compilation tool의 빌드 된 바이너리들이 위치한 디렉토리를
환경 변수에 추가하지 않고 실행시켰기 때문에 일어난 문제이다.

이 문제는 다음과 비슷한 방법으로 해결할 수 있다.
-   바이너리의 경로를 지정하여 실행한다.

    ```bash
    $ /some/place/bin/arm-unknown-linux-uclibcgnueabi-gcc -o hello hello.c
    ```

-   환경 변수(`$PATH`)에 바이너리들이 위치한 디렉토리를 추가한다.

    ```bash
    $ PATH="/some/place/bin:${PATH}"
    ```

    다만 이 방법은 일회용이다. 셸을 열 때 마다 추가해 주어야 한다.

-   셸이 실행될 때 프롬프트가 열리기 전 먼저 실행되는 `~/.profile` 등의 파일에
    다음과 같이 환경 변수(`$PATH`)를 추가한다.

    ```bash
    $ echo "export PATH=\"/some/place/bin:${PATH}\" >> ~/.profile
    ```


## 문제 6
무사히 크로스 컴파일 툴체인을 빌드한 후 그것을 사용하여 arm versatilepb용 linux
kernel 컴파일을 시도하였다. 커널을 컴파일하기 위해서는 먼저 커널을 설정해야 하므로 다음과
같이 커널 설정을 위한 타겟인 menuconfig를 실행하였다.

```bash
$ menuconfig
```

-   가) 하지만 설정 화면을 살펴보던 철이는 뭔가 이상하다는 것을 발견하였다. 아래 그림과 같이
    x86 어쩌고 하는 항목만 있고 정작 arm 프로세서에 관한 내용을 찾을 수 없는 것이다. 철이는
    뭘 빼먹은 것일까?

    ![menuconfig]( https://github.com/kdzlvaids/esp2017/raw/master/exam/figures/menuconfig.png )

    ### 예상답안

    ```bash
    $ export ARCH="arm"
    $ export CROSS_COMPILE="arm-linux-gnueabihf-"
    $ make versatile_defconfig
    ```

-   나) 철이는 (가) 항목의 문제를 무사히 해결하였다. 하지만 막상 커널을 설정하려니 아는 것이
    많지 않아 너무 막막하다. arm versatilepb 보드를 위해 미리 설정되어 있는 기본 설정값들을
    알 수 있다면 좋을 것이다. 어떻게 하면 될까?

    ### 예상답안

    ```bash
    $ make versatile_defconfig
    $ cat .config # make versatile_defconfig을 통해 설정 된 값(versatilepb의 기본값)이 저장되는 파일
    ```
