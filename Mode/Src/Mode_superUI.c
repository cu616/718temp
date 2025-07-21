// soperUI模组

#include <main.h>
#include <Mode_superUI.h>

#define FUNCTION_NUMBER 6

void superUI(uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER])
{
    OLED_Clear();
    uint8_t choice = 1;
    uint8_t select = 0;
    while (1)
    {
        if (select != 1)
        {
            OLED_ShowString(0, 0, "Please select", 8, 1);
            OLED_ShowString(0, 10, "super 1", 8, 1);
            OLED_ShowString(0, 20, "super 2", 8, 1);
            OLED_ShowString(0, 30, "super 3", 8, 1);
            OLED_ShowString(0, 40, "super 4", 8, 1);
            OLED_ShowString(0, 50, "super 5", 8, 1);
            OLED_ShowString(64, 10, "super 6", 8, 1);
            OLED_ShowString(64, 20, "super 7", 8, 1);
            OLED_ShowString(64, 30, "super 8", 8, 1);
            OLED_ShowString(64, 40, "super 9", 8, 1);
            OLED_ShowString(64, 50, "back", 8, 1);
            if (key1state == 1)
            {
                if (choice != 10)
                    choice += 1;
                else
                    choice = 1;
                key1state = 0;
            }
            switch (choice)
            {
            case 1:
                OLED_ShowString(0, 10, "super 1", 8, 0);
                break;
            case 2:
                OLED_ShowString(0, 20, "super 2", 8, 0);
                break;
            case 3:
                OLED_ShowString(0, 30, "super 3", 8, 0);
                break;
            case 4:
                OLED_ShowString(0, 40, "super 4", 8, 0);
                break;
            case 5:
                OLED_ShowString(0, 50, "super 5", 8, 0);
                break;
            case 6:
                OLED_ShowString(64, 10, "super 6", 8, 0);
                break;
            case 7:
                OLED_ShowString(64, 20, "super 7", 8, 0);
                break;
            case 8:
                OLED_ShowString(64, 30, "super 8", 8, 0);
                break;
            case 9:
                OLED_ShowString(64, 40, "super 9", 8, 0);
                break;
            case 10:
                OLED_ShowString(64, 50, "back", 8, 0);
                break;
            default:
                break;
            }
            OLED_Refresh();
        }
        if (key2state == 1)
        {
            select = 1;
            key2state = 0;
            OLED_Clear();
            if (choice == 10)
            {
                return; // back to main menu
            }
            super(choice, name, value);
            OLED_Clear();
            select = 0;
            choice = 1;
        }
    }
}

void super(int number, uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER])
{
    uint8_t choice = 1;
    uint8_t select = 0;
    char muf[20];
    sprintf(muf, "super_%d", number);
    while (1)
    {
        if (select != 1)
        {
            OLED_ShowString(0, 0, muf, 8, 1);
            OLED_ShowString(0, 10, "operate", 8, 1);
            OLED_ShowString(0, 20, "change", 8, 1);
            OLED_ShowString(0, 30, "back", 8, 1);
            if (key1state == 1)
            {
                if (choice != 3)
                    choice += 1;
                else
                    choice = 1;
                key1state = 0;
            }
            switch (choice)
            {
            case 1:
                OLED_ShowString(0, 10, "operate", 8, 0);
                break;
            case 2:
                OLED_ShowString(0, 20, "change", 8, 0);
                break;
            case 3:
                OLED_ShowString(0, 30, "back", 8, 0);
                break;
            default:
                break;
            }
            OLED_Refresh();
        }
        if (key2state == 1)
        {
            select = 1;
            key2state = 0;
            OLED_Clear();
            if (choice == 3)
            {
                return; // back to main menu
            }
            switch (choice)
            {
            case 1:
                operate(name[number - 1], value[number - 1]);
                break;
            case 2:
                change(name[number - 1], value[number - 1]);
                break;
            default:
                break;
            }
            OLED_Clear();
            select = 0;
            choice = 1;
        }
    }
}

void operate(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER])
{
    OLED_Clear();
    uint16_t i = 0;
    while (name[i] != 0 && i < SUPER_TASK_NUMBER)
    {
        single_work(name[i], value[i]);
        i++;
    }
}

