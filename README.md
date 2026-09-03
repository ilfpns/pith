# pith
Zero to one Nucleo — HAL 없이 레지스터부터 만드는 STM32 베어메탈 RTOS
-----
#### Data sheet
[Data sheet 보러가기](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf)

#### TIL
[관련 TIL 보러가기](https://github.com/ilfpns/IL/tree/main/pith)

#### Build & Flash
```
cd firmware
make          # build (elf/bin), build/ 아래 산출물 생성
make flash    # scripts/flash.ps1로 DAPLink 드라이브에 복사 (ST-Link 연결 필요)
make clean    # build/ 정리
```
새 소스 파일을 `src/<module>/`에 추가하면 `firmware/Makefile`의 `SRCS_C`에도 경로를 추가해야 빌드에 포함됩니다.
