#include "main.h"

void GPIO_INIT(void)
{
    //Initializing all EN pins
    EN_CLK_ENABLE();
    GPIO_InitTypeDef EN_InitStruct;
    memset(&EN_InitStruct, 0, sizeof(EN_InitStruct));
    EN_InitStruct.Pin = EN_L_PIN | EN_R_PIN;
    EN_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    EN_InitStruct.Pull = GPIO_NOPULL;
    EN_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(EN_GPIO_PORT, &EN_InitStruct);

    //Initializing all POL pins
    POL_CLK_ENABLE();
    GPIO_InitTypeDef POL_InitStruct;
    memset(&POL_InitStruct, 0, sizeof(POL_InitStruct));
    POL_InitStruct.Pin = POL_L_PIN | POL_R_PIN;
    POL_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    POL_InitStruct.Pull = GPIO_NOPULL;
    POL_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(POL_GPIO_PORT, &POL_InitStruct);


    //Initializing all channel pins from the receiver
    CH_CLK_ENABLE();
    GPIO_InitTypeDef CH_InitStruct;
    memset(&CH_InitStruct, 0, sizeof(CH_InitStruct));
    CH_InitStruct.Pin = CH1_PIN | CH2_PIN | CH3_PIN | CH4_PIN;
    CH_InitStruct.Mode = GPIO_MODE_INPUT;
    CH_InitStruct.Pull = GPIO_NOPULL;
    CH_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(CH_GPIO_PORT, &CH_InitStruct);
}