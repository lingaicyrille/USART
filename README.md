# USART (Universal Synchronous/Asynchronous Receiver/Transmitter)  
Asynchronous serial interface to the PC. USART, an acronym for Universal Synchronous/Asynchronous Receiver/Transmitter, is a hardware device and serial communication protocol frequently utilized in microcontrollers and embedded systems to facilitate communication with other devices. Its versatility is evident in its capability to operate in both synchronous and asynchronous modes, accommodating diverse communication requirements.
In synchronous mode, communication is synchronized with a shared clock signal, while asynchronous mode operates without a synchronized clock, utilizing start and stop bits to delineate data boundaries. A notable feature of USART is its support for full-duplex communication, enabling simultaneous data transmission and reception.
Configuration options include setting the baud rate, which determines the communication speed, and defining the data frame format. The data frame typically consists of a start bit, a specified number of data bits, an optional parity bit for error checking, and stop bits. Additionally, USART often incorporates buffered operation, allowing the microcontroller or device to manage data at its own pace.
Beyond its basic functionalities, USART may also be configured with error detection features, such as a parity bit, to enhance data integrity. Its widespread use in microcontrollers underscores its reliability and efficiency in facilitating serial communication with peripherals, sensors, and various devices.


Requires:  
* Explorer 18 Board
* Pickit 3
* PIC18F87J11 Plugin module (PIM)
* USB cable
* PuttY software on the PC
