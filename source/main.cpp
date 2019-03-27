#include <iostream>
#include <stdio.h>
#include <string.h>

#include "PicProgVirtualMachine.h"

static const char* YOU_CAN_GET_HELP = "You can get help using \"-?\" or \"--help\".";

void print_help()
{
    std::cout <<
    "Specify a path to an image file to execute in the first argument."
    "-? or --help       :   Show Help\n" <<
    "-g or --graphic    :   Graphic mode\n" <<
    std::endl;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Error, You must specify an image file to \"execute\".\n"
                << YOU_CAN_GET_HELP << std::endl;
        return 1;
    }
    //Get the image
    bool graphic_mode = false;
    char* img_path = argv[1];
    //Read arguments
    for (int i = 2; i < argc; i++)
    {
        size_t arg_len = strlen(argv[i]);
        if (arg_len < 2)
        {
            std::cerr << "Argument error, argument is too short!\n"
            << YOU_CAN_GET_HELP << std::endl;
            return 1;
        }
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == '-')
            {
                //Wordy arguments
                if (arg_len < 3)
                {
                    std::cerr << "Argument error, option is too short!\n"
                    << YOU_CAN_GET_HELP << std::endl;
                    return 1;
                }
                if (!strcmp("--graphic", argv[i]))
                {
                    //Graphic mode
                    graphic_mode = true;
                    continue;
                }
                if (!strcmp("--help", argv[i]))
                {
                    //Help
                    print_help();
                    return 0;
                }
                std::cerr << "Argument error, unknown option : \"" << argv[i] << "\".\n"
                << YOU_CAN_GET_HELP << std::endl;
                return 1;
            }
            else
            {
                if (arg_len > 2)
                {
                    std::cerr << "Argument error, option is too long : \"" << argv[i] << "\". Did you mean to use --?\n"
                    << YOU_CAN_GET_HELP << std::endl;
                    return 1;
                }
                switch (argv[i][1])
                {
                case 'g':
                    //Graphic mode
                    graphic_mode = true;
                    break;
                case '?':
                    //Help
                    print_help();
                    return 0;
                default:
                    //Unknown
                    std::cerr << "Argument error, unknown option : \"" << argv[i] << "\".\n"
                    << YOU_CAN_GET_HELP << std::endl;
                    return 1;
                }
            }

        }
        else
        {
            std::cerr << "Argument error : \"" << argv[i] << "\", expected an option (starting by - or --).\n"
            << "You can get help using \"-?\" or \"--help\"." << std::endl;
            return 1;
        }
    }



    PPVM ppvm(img_path, graphic_mode);

    auto init_code = ppvm.initialize();

    if (init_code)
    {
        std::cerr << "The PPVM could not be initialized.\n - ";
        switch (init_code)
        {
        case InitCodes::WrongImageFilePath:
            std::cerr << "The image file could not be found." << std::endl;
            break;
        case InitCodes::FileIsJPEG:
            std::cerr << "The image file is a JPEG, it is not suitable for the PPVM.\n"
            << "Please use bitmap or PNG files." << std::endl;
        default:
            std::cerr << std::endl;
            break;
        }
        return 1;
    }
    else
    {
        ppvm.run();
    }

    std::cout << "Program terminated\n";



    return 0;
}
