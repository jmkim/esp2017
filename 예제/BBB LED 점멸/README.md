- [문제 읽기]( https://github.com/kdzlvaids/esp2017/blob/master/md/2016%20%EC%9E%84%EB%B2%A0%EB%94%94%EB%93%9C%EC%8B%9C%EC%8A%A4%ED%85%9C%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D%20II%20%EA%B8%B0%EB%A7%90%EA%B3%A0%EC%82%AC.md#문제-1 )

- Make

    ```bash
    $ make
    ```

- BBB LED 점멸

    ```bash
    $ ./bbb_led
    ```

- GPIO LED 점멸

    ```bash
    $ ./gpio_led
    ```

- Make 결과물 제거하기

    ```
    $ make clean
    ```

- 알려진 문제점
    - BBB LED loop 횟수(10회) 점멸 후 trigger가 복구되지 않는 문제
