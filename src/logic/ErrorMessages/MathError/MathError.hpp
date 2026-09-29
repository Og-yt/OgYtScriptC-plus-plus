#ifndef MATHERROR_HPP
#define MATHERROR_HPP

#include "../../ErrorLogic.hpp"

namespace MathError
{
    namespace ArcSinError
    {
        inline bool arg_1_is_min2_max2(double arg_1,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < -1 || arg_1 > 1)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathAsin must be in [-1, 1].");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
            return true;
        }
    }

    namespace ArcCosError
    {
        inline bool arg_1_is_min2_max0(double arg_1,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < -1 || arg_1 > 1)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathACos must be in [-1, 1].");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
            return true;
        }
    }

    namespace PIError
    {
        inline bool arg_1_is_negative(double arg_1,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathPI cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }
    }

    namespace SquareRootError
    {
        inline bool arg_1_is_negative(double arg_1,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathSqrt must be in [0 that's all].");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }
    }

    namespace SquareNumberError
    {
        inline bool arg_1_is_negative(double arg_1,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathSqrt cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }
    }

    namespace CubicNumberError
    {
        inline bool arg_1_is_negative(double arg_1,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Argument for MathCbrt cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }
    }

    namespace FactorialError
    {
        inline bool arg_1_is_negative(long long arg_1,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: Argument for MathFact cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return true;
        }
    }

    namespace PermutationError
    {
        inline bool arg_2_is_thats_all(long long arg_1,
                                       long long arg_2,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_2 > arg_1)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: n must be greater than or equal to r.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }

        inline bool arg_1_2_is_0_or_negative(long long arg_1,
                                             long long arg_2,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_2 < 0 || arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: n and r cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return true;
        }
    }

    namespace CombinationError
    {
        inline bool arg_2_is_thats_all(long long arg_1,
                                       long long arg_2,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_2 > arg_1)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: n must be greater than or equal to r.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }

        inline bool arg_1_2_is_0_or_negative(long long arg_1,
                                             long long arg_2,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_2 < 0 || arg_1 < 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: n and r cannot be negative.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return true;
        }
    }

    namespace LerTranscError
    {
        inline bool arg_3_is_negative(long long arg_3,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_3 <= 0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: Parameter 'c' must be greater than 0 to avoid zero or negative denominators.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }

        inline bool arg_1_is_positive(long long a_val,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (a_val > 1.0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: This basic series implementation requires |z| <= 1.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }

        inline bool arg_1_is_1_and_arg_2_is_1_below(long long a_val,
                                                    long long b_val,
                                                    int line_num,
                                                    std::string &result_text,
                                                    Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (a_val == 1.0 && b_val <= 1.0)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: If |z| == 1, 's' must be greater than 1 for the series to converge.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }
    }

    namespace Jacobi_CN_Error
    {
        inline bool handle_arg_2_0_val_or_1(long long arg_2,
                                            int line_num,
                                            std::string &result_text,
                                            Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg_2 < 0 || arg_2 > 1)
            {
                result_text += ErrorLogic::build_msg(line_num, "b must be in [0, 1]");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }
    }

    namespace MatrixProductError
    {
        inline bool handle_arg3_not_arg5(double arg3,
                                         double arg5,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (arg3 != arg5)
            {
                result_text += ErrorLogic::build_msg(line_num, "Matrix dimensions mismatch for multiplication!");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return true;
        }
    }
}

#endif // MATHERROR_HPP