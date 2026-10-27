#ifndef DOT11PHYTYPETOSTRING_HPP
#define DOT11PHYTYPETOSTRING_HPP

#include <wlanapi.h>

const char *PhyTypeToString(DOT11_PHY_TYPE phyType)
{
    switch (phyType)
    {
    case dot11_phy_type_unknown:
        return "Unknown";
    case dot11_phy_type_fhss:
        return "Frequency-Hopping Spread Spectrum (FHSS)";
    case dot11_phy_type_dsss:
        return "Direct Sequence Spread Spectrum (DSSS)";
    case dot11_phy_type_irbaseband:
        return "Infrared (IR) Baseband";
    case dot11_phy_type_ofdm:
        return "Orthogonal Frequency-Division Multiplexing (OFDM)";
    case dot11_phy_type_hrdsss:
        return "High Rate DSSS (HRDSSS)";
    case dot11_phy_type_erp:
        return "Extended Rate PHY (ERP)";
    case dot11_phy_type_ht:
        return "High Throughput (802.11n / HT)";
    case dot11_phy_type_vht:
        return "Very High Throughput (802.11ac / VHT)";
    case dot11_phy_type_dmg:
        return "Directional Multi-Gigabit (802.11ad / DMG)";
    case dot11_phy_type_he:
        return "High Efficiency (802.11ax / Wi-Fi 6)";
    default:
        return "Other / Newer PHY Type";
    }
}

#endif // DOT11PHYTYPETOSTRING_HPP