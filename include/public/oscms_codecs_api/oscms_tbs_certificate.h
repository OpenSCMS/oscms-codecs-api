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

/**
 * @file Defines the API datastructures related to the ToBSignedCertificate structure
 *
 * See IEEE 1609.2-2016 Section 6.4.8 through 6.4.36 and IEEE 1609.2-2022 Section 11.2.8
 *
 * No decode/encode functions are exposed as this is an internal element of other higher
 * level structures. However, it is extremely large and complex, and thus warrants its own header.
 *
 * Function prototypes are provided for two utility functions which are likely to be required
 * by concrete implementations of the API. These functions convert between the API's representations and
 * the implementation's internal structures.
 *
 * Also, two utility functions are implemented in the API library for initializing and clearing
 * an OscmsTbsCertificate structure in a consistent way.
 */

#ifndef OSCMS_TBS_CERTIFICATE_H
#define OSCMS_TBS_CERTIFICATE_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    // CertificateID definitions: IEEE 1609.2-2016 Section 6.4.9 .. 6.4.13

    // GroupLinkageValue definitions: IEEE 1609.2-2022 Section 6.4.12
    typedef struct OscmsGroupLinkageValue
    {
        uint8_t j_value[4];
        uint8_t value[4];
    } OscmsGroupLinkageValue;

    typedef enum OscmsCertificateIdType
    {
        OSCMS_CERTIFICATE_ID_TYPE_LINKAGE   = 1,
        OSCMS_CERTIFICATE_ID_TYPE_HOSTNAME  = 2,
        OSCMS_CERTIFICATE_ID_TYPE_BINARY_ID = 3,
        OSCMS_CERTIFICATE_ID_TYPE_NONE      = 4
    } OscmsCertificateIdType;

    typedef struct OscmsCertificateId
    {
        OscmsCertificateIdType type;
        union
        {
            struct // LinkageData - See IEEE 1609.2-2016 Section 6.4.10
            {
                uint16_t i_cert;
                uint8_t linkage_value[9];
                OscmsGroupLinkageValue *group_linkage_value;
            } linkage_data;

            OscmsOctetBuffer host_name;
            OscmsOctetBuffer binary_id; // Length [1,64]
        } value;
    } OscmsCertificateId;

    // ValidityPeriod definitions: IEEE 1609.2-2016 Section 6.4.14 .. 6.4.16
    typedef enum OscmsValidityDurationUnits
    {
        OSCMS_VALIDITY_DURATION_UNITS_MICROSECONDS = 1,
        OSCMS_VALIDITY_DURATION_UNITS_MILLISECONDS = 2,
        OSCMS_VALIDITY_DURATION_UNITS_SECONDS      = 3,
        OSCMS_VALIDITY_DURATION_UNITS_MINUTES      = 4,
        OSCMS_VALIDITY_DURATION_UNITS_HOURS        = 5,
        OSCMS_VALIDITY_DURATION_UNITS_60_HOURS     = 6,
        OSCMS_VALIDITY_DURATION_UNITS_YEARS        = 7,
    } OscmsValidityDurationUnits;

    // GeographicalRegion definitions: IEEE 1609.2-2016 Section 6.4.17 .. 6.4.26
    typedef enum OscmsGeographicalRegionType
    {
        OSCMS_GEOGRAPHICAL_REGION_TYPE_NONE        = 0,
        OSCMS_GEOGRAPHICAL_REGION_TYPE_CIRCULAR    = 1,
        OSCMS_GEOGRAPHICAL_REGION_TYPE_RECTANGULAR = 2,
        OSCMS_GEOGRAPHICAL_REGION_TYPE_POLYGONAL   = 3,
        OSCMS_GEOGRAPHICAL_REGION_TYPE_IDENTIFIED  = 4,
    } OscmsGeographicalRegionType;

    typedef enum OscmsIdentifiedRegionType
    {
        OSCMS_IDENTIFIED_REGION_TYPE_NONE                   = 0,
        OSCMS_IDENTIFIED_REGION_TYPE_COUNTRY_ONLY           = 1,
        OSCMS_IDENTIFIED_REGION_TYPE_COUNTRY_AND_REGIONS    = 2,
        OSCMS_IDENTIFIED_REGION_TYPE_COUNTRY_AND_SUBREGIONS = 3
    } OscmsIdentifiedRegionType;

    typedef uint16_t OscmsCountryOnly;

    typedef struct OscmsCountryAndRegion
    {
        OscmsCountryOnly country;
        OscmsOctetBuffer region;
    } OscmsCountryAndRegion;

    typedef struct OscmsRegionAndSubregions
    {
        uint8_t region;
        uint16_t *subregions;
        size_t subregion_count;
    } OscmsRegionAndSubregions;

    typedef struct OscmsCountryAndSubregions
    {
        OscmsCountryOnly country;
        OscmsRegionAndSubregions *subregions;
        size_t subregion_count;
    } OscmsCountryAndSubregions;

    typedef struct OscmsIdentifiedRegion
    {
        OscmsIdentifiedRegionType type;
        union
        {
            OscmsCountryOnly country;
            OscmsCountryAndRegion country_and_region;
            OscmsCountryAndSubregions country_and_subregions;
        } value;

    } OscmsIdentifiedRegion;

    typedef struct OscmsRectangularRegion
    {
        OscmsTwoDLocation top_left;
        OscmsTwoDLocation bottom_right;
    } OscmsRectangularRegion;
    typedef struct OscmsGeographicalRegion
    {
        OscmsGeographicalRegionType type;
        union
        {
            struct
            {
                OscmsTwoDLocation center;
                uint16_t radius; // in meters
            } circular;
            struct
            {
                OscmsRectangularRegion *rectangles;
                size_t rectangle_count;
            } rectangular;
            struct
            {
                OscmsTwoDLocation *points;
                size_t point_count;
            } polygonal;
            struct
            {
                OscmsIdentifiedRegion *regions;
                size_t count;
            } identified_regions;
        } value;
    } OscmsGeographicalRegion;

    // PSID-SSP definitions: IEEE 1609.2-2016 Section 6.4.28 .. 6.4.29

    typedef enum OscmsSspType
    {
        OSCMS_SSP_TYPE_NONE   = 0,
        OSCMS_SSP_TYPE_OPAQUE = 1,
        OSCMS_SSP_TYPE_BITMAP = 2,
    } OscmsSspType;

    typedef struct OscmsSsp
    {
        OscmsSspType type;
        OscmsOctetBuffer value;
    } OscmsSsp;

    typedef struct OscmsPsidSsp
    {
        OscmsPsid psid;
        OscmsSsp *ssp; // OPTIONAL
    } OscmsPsidSsp;

    // Permissions related fields: IEEE 1609.2-2016 Section 6.4.30 through 6.4.34

    // Define the bit values, not numbers as per the spec
    typedef enum OscmsEndEntityType
    {
        OSCMS_END_ENTITY_TYPE_NONE  = 0,
        OSCMS_END_ENTITY_TYPE_APP   = 1,
        OSCMS_END_ENTITY_TYPE_ENROL = 2
    } OscmsEndEntityType;

    typedef enum OscmsSspRangeType
    {
        OSCMS_SSP_RANGE_TYPE_NONE   = 0,
        OSCMS_SSP_RANGE_TYPE_OPAQUE = 1,
        OSCMS_SSP_RANGE_TYPE_ALL    = 2,
        OSCMS_SSP_RANGE_TYPE_BITMAP = 3,
    } OscmsSspRangeType;

    typedef struct OscmsBitmapSspRange
    {
        OscmsOctetBuffer ssp_value;
        OscmsOctetBuffer ssp_bitmask;
    } OscmsBitmapSspRange;

    typedef struct OscmsSspRange
    {
        OscmsSspRangeType type;

        union
        {
            struct
            {
                // Set to NULL and 0 for OSCMS_SSP_RANGE_TYPE_ALL or OSCMS_SSP_RANGE_TYPE_BITMAP
                OscmsOctetBuffer *buffers;
                size_t buffer_count;
            } opaque;
            OscmsBitmapSspRange bitmap_ssp_range;
        } value;
    } OscmsSspRange;

    typedef struct OscmsPsidSspRange
    {
        OscmsPsid psid;
        OscmsSspRange *ssp_range;
    } OscmsPsidSspRange;

    typedef enum OscmsSubjectPermissionType
    {
        OSCMS_SUBJECT_PERMISSION_TYPE_EXPLICIT = 1,
        OSCMS_SUBJECT_PERMISSION_TYPE_ALL      = 2,
    } OscmsSubjectPermissionType;

    typedef struct OscmsSubjectPermissions
    {
        OscmsSubjectPermissionType type;

        // Set to NULL for OSCMS_SUBJECT_PERMISSION_TYPE_ALL
        OscmsPsidSspRange *explicit_permissions;
        size_t explicit_count;
    } OscmsSubjectPermissions;

    typedef struct OscmsPsidGroupPermissions
    {
        OscmsSubjectPermissions subject_permissions;
        bool has_minimum_chain_length; // to avoid a pointer
        int64_t minimum_chain_length;
        int64_t chain_depth_range;
        OscmsEndEntityType ee_type; // defaults to OSCMS_END_ENTITY_TYPE_APP
    } OscmsPsidGroupPermissions;

    // VerificationKeyIndicator (VKI) definitions: IEEE 1609.2.1-2022 Section 11.2.7

    typedef enum OscmsVerificationKeyIndicatorType
    {
        OSCMS_VERIFICATION_KEY_INDICATOR_TYPE_NONE           = 0,
        OSCMS_VERIFICATION_KEY_INDICATOR_TYPE_KEY            = 1,
        OSCMS_VERIFICATION_KEY_INDICATOR_TYPE_RECONSTRUCTION = 2,

    } OscmsVerificationKeyIndicatorType;

    typedef struct OscmsVerificationKeyIndicator
    {
        OscmsVerificationKeyIndicatorType type;
        OscmsEccCurvePoint point;
    } OscmsVerificationKeyIndicator;

    // ToBeSignedCertificate flags extension definition: IEEE 1609.2.1-2022 Section 11.2.8
    typedef enum OscmsTbsCertificateFlags
    {
        OSCMS_TBS_CERTIFICATE_FLAG_NONE = 0,
        OSCMS_TBS_CERTIFICATE_FLAG_CUBK = 1
    } OscmsTbsCertificateFlags;

    // The actual top level structure
    typedef struct OscmsTbsCertificate
    {
        OscmsCertificateId id;
        OscmsHashedId3 craca_id;
        OscmsCrlSeries crl_series;

        OscmsTime32 validity_period_start;
        OscmsValidityDurationUnits validity_period_units;
        uint16_t validity_period;

        OscmsVerificationKeyIndicator verify_key_indicator;

        // Optional fields. Set to NULL (or zero) if not present.
        OscmsPsidSsp *app_permissions; // OPTIONAL
        size_t app_permissions_count;

        OscmsGeographicalRegion *region;   // OPTIONAL
        OscmsOctetBuffer *assurance_level; // OPTIONAL - Should be SIZE(1) if present

        OscmsPsidGroupPermissions *cert_issue_permissions; // OPTIONAL
        size_t cert_issue_permissions_count;

        OscmsPsidGroupPermissions *cert_request_permissions; // OPTIONAL
        size_t cert_request_permissions_count;

        OscmsPublicEncryptionKey *encryption_key; // OPTIONAL

        OscmsBitString *flags; // OPTIONAL - set to OSCMS_TBS_CERTIFICATE_FLAG_NONE if not used.

        // Note: The following extensions are not currently supported as we do not use them
        //
        // * appExtensions
        // * certIssueExtensions
        // * certRequestExtensions
        //
        // They are encoded internally as zero length sequences, and are not decoded.
        //

        // This field does not form part of the standard.
        //
        // One of these structures contains a large number of dynamically allcoated buffers. It is strongly recommended
        // that concrete implementations of the `certificate_from_internal` function use this sequence to track all such
        // buffers.
        //
        // Clients initializing a structure for a call to `oscms_internal_from_tbs_certificate` are also free to use
        // this.
        //
        // The memory used can then be freed using the `oscms_empty_sequence` function.
        //
        OscmsSequence allocations;
    } OscmsTbsCertificate;

    /**
     * Convert an internal representation of a TBS Certificate to the API's representation.
     *
     * @param internal The internal representation of the TBS certificate.
     * @param tbs_certificate The TBS certificate to convert.
     *
     * @return 0 on success.
     */
    int oscms_tbs_certificate_from_internal(const void *internal, OscmsTbsCertificate *tbs_certificate);

    /**
     * Convert the API's representation of the TBS certificate to an internal representation.
     *
     * @param tbs_certificate The TBS certificate to convert.
     * @param internal The internal representation of the TBS certificate.
     *
     * @return 0 on success.
     */
    int oscms_internal_from_tbs_certificate(const OscmsTbsCertificate *tbs_certificate, void *internal);

    /**
     * Initialize an internal representation of the TBS certificate structure.
     *
     * All fields are set to their default values (if applicable), all pointers (I.e. OPTIONAL fields) are set to NULL.
     *
     * @param internal The TBS certificate to initialize.
     *
     */
    void oscms_tbs_certificate_init_internal(void *internal);

    /**
     * Initialize a TBS certificate structure.
     *
     * All fields are set to their default values (if applicable), all pointers (I.e. OPTIONAL fields) are set to NULL.
     *
     * @param tbs_certificate The TBS certificate to initialize.
     *
     */
    SO_EXPORT void oscms_tbs_certificate_init(OscmsTbsCertificate *tbs_certificate);

    /**
     * Clear the fields of the TBS certificate.
     *
     * This will work through the object, releasing all allocated memory. It does not free the object itself.
     * This assumes that all pointers withing the structure, and its children, point to dynamically allocated memory.
     *
     * @param tbs_certificate The TBS certificate to clear.
     *
     */
    SO_EXPORT void oscms_empty_tbs_certificate(OscmsTbsCertificate *tbs_certificate);

    /**
     * Free the memory used by the TBS certificate, including the object itself
     *
     * @param tbs_certificate The TBS certificate to free
     *
     */
    SO_EXPORT void oscms_free_tbs_certificate(OscmsTbsCertificate *tbs_certificate);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_TBS_CERTIFICATE_H
