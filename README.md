# mbed-os-example-devicekey

Device key example for Mbed OS

## Getting started with DeviceKey ##

This is an example of an application that uses the DeviceKey APIs. 
The application injects a dummy root of trust (ROT) if true random number generator (TRNG) is not avalable. The application also invoke the derive key API several times in diffrent conditions and print the result. 

## Required hardware
* An mbed-os supported development board.
* A micro-USB cable.

##  Getting started ##

 1. Import the example.

    ```
    mbed import mbed-os-example-devicekey
    cd mbed-os-example-devicekey
    ```

 2. Compile and generate binary.

    For example, for `GCC`:

    ```
    mbed compile -t GCC_ARM -m <your device>
    ```
   
 3. Open a serial console session with the target platform using the following parameters:

    * **Baud rate:** 9600
    * **Data bits:** 8
    * **Stop bits:** 1
    * **Parity:** None

 5. Copy the application `mbed-os-example-devicekey.bin` in the folder `mbed-os-example-devicekey/BUILD/<TARGET NAME>/<PLATFORM NAME>` onto the target board.

 6. Press the **RESET** button on the board to run the program

 7. The serial console should now display a series of results. 

## Troubleshooting

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.
