#ifndef DOREMIFASORASHIDOLOGIC_HPP
#define DOREMIFASORASHIDOLOGIC_HPP

#include <windows.h>
#include <thread>

namespace Doremifasorashido
{
    inline bool handle_doremifasorashido_octave(DWORD octave,
                                                DWORD duration)
    {
        if (octave == 0)
        {
            Beep(37, duration);
        }
        else if (octave == 1)
        {
            Beep(37, duration);
        }
        else if (octave == 2)
        {
            Beep(65, duration);
            Beep(73, duration);
            Beep(82, duration);
            Beep(87, duration);
            Beep(98, duration);
            Beep(110, duration);
            Beep(123, duration);
            Beep(131, duration);
        }
        else if (octave == 3)
        {
            Beep(131, duration);
            Beep(147, duration);
            Beep(165, duration);
            Beep(175, duration);
            Beep(196, duration);
            Beep(220, duration);
            Beep(247, duration);
            Beep(262, duration);
        }
        else if (octave == 4)
        {
            Beep(262, duration);
            Beep(294, duration);
            Beep(330, duration);
            Beep(349, duration);
            Beep(392, duration);
            Beep(440, duration);
            Beep(494, duration);
            Beep(523, duration);
        }
        else if (octave == 5)
        {
            Beep(523, duration);
            Beep(587, duration);
            Beep(659, duration);
            Beep(698, duration);
            Beep(784, duration);
            Beep(880, duration);
            Beep(988, duration);
            Beep(1047, duration);
        }
        else if (octave == 6)
        {
            Beep(1047, duration);
            Beep(1175, duration);
            Beep(1319, duration);
            Beep(1397, duration);
            Beep(1568, duration);
            Beep(1760, duration);
            Beep(1976, duration);
            Beep(2093, duration);
        }
        else if (octave == 7)
        {
            Beep(2093, duration);
            Beep(2349, duration);
            Beep(2637, duration);
            Beep(2794, duration);
            Beep(3136, duration);
            Beep(3520, duration);
            Beep(3951, duration);
            Beep(4186, duration);
        }
        else if (octave == 8)
        {
            Beep(4186, duration);
            Beep(4699, duration);
            Beep(5274, duration);
            Beep(5588, duration);
            Beep(6272, duration);
            Beep(7040, duration);
            Beep(7902, duration);
            Beep(8372, duration);
        }
        else if (octave == 9)
        {
            Beep(8372, duration);
            Beep(9397, duration);
            Beep(10548, duration);
            Beep(11175, duration);
            Beep(12544, duration);
            Beep(14080, duration);
            Beep(15804, duration);
            Beep(16744, duration);
        }
        else if (octave == 10)
        {
            Beep(16744, duration);
            Beep(18795, duration);
            Beep(21096, duration);
            Beep(22351, duration);
            Beep(25088, duration);
            Beep(28160, duration);
            Beep(31609, duration);
            Beep(32767, duration); // Beepの最大周波数
        }
        else if (octave == 11)
        {
            Beep(32767, duration);
        }
        return true;
    }
}

#endif // DOREMIFASORASHIDOLOGIC_HPP