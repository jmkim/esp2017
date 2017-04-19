<!-- Author: Jongmin Kim <jmkim@pukyong.ac.kr> -->
# 임베디드 시스템 프로그래밍 QUIZ #2
<!-- Notice:
    이 문서는 Markdown 문서입니다.

    Markdown reader (Chrome extension)
        - 다운로드 URL: https://chrome.google.com/webstore/detail/markdown-reader/gpoigdifkoadgajcincpilkjmejcaanc?utm_source=chrome-app-launcher-info-dialog
        - 설치 후 chrome://extensions/ 에서 "Allow access to file URLs"에 체크하세요.
        - 설치가 끝나면 Chrome으로 이 문서를 열어주세요.
-->

## 문제 1
다음의 bash 스크립트가 하는 일을 구체적으로 설명하라.

```bash
#!/bin/bash

if [ ! -r "$1" ]; then
    echo "Error"
else
    cat "$1"
fi
```

### 참고사항
- `if` expression `-r FILE`은 읽을 수 있는 파일인지를 확인하는 용도이다.

### 예상답안
첫번째 인자의 경로에 해당하는 파일이
읽기가 불가능하면
표준 출력으로 `Error`를 표시하고,
아니면 파일의 내용을 표준 출력으로 출력한다.


## 문제 2
다음의 bash 스크립트가 하는 일을 설명하라.

```bash
#!/bin/bash

if [ -d ~/bin ]; then
    PATH=$PATH:~/bin
fi
```

### 참고사항
- `if` expression `-d FILE`는 디렉토리가 존재하는지 확인하는 용도이다.
- 파일 경로의 `~`는 리눅스나 Unix-like 시스템에서 사용자의 홈 디렉토리를 의미한다.
- `$PATH` 는 리눅스나 Unix-like 시스템에서 환경 변수로서 쓰인다.

### 예상답안
사용자의 홈 디렉토리에 bin이라는 디렉토리가 있으면 환경 변수에 이 디렉토리를 추가한다.


## 문제 3
다음의 bash 스크립트가 하는 일을 설명하라.

```bash
#!/bin/bash

for file in /tmp/*
do
    if [ -f ${file} ]
    then
        if [ -e "${file}.bak" ]
        then
            echo "Error"
        else
            cp "${file}" "${file}.bak"
        fi
    fi
done
```

### 참고사항
- `if` expression `-f FILE`는 평범한 파일이 존재하는지 확인하는 용도이다.
    - 평범하지 않은 파일의 목록
        - 디렉토리
        - Block special file
        - Character special file
        - 심볼릭 링크
        - Named pipe (FIFO)
        - etc..
- `if` expression `-e FILE`는 단순히 파일이 존재하는지 확인하는 용도이다.
- bash에서는 변수 이름을 braces(`{}`)로 감쌀 수 있는데, 변수 이름의 끝을 명시하거나 변수의 확장 제어에 쓰인다.
    - 변수 직후에 문자열을 붙여야 하는 경우
        - `$PATHaaa` : 변수의 이름이 `PATHaaa`
        - `${PATH}aaa` : 변수의 이름은 `PATH`, 변수 바로 뒤에 문자열 `aaa`가 따라붙음

### 예상 답안
`/tmp` 디렉토리에 존재한 모든 파일에 대해
파일이 평범한 파일
(심볼릭 링크나 special file이 아닌 등 특성이 없는 파일)이면,
파일의 이름 뒤에 `.bak` 파일이 있다면
표준 출력으로 `Error`을 출력하고,
없다면 파일 이름 뒤에 `.bak`을 붙여서 파일을 복제한다.
또한 만약 파일이 평범하지 않은 파일이라면 아무 일도 하지 않는다.


## 문제 4
다음의 bash 스크립트가 하는 일을 설명하라.

```bash
#!/bin/bash

for FN in *.bad
do
    mv "${FN}" "${FN%bad}bash"
done
```

### 참고사항
- bash에서는 변수 이름을 braces(`{}`)로 감쌀 수 있는데, 변수 이름의 끝을 명시하거나 변수의 확장 제어에 쓰인다.
    - 변수의 확장 제어 (Parameter substitution)
        - `%`: 단어의 끝에서 match되는 부분을 제거
            - `abcd`에서 `cd` 제거 시 `ab`

### 예상답안
.bad로 끝나는 모든 파일에 대해
파일 이름 맨 끝의 bad를 bash로 바꾼다.


## 문제 5
다음의 bash 스크립트를 실행했을 때 어떻게 출력되는지 경우에 따라 설명하라.

```bash
$ cat testscript.sh
#!/bin/bash

fatal () {
    echo "$0: fatal error:" "$@" >&2
    exit 1
}

if [ $# = 0 ]
then
    fatal not enough arguments
fi
```

### 참고사항
- `$0`는 현재 셸 또는 셸 스크립트의 이름을 의미한다.
    - bash를 `bash`로 실행 시 `$0`는 `bash`
    - bash를 `/bin/bash`로 실행 시 `$0`는 `/bin/bash`
- `$#`는 인자의 개수를 의미한다.
- `$@`는 `$1`부터 시작하여, 모든 인자의 나열을 의미한다. (`$0` 제외)

### 예상답안
testscript.sh를 실행할 때 인자를 준다면 아무 일도 일어나지 않고 종료한다.
만약 인자를 주지 않는다면
`./testscript: fatal error: not enough arguments`
를 표준 오류(stderr)로 출력하고, 종료 상태 1을 반환하며 종료한다.


## 문제 6
다음의 bash 스크립트가 하는 일을 설명하라.

