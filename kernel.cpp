#include "types.h"

static bool cleared = false;

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    if (cleared == true)
    {
        x=0;
        y=0;
        cleared = false;
    }

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                cleared=false;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                cleared=false;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void clear()
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x=0,y=0;

    for(y = 0; y < 25; y++)
        for(x = 0; x < 80; x++)
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
    
    cleared = true;
}

extern "C" void kmain () {
    clear();
    printf("PUT NAME HERE");
}
