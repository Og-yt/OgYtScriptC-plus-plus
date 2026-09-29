#ifndef CURRENTTIME_HPP
#define CURRENTTIME_HPP

#include <gtkmm.h>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>
#include "TimeZone/TimeZoneConfig.hpp"

namespace CurrentWorldTime
{
    inline bool handle_current_world_time(const std::string &Country_Code,
                                          int line_num,
                                          std::string &result_text,
                                          Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        if (Country_Code == "MID")                            // ミッドウェー島
        {
            MidwayTime::handle_midway_time(result_text);
            return true;
        }
        else if (Country_Code == "NIU")                       // ニウエ
        {
            NiueTime::handle_niue_time(result_text);
            return true;
        }
        else if (Country_Code == "ASM")                       // アメリカ領サモア (パゴパゴ諸島)
        {
            PagoPagoTime::handle_pago_pago_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_HL")                    // アメリカ / ハワイ州
        {
            HonoluluTime::handle_honolulu_time(result_text);
            return true;
        }
        else if (Country_Code == "COK_RAR")                   // クック諸島ラロトンガ
        {
            RarotongaTime::handle_rarotonga_time(result_text);
            return true;
        }
        else if (Country_Code == "PYF")                       // タヒチ
        {
            TahitiTime::handle_tahiti_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_ANC")                   // アンカレッジ
        {
            AnchorageTime::handle_anchorage_time(result_text);
            return true;
        }
        else if (Country_Code == "GMD")                       // ガンビア
        {
            GambiaTime::handle_gambia_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_LOS")                   // ロサンゼルス
        {
            LosangelesTime::handle_los_angeles_time(result_text);
            return true;
        }
        else if (Country_Code == "PCN")                       // ピトケアン
        {
            PitcairnTime::handle_pitcairn_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_CAM")                   // ケンブリッジ
        {
            CambridgeTime::handle_cambridge_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_CHI")                   // シカゴ
        {
            ChicagoTime::handle_chicago_time(result_text);
            return true;
        }
        else if (Country_Code == "ECW")                       // ガラパゴス
        {
            GalapagosTime::handle_galapagos_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_NEW")                   // ニューヨーク
        {
            NewYorkTime::handle_newyork_time(result_text);
            return true;
        }
        else if (Country_Code == "EASTER")                    // イースター島
        {
            EasterTime::handle_easter_time(result_text);
            return true;
        }
        else if (Country_Code == "USA_CAR")                   // カラカス
        {
            CaracasTime::handle_caracas_time(result_text);
            return true;
        }
        else if (Country_Code == "BMU")                       // バミューダ諸島
        {
            BermudaTime::handle_bermuda_time(result_text);
            return true;
        }
        else if (Country_Code == "ARG")                       // アルゼンチン
        {
            ArgentineTime::handle_argentine_time(result_text);
            return true;
        }
        else if (Country_Code == "SGS")                       // サウスジョージア
        {
            SouthGeorgiaTime::handle_south_georgia_time(result_text);
            return true;
        }
        else if (Country_Code == "CPV")                       // カーボベルデ
        {
            CapeVerdeTime::handle_cape_verde_time(result_text);
            return true;
        }
        else if (Country_Code == "CIV")                       // コートジボワール
        {
            CoteDivoireTime::handle_cote_divoire_time(result_text);
            return true;
        }
        else if (Country_Code == "GBR")                       // イギリス/ロンドン
        {
            LondonTime::handle_london_time(result_text);
            return true;
        }
        else if (Country_Code == "ITA")                       // イタリア
        {
            ItalyTime::handle_italy_time(result_text);
            return true;
        }
        else if (Country_Code == "GRC")                       // ギリシャ/アテネ
        {
            GreeceTime::handle_greece_time(result_text);
            return true;
        }
        else if (Country_Code == "KEN")                       // ケニア/ナイロビ
        {
            KenyaTime::handle_kenya_time(result_text);
            return true;
        }
        else if (Country_Code == "RUS_MOS")                   // ロシア/モスクワ
        {
            RussianTime::handle_russian_time(result_text);
            return true;
        }
        else if (Country_Code == "IRQ")                       // イラク/バグダッド
        {
            IraqTime::handle_iraq_time(result_text);
            return true;
        }
        else if (Country_Code == "UAE")                       // アラブ首長国連邦/ドバイ
        {
            ArabTime::handle_arab_time(result_text);
            return true;
        }
        else if (Country_Code == "PAK")                       // パキスタン/カラチ
        {
            PakistanTime::handle_pakistan_time(result_text);
            return true;
        }
        else if (Country_Code == "BGD")                       // バングラデシュ/ダッカ
        {
            BangladeshTime::handle_bangladesh_time(result_text);
            return true;
        }
        else if (Country_Code == "IDN")                       // インドネシア
        {
            IndonesiaTime::handle_indonesia_time(result_text);
            return true;
        }
        else if (Country_Code == "CHN")                       // 中国
        {
            ChinaTime::handle_china_time(result_text);
            return true;
        }
        else if (Country_Code == "JPN")                       // 日本!!
        {
            JapanTime::handle_japan_time(result_text);
            return true;
        }
        else if (Country_Code == "GUM")                       // グアム
        {
            GuamTime::handle_guam_time(result_text);
            return true;
        }
        else if (Country_Code == "RUS_SAK")                   // サハリン
        {
            SakhalinTime::handle_sakhalin_time(result_text);
            return true;
        }
        else if (Country_Code == "NRU")                       // ナウル
        {
            NauruTime::handle_nauru_time(result_text);
            return true;
        }
        else
        {
            return false;
        }

        return false;
    }
}

#endif // CURRENTTIME_HPP