```bash
#!/bin/bash

for SCRIPT in ~/bin/*
do
    if [ -f $SCRIPT -a -x $SCRIPT ]
    then
        $SCRIPT
    fi
done
```

### 참고사항
- **`-a`는 AND 연산자이다.**
    - `-a FILE`은 `-e FILE`
    - `if` expression `-a FILE`은 `-e FILE`과 같다 (파일이 존재하는지 여부를 확인하는 용도).
- `if` expression `-f FILE`는 평범한 파일이 존재하는지 확인하는 용도이다. *[문제3](#참고사항-2) 참조*
- `if` expression `-x FILE`는 실행가능한 파일이 존재하는지 확인하는 용도이다.
- 파일 경로의 `~`는 리눅스나 Unix-like 시스템에서 사용자의 홈 디렉토리를 의미한다.

### 예상답안
사용자의 홈 디렉토리의 bin 디렉토리 내의 모든 파일에 대해
파일이 평범한 파일이자 실행가능한 파일이면
실행한다.


## 문제 7
매개변수로 주어지는 모든 파일들의 permission을 아무나 읽고, 쓰고, 실행할 수 있게
변환하는 스크립트 changebatch.sh을 작성하라. 예를 들어 다음과 같이 실행하면 file1,
file2, file3의 권한이 변경된다.
```bash
$ ./changebatch.sh file1 file2 file3
```

### 예상답안
```bash
#!/bin/bash

# 파일이름에 공백이 포함된 파일도 다루기 위해서,
# $@ 와 $FILE 모두 double-quotes로 감싸야 한다.
for FILE in "$@"
do
    if [ ! -e "$FILE" ]; then
        echo "$FILE : file not exists"
        exit 1
    fi

    chmod 777 "$FILE" # 777 = rwx
done
```


## 문제 8
7번 문제에서 매개변수로 주어진 이름이 파일인지 디렉토리인지 검사하여
파일인 경우에만 권한을 변경하고 디렉토리인 경우에는 권한을 변경하는 대신
적절한 오류 메시지를 출력하도록 스크립트를 작성하라. 예를 들면 다음과 같이 실행된다.
```bash
$ ./changebatch.sh file1 directory1 file2
file1 : done
directory1 : it is a directory
file2 : done
```

### 예상답안
```bash
#!/bin/bash

# 파일이름에 공백이 포함된 파일도 다루기 위해서,
# $@ 와 $FILE 모두 double-quotes로 감싸야 한다.
for FILE in "$@"
do
    if [ ! -e "$FILE" ]; then
        echo "$FILE : file not exists"
        exit 1
    fi

    if [ -d "$FILE" ]; then     # $FILE이 디렉토리인지 검사한다.
        echo "$FILE : it is a directory"
    else
        chmod 777 "$FILE"       # 777 = rwx
        echo "$FILE : done"
    fi
done
```


## 문제 9
7번 문제에서 확장자가 .mp3인 파일만 권한을 변경하도록 수정하라.
예를 들면 다음과 같이 실행된다.
```bash
$ ls
directory1  file1.txt    file2   song1.mp3   song2.mp3
$ ./changebatch.sh *
directory1 : it is a directory
file1.txt : it is not a mp3 file
file2 : it is not a mp3 file
song1.mp3 : done
song2.mp3 : done
```

### 예상답안
```bash
#!/bin/bash

# 파일이름에 공백이 포함된 파일도 다루기 위해서,
# $@ 와 $FILE 모두 double-quotes로 감싸야 한다.
for FILE in "$@"
do
    if [ ! -e "$FILE" ]; then
        echo "$FILE : file not exists"
        exit 1
    fi

    if [ -d "$FILE" ]; then
        echo "$FILE : it is a directory"
    elif [ "$FILE" != *.mp3 ]; then
        echo "$FILE : it is not a mp3 file"
    else
        chmod 777 "$FILE" # 777 = rwx
        echo "$FILE : done"
    fi
done
```


## 문제 10
Linux의 기본 rm 명령으로 파일을 삭제하면 복구하기가 어렵다.
그래서 아래의 예와 같이 파일을 삭제할 경우 정말 삭제할 것인지 물어보도록 만들고 싶다.
가능한 방법을 2가지 설명하라.
```bash
$ rm test.c
remove test.c ?
```

### 예상답안

#### 방법 1: alias
`rm` 명령어에는 모든 파일에 대해 삭제 여부를 물어보는 옵션인 `-i`이 있다.
bash에서는 built-in 명령어인 `alias`를 이용하여
`rm`을 실행하려 할 때 `rm -i`로써 실행되도록 할 수 있다.

```bash
alias rm='rm -i'
```

#### 방법 2: 셸 스크립트 제작
다음과 같은 셸 스크립트를 작성 후
```bash
/bin/rm -i "$@"     # `which rm`
```
이 스크립트의 파일 이름을 "rm"으로 저장하여,
환경 변수(`$PATH`)에 포함 된 위치로
옮기거나 심볼링 링크를 건다.
이 때 `$PATH`에서 이 스크립트의 위치는
실제 `rm` 바이너리의 위치(`/bin/rm`)보다 앞에 놓여야 한다.

```bash
mkdir ~/bin
mv rm ~/bin/
PATH="~/bin/:$PATH"
```

다만, 이 방법에는 치명적인 문제가 있는데,
이 환경 변수를 상속받은 자동화 스크립트가
사용자가 아닌 시스템에 의해서 혹은 비 대화형으로 실행되고 있을 때
이 스크립트가 `rm` 명령어를 수행한다면
접근할 수 없는 프롬프트의 발생으로 인해 그대로 멈출 수 있다.

