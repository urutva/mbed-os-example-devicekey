/*
* Copyright (c) 2018 ARM Limited. All rights reserved.
* SPDX-License-Identifier: Apache-2.0
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "mbed.h"
#include "DeviceKey.h"

//print a unsigned char buffer in hex format
void print_buffer(unsigned char *buf, size_t size)
{
    for (int i = 0; i < size; i++) {
        printf("%02X", buf[i]);
    }
}

//Injection of a dummy key when there is no TRNG
int inject_rot_key()
{
    uint32_t key[DEVICE_KEY_16BYTE / sizeof(uint32_t)];

    memset(key, 0, DEVICE_KEY_16BYTE);
    memcpy(key, "ABCDEF1234567890", DEVICE_KEY_16BYTE);
    int size = DEVICE_KEY_16BYTE;
    DeviceKey& devkey = DeviceKey::get_instance();
    return devkey.device_inject_root_of_trust(key, size);
}

// Entry point for the example
int main()
{
    unsigned char derive_key1 [DEVICE_KEY_32BYTE];
    unsigned char derive_key2 [DEVICE_KEY_32BYTE];
    unsigned char salt1[] = "SALT1 ----- SALT1 ------ SALT1";
    unsigned char salt2[] = "SALT2 ----- SALT2 ------ SALT2";
    int ret = DEVICEKEY_SUCCESS;

    printf("\n--- Mbed OS DeviceKey example ---\n");

    //DeviceKey is a singleton
    DeviceKey& devkey = DeviceKey::get_instance();

#if not defined(DEVICE_TRNG)

    //If TRNG is not available it is a must to inject the ROT before the first call to derived key method.
    printf("\n--- No TRNG support for this device. injecting ROT. ---\n");
    ret = inject_rot_key();
    if (DEVICEKEY_SUCCESS != ret && DEVICEKEY_ALREADY_EXIST != ret) {
        printf("\n--- Error, injection of ROT key has failed with status %d ---\n", ret);
        return -1;
    }

    if ( DEVICEKEY_ALREADY_EXIST == ret ) {
        printf("\n--- ROT Key already exist in the persistent memory. ---\n", ret);
    } else {
        printf("\n--- ROT Key injected and stored in persistent memory. ---\n", ret);
    }

#endif

    printf("\n--- Using the following salt for key derivation: %s ---\n", salt1);

    //16 byte key derivation.
    printf("--- First call to derive key, requesting derived key of 16 byte ---\n");
    ret = devkey.device_key_derived_key(salt1, sizeof(salt1), derive_key1, DEVICE_KEY_16BYTE);
    if (DEVICEKEY_SUCCESS != ret) {
        printf("\n--- Error, derive key failed with error code %d ---\n", ret);
        return -1;
    }

    printf("--- Derived key1 is: \n");
    print_buffer(derive_key1, DEVICE_KEY_16BYTE);
    printf("\n");

    //16 byte key derivation with the same salt should result with the same derived key.
    printf("\n--- Second call to derived key with the same salt. ---\n");
    ret = devkey.device_key_derived_key(salt1, sizeof(salt1), derive_key2, DEVICE_KEY_16BYTE);
    if (DEVICEKEY_SUCCESS != ret) {
        printf("\n--- Error, derive key failed with error code %d ---\n", ret);
        return -1;
    }

    printf("--- Derived key2 should be equal to key1 from the first call. key2 is: \n");
    print_buffer(derive_key2, DEVICE_KEY_16BYTE);
    printf("\n");

    if (memcmp(derive_key1, derive_key2, DEVICE_KEY_16BYTE) != 0) {
        printf("--- Error, first key and second key do not match ---\n");
        return -1;
    } else {
        printf("--- Keys match ---\n");
    }

    printf("\n--- Using the following salt for key derivation %s ---\n", salt2);

    //16 byte key derivation with the different salt should result with new derived key.
    ret = devkey.device_key_derived_key(salt2, sizeof(salt2), derive_key1, DEVICE_KEY_16BYTE);
    if (DEVICEKEY_SUCCESS != ret) {
        printf("\n--- Error, derive key failed with error code %d ---\n", ret);
        return -1;
    }

    printf("--- Third call to derive key with the different salt should result with a new derived key1: \n");
    print_buffer(derive_key1, DEVICE_KEY_16BYTE);
    printf("\n");

    if (memcmp(derive_key1, derive_key2, DEVICE_KEY_16BYTE) == 0) {
        printf("--- Error, first key and second key do not match ---\n");
        return -1;
    } else {
        printf("--- Keys not match ---\n");
    }

    //32 byte key derivation.
    printf("\n--- 32 byte key derivation example. ---\n");
    ret = devkey.device_key_derived_key(salt2, sizeof(salt2), derive_key2, DEVICE_KEY_32BYTE);
    if (DEVICEKEY_SUCCESS != ret) {
        printf("\n--- Error, derive key failed with error code %d ---\n", ret);
        return -1;
    }

    printf("--- 32 byte derived key is: \n");
    print_buffer(derive_key2, DEVICE_KEY_32BYTE);
    printf("\n");

    printf("\n--- Mbed OS DeviceKey example done. ---\n");

    return 0;
}
