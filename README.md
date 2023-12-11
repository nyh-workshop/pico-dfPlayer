# pico-dfPlayerMini

This is a simple library for DFPlayer Mini using the Raspberry Pico.
Currently it does not support reading the responses from the unit.
More features will be added in the future.

## Requirements:
- DFPlayer Mini
- Raspberry Pico SDK 1.4

## References:
- [DFPlayer Mini Manual](https://picaxe.com/docs/spe033.pdf)

## Wiring

Showing a Arduino Nano... :grimacing:  
Basic Concept is the same.

Connection to Raspberry Pi Pico:

- Pico GPIO8 (UART1 TX) -> RX on DFPlayer (Omit 1K resistor)
- Pico GPIO9 (UART1 RX) -> TX on DFPlayer


![circuit-diagram](./Documents/DFPlayer%20Wiring.png)


## GOTCHAs

- None (So far)

## TODO

- Add further fuctionality for the commands
- Add support for response from DFPlayer
- Add support for quering the DFPlayer status

