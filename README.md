# pith
Zero to one Nucleo — HAL 없이 레지스터부터 만드는 STM32 베어메탈 RTOS
-----
#### 구현 내용
- **클럭**: HSI + PLL로 36MHz 설정, GPIO/AFIO/EXTI/USART 클럭까지 전부 레지스터 직접 조작 (HAL 미사용)
- **스케줄러**: SysTick 기반 preemptive round-robin + priority 스케줄링. `SVC_Handler`가 첫 태스크를 부팅하고, `PendSV_Handler`가 실제 컨텍스트 스위칭(R4-R11 저장/복원, PSP 스왑) 담당
- **태스크 관리**: TCB 풀 기반 태스크 생성/관리, `task_delay`로 voluntary blocking, 스택 오버플로 캐너리(canary)로 태스크별 스택 보호
- **GPIO/EXTI**: 버튼 인터럽트(EXTI15_10)로 LED 토글 및 UART 로그 트리거
- **UART**: USART2 register-level TX 드라이버 (`usart2_send_char`/`usart2_send_string`)
- **동기화**: IRQ masking 기반 spinlock mutex(`mutex_lock`/`mutex_unlock`)로 태스크·ISR이 공유하는 UART 송신 자원을 보호

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
<br>