void change(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER])
{
    uint16_t i = 0;
    uint8_t choice = 1;
    uint8_t select = 0;

    while (i < SUPER_TASK_NUMBER)
    {
        if (select != 1)
        {
            OLED_ShowString(0, 0, "please select the function", 8, 1);
            OLED_ShowString(0, 10, "turn", 8, 1);
            OLED_ShowString(0, 20, "go_straight", 8, 1);
            OLED_ShowString(0, 30, "trace", 8, 1);
            OLED_ShowString(0, 40, "reverse", 8, 1);
            OLED_ShowString(0, 50, "HAL_Delay", 8, 1);
            OLED_ShowString(64, 10, "over", 8, 1);
            OLED_ShowNum(64, 50, i, 2, 8, 1);//显示已有功能数量
            if (key1state == 1)
            {
                if (choice != FUNCTION_NUMBER)
                    choice += 1;
                else
                    choice = 1;
                key1state = 0;
            }
            switch (choice)
            {
            case 1:
                OLED_ShowString(0, 10, "turn", 8, 0);
                break;
            case 2:
                OLED_ShowString(0, 20, "go_straight", 8, 0);
                break;
            case 3:
                OLED_ShowString(0, 30, "trace", 8, 0);
                break;
            case 4:
                OLED_ShowString(0, 40, "reverse", 8, 0);
                break;
            case 5:
                OLED_ShowString(0, 50, "HAL_Delay", 8, 0);
                break;
            case 6:
                OLED_ShowString(64, 10, "over", 8, 0);
                break;
            default:
                break;
            }
            OLED_Refresh();
        }
        if (key2state == 1)
        {
            select = 1;
            key2state = 0;
            OLED_Clear();
            switch(choice)
            {
            case 1:case 4:case 5:
                value[i] = set_value(); // set the value
                name[i] = choice; // save the choice
                break;
            case 2:case 3:
                name[i] = choice; // save the choice
                break;
            case FUNCTION_NUMBER:
                name[i] = 0; // save the choice
                return; // back to main menu
                break;
            default:
                break;
            }
            OLED_Refresh();
            select = 0;
            choice = 1;
            i++;
        }
    }
}

void single_work(uint8_t name, uint16_t value)
{
    switch (name)
    {
    case 1:
        turn(value, 60, 1);
        break;
    case 2:
        go_straight(Yaw, 40);
        break;
    case 3:
        trace(60);
        break;
    case 4:
        reverse_straight(Yaw, value);
        break;
    case 5:
        HAL_Delay(value);
        break;
    default:
        break;
    }
}

uint16_t set_value()
{
    uint16_t value = 0; // Initialize value to 0
    OLED_Clear();
    uint8_t choice = 1;
    uint8_t select = 0;
    uint8_t flag = 1;
    while (1)
    {
        if (select != 1)
        {
            OLED_ShowString(0, 0, "Please select", 8, 1);
            OLED_ShowString(0, 10, "1", 8, 1);
            OLED_ShowString(0, 20, "2", 8, 1);
            OLED_ShowString(0, 30, "3", 8, 1);
            OLED_ShowString(0, 40, "4", 8, 1);
            OLED_ShowString(0, 50, "5", 8, 1);
            OLED_ShowString(30, 10, "6", 8, 1);
            OLED_ShowString(30, 20, "7", 8, 1);
            OLED_ShowString(30, 30, "8", 8, 1);
            OLED_ShowString(30, 40, "9", 8, 1);
            OLED_ShowString(30, 50, "0", 8, 1);
            OLED_ShowString(64, 10, "-", 8, 1);
            OLED_ShowString(64, 20, "back", 8, 1);
            OLED_ShowNum(64, 30, value, 2, 8, 1);
            if (key1state == 1)
            {
                if (choice != 12)
                    choice += 1;
                else
                    choice = 1;
                key1state = 0;
            }
            switch (choice)
            {
            case 1:
                OLED_ShowString(0, 10, "1", 8, 0);
                break;
            case 2:
                OLED_ShowString(0, 20, "2", 8, 0);
                break;
            case 3:
                OLED_ShowString(0, 30, "3", 8, 0);
                break;
            case 4:
                OLED_ShowString(0, 40, "4", 8, 0);
                break;
            case 5:
                OLED_ShowString(0, 50, "5", 8, 0);
                break;
            case 6:
                OLED_ShowString(30, 10, "6", 8, 0);
                break;
            case 7:
                OLED_ShowString(30, 20, "7", 8, 0);
                break;
            case 8:
                OLED_ShowString(30, 30, "8", 8, 0);
                break;
            case 9:
                OLED_ShowString(30, 40, "9", 8, 0);
                break;
            case 10:
                OLED_ShowString(30, 50, "0", 8, 0);
                break;
            case 11:
                OLED_ShowString(64, 10, "-", 8, 0);
                break;
            case 12:
                OLED_ShowString(64, 20, "back", 8, 0);
                break;
            default:
                break;
            }
            OLED_Refresh();
        }
        if (key2state == 1)
        {
            select = 1;
            key2state = 0;
            OLED_Clear();
            if( choice == 10)
            {
                value = value * 10 + 0; // Add 0 to the value
            }
            if( choice == 11)
            {
                flag = -1;
            }
            if (choice == 12)
            {
                return value * flag; // back to main menu
            }
            value = value * 10 + choice;
            OLED_Clear();
            select = 0;
            choice = 1;
        }
    }
}

