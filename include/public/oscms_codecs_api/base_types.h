// Copyright (c) 2025 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef OSCMS_CODECS_BASE_TYPES_H
#define OSCMS_CODECS_BASE_TYPES_H

/**
 * @file base_types.h
 *
 * @brief Defines the basic types used by the codecs APIs
 *
 * Generally, a "base type" is one which has a direct mapping onto a native C type
 * (e.g., int, float, etc.), and which may be used by multiple other structures.
 *
 * There are also some fundamental structures (such as a string with size information)
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

    // Equivalent of ASN.1 OCTET
    typedef uint8_t OscmsOctet;

    // A sized-array of octets - Equivalent o ASN.1 OCTET STRING
    //
    // Effectively this represents a buffer of raw data, along with a record of it's length.
    // It is not meant to replace a traditional NUL-terminated C-style string.
    //
    // The creator of an instance of this type is responsible for
    // managing the memory for the array.
    //
    typedef struct
    {
        size_t length;
        OscmsOctet *data;
    } OscmsOctetBuffer;

    // Equivalent of ASN.1 BIT STRING
    typedef struct OscmsBitString
    {
        OscmsOctetBuffer data;
        int unused_bits;
    } OscmsBitString;

    // Certificate types - IEEE 1609.2-2022 Section 6.4.4
    typedef enum OscmsCertificateType
    {
        OSCMS_CERTIFICATE_TYPE_EXPLICIT = 0,
        OSCMS_CERTIFICATE_TYPE_IMPLICIT = 1,

        OSCMS_CERTIFICATE_TYPE_MAX = OSCMS_CERTIFICATE_TYPE_IMPLICIT,
    } OscmsCertificateType;

    // Hashed IDs
    // IEEE 1609.2-2022 Section 6.3.32..6.3.36
    typedef uint8_t OscmsHashedId3[3];
    typedef uint8_t OscmsHashedId8[8];
    typedef uint8_t OscmsHashedId10[10];
    typedef uint8_t OscmsHashedId32[32];
    typedef uint8_t OscmsHashedId48[48];

    // Hash Algorithm types
    // IEEE 1609.2-2022 Section 6.3.5
    typedef enum OscmsHashAlgorithm
    {
        OSCMS_HASH_ALGORITHM_SHA256 = 0,
        OSCMS_HASH_ALGORITHM_SHA384 = 1,
        OSCMS_HASH_ALGORITHM_SM3    = 2,

        OSCMS_HASH_ALGORITHM_MAX = OSCMS_HASH_ALGORITHM_SM3,
    } OscmsHashAlgorithm;

    // Hashed Data
    // IEEE 1609.2-2022 Section 6.3.8
    typedef struct OscmsHashedData
    {
        OscmsHashAlgorithm algorithm;
        OscmsHashedId48 hash; // large enough to hold the largest hash type
    } OscmsHashedData;

    // Time related types
    typedef uint32_t OscmsTime32; // IEEE 1609.2-2022 Section 6.4.15
    typedef uint64_t OscmsTime64; // IEEE 1609.2-2022 Section 6.3.11

    // Location related types
    typedef int32_t OscmsLatitude; // IEEE 1609.2-2022 Section 6.3.13
    static inline bool oscms_is_valid_latitude(const int64_t latitude)
    {
        return (-90000000 <= latitude) && (latitude <= 90000000);
    }

    typedef int32_t OscmsLongitude; // IEEE 1609.2-2022 Section 6.3.14
    static inline bool oscms_is_valid_longitude(const int64_t longitude)
    {
        return (-179999999 <= longitude) && (longitude <= 180000000);
    }

    typedef uint16_t OscmsElevation; // IEEE 1609.2-2022 Section 6.3.15
    static inline bool oscms_is_valid_elevation(const int64_t elevation)
    {
        return (0 <= elevation) && (elevation <= UINT16_MAX);
    }
    typedef struct OscmsTwoDLocation // IEEE 1609.2-2022 Section 6.4.19
    {
        OscmsLatitude latitude;   // [-90E6, 90E6] in microdegrees
        OscmsLongitude longitude; // [-180E6, 180E6] in microdegrees
    } OscmsTwoDLocation;

    typedef struct OscmsThreeDLocation // IEEE 1609.2-2022 Section 6.3.12
    {
        OscmsLatitude latitude;   // [-90E6, 90E6] in microdegrees
        OscmsLongitude longitude; // [-180E6, 180E6] in microdegrees
        OscmsElevation elevation; // [-32768E6, 32767E6] in microfeet
    } OscmsThreeDLocation;

    // IValue - IEEE 1609.2-2022 Section 6.2
    typedef uint16_t OscmsIValue;

    // Provider Service IDentifier (PSID)
    // IEEE 1609.2-2022 Section 6.3.10
    typedef uint64_t OscmsPsid;
#define OSCMS_PSID_SECURITY_MGMT ((OscmsPsid)0x23)  // Predefined PSID used in a number of SPDUS
#define OSCMS_PSID_CRL           ((OscmsPsid)0x100) // Predefined PSID used in CRLs

    // CRL Series Number
    // IEEE 1609.2-2022 Section 6.3.17
    typedef uint16_t OscmsCrlSeries;

    // CTL Related
    typedef uint8_t OscmsCtlSeriesId[8];             // IEEE 1609.2.1-2022 Section 7.3.16
    typedef uint16_t OscmsCtlSequenceNumber;         // IEEE 1609.2.1-2022 Section 7.3.17
    typedef OscmsHashedId48 OscmsCtElectorEntryHash; // IEEE 1609.2.1-2022 Section 7.3.18

    // ECC Point Curve Types
    typedef enum OscmsEccPointCurveType
    {
        OSCMS_ECC_POINT_CURVE_TYPE_NONE           = 0,
        OSCMS_ECC_POINT_CURVE_TYPE_NIST_P256      = 1,
        OSCMS_ECC_POINT_CURVE_TYPE_BRAINPOOL_P256 = 2,
        OSCMS_ECC_POINT_CURVE_TYPE_NIST_P384      = 3,
        OSCMS_ECC_POINT_CURVE_TYPE_BRAINPOOL_P384 = 4,
        OSCMS_ECC_POINT_CURVE_TYPE_SM2            = 5,

        OSCMS_ECC_POINT_CURVE_TYPE_MAX = OSCMS_ECC_POINT_CURVE_TYPE_SM2,
    } OscmsEccPointCurveType;

    // ECC Point Types - See IEEE 1609.2-2022 Section 6.3.23..6.3.24
    typedef enum OscmsEccPointType
    {
        OSCMS_ECC_POINT_TYPE_NONE           = 0,
        OSCMS_ECC_POINT_TYPE_X_ONLY         = 1,
        OSCMS_ECC_POINT_TYPE_FILL           = 2,
        OSCMS_ECC_POINT_TYPE_COMPRESSED_Y_0 = 3,
        OSCMS_ECC_POINT_TYPE_COMPRESSED_Y_1 = 4,
        OSCMS_ECC_POINT_TYPE_UNCOMPRESSED   = 5,

        OSCMS_ECC_POINT_TYPE_MAX = OSCMS_ECC_POINT_TYPE_UNCOMPRESSED,
    } OscmsEccPointType;

    typedef struct OscmsEccCurvePoint
    {
        OscmsEccPointCurveType curve_type;
        OscmsEccPointType point_type;
        OscmsOctetBuffer x; // Used for x-only and compresses_y_[01]
        OscmsOctetBuffer y; // Only for uncompressed
    } OscmsEccCurvePoint;

    // Supported Symmetric Encryption Algorithms
    // IEEE 1609.2-2022 Section 6.3.21
    typedef enum OscmsSymmetricAlgorithmType
    {
        OSCMS_SYMMETRIC_ALGORITHM_AES128  = 0,
        OSCMS_SYMMETRIC_ALGORITHM_SM4_CCM = 1,

        OSCMS_SYMMETRIC_ALGORITHM_MAX = OSCMS_SYMMETRIC_ALGORITHM_SM4_CCM
    } OscmsSymmetricAlgorithmType;

    // Symmetric Encryption Key
    // IEEE 1609.2-2022 Section 6.3.19
    typedef struct OscmsSymmetricEncryptionKey
    {
        OscmsSymmetricAlgorithmType algorithm;
        OscmsOctetBuffer key;
    } OscmsSymmetricEncryptionKey;

    // Public encryption Key
    // IEEE 1609.2-2022 Section 6.3.20
    typedef struct OscmsPublicEncryptionKey
    {
        OscmsSymmetricAlgorithmType algorithm;
        OscmsEccCurvePoint key;

    } OscmsPublicEncryptionKey;

    // Encrytion Key
    // IEEE 1609.2-2022 Section 6.3.18
    typedef enum OscmsEncryptionKeyType
    {
        OSCMS_ENCRYPTION_KEY_TYPE_SYMMETRIC = 1,
        OSCMS_ENCRYPTION_KEY_TYPE_PUBLIC    = 2,

        OSCMS_ENCRYPTION_KEY_TYPE_MAX = OSCMS_ENCRYPTION_KEY_TYPE_PUBLIC,
    } OscmsEncryptionKeyType;
    typedef struct OscmsEncryptionKey
    {
        OscmsEncryptionKeyType type;
        union
        {
            OscmsSymmetricEncryptionKey symmetric;
            OscmsPublicEncryptionKey public_key; // to avoid the C++ reserved keyword
        } key;
    } OscmsEncryptionKey;

    // Linkage Authority ID
    // IEEE 1609.2-2022 Section 7.3.14
    typedef uint8_t OscmsLaId[2];

    // Linkage Seed
    // IEEE 1609.2-2022 Section 7.3.15
    typedef uint8_t OscmsLinkageSeed[16];

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_CODECS_BASE_TYPES_H
