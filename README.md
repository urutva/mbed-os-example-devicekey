![](./resources/official_armmbed_example_badge.png)
# mbed-os-example-devicekey

Device key example for Mbed OS

## Getting started with DeviceKey ##

This is an example of an application that uses the DeviceKey APIs. 
The application injects a dummy root of trust (ROT) if true random number generator (TRNG) is not avalable. The application also invoke the derive key API several times in diffrent conditions and print the result. 

## Required hardware
* An mbed-os supported development board.
* A micro-USB cable.

**NOTE:** Currently this application defines settings only for K66F board. Please refer to [Storage Configuration](https://os.mbed.com/docs/mbed-os/latest/reference/storage.html) from Mbed OS documentation as the DeviceKey requires KVStore to be configured.

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

## License and contributions

The software is provided under Apache-2.0 license. Contributions to this project are accepted under the same license. Please see [contributing.md](./CONTRIBUTING.md) for more info.

This project contains code from other projects. The original license text is included in those source files. They must comply with our [license guide](https://os.mbed.com/docs/mbed-os/v6.2/contributing/license.html)


